#include "elf64.h"
#include "file.h"
#include "libc.h"
#include "memory.h"

#include "dump.h"

typedef struct {
  int index;
  uint64_t fileoff;
  size_t bufsz;
  size_t filesz;
  int enc;
} SegmentBufInfo;

#define SELF_MAGIC 0x1D3D154F
#define ELF_MAGIC 0x464C457F

int is_self(const char *fn) {
  struct stat st;
  int res = 0;
  int fd = open(fn, O_RDONLY, 0);
  if (fd != -1) {
    stat(fn, &st);
    void *addr = mmap(0, 0x4000, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (addr != MAP_FAILED) {
      if (st.st_size >= 4) {
        uint32_t selfMagic = *(uint32_t *)((uint8_t *)addr + 0x00);
        if (selfMagic == SELF_MAGIC) {
          uint16_t snum = *(uint16_t *)((uint8_t *)addr + 0x18);
          if (st.st_size >= (0x20 + snum * 0x20 + 4)) {
            uint32_t elfMagic = *(uint32_t *)((uint8_t *)addr + 0x20 + snum * 0x20);
            if (elfMagic == ELF_MAGIC) {
              res = 1;
            }
          }
        }
      }
      munmap(addr, 0x4000);
    }
    close(fd);
  }
  return res;
}

#define DECRYPT_SIZE 0x100000

bool read_decrypt_segment(int fd, uint64_t index, uint64_t offset, size_t size, uint8_t *out) {
  uint8_t *outPtr = out;
  uint64_t outSize = size;
  uint64_t realOffset = (index << 32) | offset;
  while (outSize > 0) {
    size_t bytes = (outSize > DECRYPT_SIZE) ? DECRYPT_SIZE : outSize;
    uint8_t *addr = (uint8_t *)mmap(0, bytes, PROT_READ, MAP_PRIVATE | 0x80000, fd, realOffset);
    if (addr == MAP_FAILED) {
      return 0;
    }
    memcpy(outPtr, addr, bytes);
    munmap(addr, bytes);
    outPtr += bytes;
    outSize -= bytes;
    realOffset += bytes;
  }
  return 1;
}

int is_segment_in_other_segment(Elf64_Phdr *phdr, int index, Elf64_Phdr *phdrs, int num) {
  for (int i = 0; i < num; i += 1) {
    Elf64_Phdr *p = &phdrs[i];
    if (i != index) {
      if (p->p_filesz > 0) {
        if ((phdr->p_offset >= p->p_offset) && ((phdr->p_offset + phdr->p_filesz) <= (p->p_offset + p->p_filesz))) {
          return 1;
        }
      }
    }
  }
  return 0;
}

SegmentBufInfo *parse_phdr(Elf64_Phdr *phdrs, int num, int *segBufNum) {
  SegmentBufInfo *infos = (SegmentBufInfo *)malloc(sizeof(SegmentBufInfo) * num);
  if (infos == NULL) {
    return NULL; // Is this what should be returned when unable to allocate `infos`?
  }
  int segindex = 0;
  for (int i = 0; i < num; i += 1) {
    Elf64_Phdr *phdr = &phdrs[i];
    if (phdr->p_filesz > 0) {
      if ((!is_segment_in_other_segment(phdr, i, phdrs, num)) || (phdr->p_type == 0x6fffff01)) {
        SegmentBufInfo *info = &infos[segindex];
        segindex += 1;
        info->index = i;
        info->bufsz = (phdr->p_filesz + (phdr->p_align - 1)) & (~(phdr->p_align - 1));
        info->filesz = phdr->p_filesz;
        info->fileoff = phdr->p_offset;
        info->enc = (phdr->p_type != 0x6fffff01) ? 1 : 0;
      }
    }
  }
  *segBufNum = segindex;
  return infos;
}

void do_dump(char *saveFile, int fd, SegmentBufInfo *segBufs, int segBufNum, Elf64_Ehdr *ehdr) {
  int sf = open(saveFile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if (sf != -1) {
    size_t elfsz = 0x40 + ehdr->e_phnum * sizeof(Elf64_Phdr);
    write(sf, ehdr, elfsz);
    for (int i = 0; i < segBufNum; i += 1) {
      uint8_t *buf = (uint8_t *)malloc(segBufs[i].bufsz);
      if (buf != NULL) {
        memset(buf, 0, segBufs[i].bufsz);
        if (segBufs[i].enc) {
          if (read_decrypt_segment(fd, segBufs[i].index, 0, segBufs[i].filesz, buf)) {
            lseek(sf, segBufs[i].fileoff, SEEK_SET);
            write(sf, buf, segBufs[i].bufsz);
          }
        } else {
          lseek(fd, -segBufs[i].filesz, SEEK_END);
          read(fd, buf, segBufs[i].filesz);
          lseek(sf, segBufs[i].fileoff, SEEK_SET);
          write(sf, buf, segBufs[i].filesz);
        }
        free(buf);
      }
    }
    close(sf);
  }
}

void decrypt_and_dump_self(char *selfFile, char *saveFile) {
  int fd = open(selfFile, O_RDONLY, 0);
  if (fd != -1) {
    void *addr = mmap(0, 0x4000, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (addr != MAP_FAILED) {
      uint16_t snum = *(uint16_t *)((uint8_t *)addr + 0x18);
      Elf64_Ehdr *ehdr = (Elf64_Ehdr *)((uint8_t *)addr + 0x20 + snum * 0x20);
      ehdr->e_shoff = ehdr->e_shentsize = ehdr->e_shnum = ehdr->e_shstrndx = 0;
      Elf64_Phdr *phdrs = (Elf64_Phdr *)((uint8_t *)ehdr + 0x40);
      int segBufNum = 0;
      SegmentBufInfo *segBufs = parse_phdr(phdrs, ehdr->e_phnum, &segBufNum);
      do_dump(saveFile, fd, segBufs, segBufNum, ehdr);
      free(segBufs);
      munmap(addr, 0x4000);
    }
    close(fd);
  }
}

void decrypt_dir(char *sourcedir, char *destdir) {
  DIR *dir;
  struct dirent *dp;
  struct stat info;
  char src_path[1024], dst_path[1024];

  dir = opendir(sourcedir);
  if (!dir) {
    return;
  }

  mkdir(destdir, 0777);

  while ((dp = readdir(dir)) != NULL) {
    if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
      // Do Nothing
    } else {
      sprintf(src_path, "%s/%s", sourcedir, dp->d_name);
      sprintf(dst_path, "%s/%s", destdir, dp->d_name);
      if (!stat(src_path, &info)) {
        if (S_ISDIR(info.st_mode)) {
          decrypt_dir(src_path, dst_path);
        } else if (S_ISREG(info.st_mode)) {
          if (is_self(src_path)) {
            decrypt_and_dump_self(src_path, dst_path);
          }
        }
      }
    }
  }
  closedir(dir);
}

int wait_for_app(char *title_id) {
  int res = 0;

  DIR *dir;
  struct dirent *dp;

  dir = opendir("/mnt/sandbox/pfsmnt");
  if (!dir) {
    return 0;
  }

  while ((dp = readdir(dir)) != NULL) {
    if (!strcmp(dp->d_name, ".") || !strcmp(dp->d_name, "..")) {
      // Do Nothing
    } else {
      if (strstr(dp->d_name, "-app0") != NULL) {
        sscanf(dp->d_name, "%[^-]", title_id);
        res = 1;
        break;
      }
    }
  }
  closedir(dir);

  return res;
}

int wait_for_bdcopy(char *title_id) {
  char path[256];
  char *buf;
  size_t filelen, progress;

  sprintf(path, "/system_data/playgo/%s/bdcopy.pbm", title_id);
  FILE *pbm = fopen(path, "rb");
  if (!pbm) {
    return 100;
  }

  fseek(pbm, 0, SEEK_END);
  filelen = ftell(pbm);
  fseek(pbm, 0, SEEK_SET);

  buf = malloc(filelen);
  if (buf == NULL) {
    fclose(pbm);
    return 0; // Return 0 on when unable to allocate buffer, should this be 100?
  }

  fread(buf, sizeof(char), filelen, pbm);
  fclose(pbm);

  progress = 0;
  for (size_t i = 0x100; i < filelen; i++) {
    if (buf[i]) {
      progress++;
    }
  }

  free(buf);

  return (progress * 100 / (filelen - 0x100));
}

int wait_for_usb(char *usb_name, char *usb_path) {
  FILE *fp = fopen("/mnt/usb0/.dirtest", "w");
  if (fp) {
    fclose(fp);
    unlink("/mnt/usb0/.dirtest");
    sprintf(usb_name, "%s", "USB0");
    sprintf(usb_path, "%s", "/mnt/usb0");
    return 1;
  }
  return 0;
}
