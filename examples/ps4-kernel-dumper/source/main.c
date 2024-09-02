//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"

#define KERNEL_CHUNK_SIZE PAGE_SIZE

int nthread_run = 1;
int notify_time = 20;
char notify_buf[512] = {0};

void *nthread_func(void *arg) {
  UNUSED(arg);
  time_t t1 = 0;
  while (nthread_run) {
    if (notify_buf[0]) {
      time_t t2 = time(NULL);
      if ((t2 - t1) >= notify_time) {
        t1 = t2;
        printf_notification("%s", notify_buf);
      }
    } else {
      t1 = 0;
    }
    sceKernelSleep(1);
  }
  return NULL;
}

uint64_t get_kernel_size(uint64_t kernel_base) {
  uint16_t elf_header_size;       // ELF header size
  uint16_t elf_header_entry_size; // ELF header entry size
  uint16_t num_of_elf_entries;    // Number of entries in the ELF header

  get_memory_dump(kernel_base + 0x34, (uint64_t *)&elf_header_size, sizeof(uint16_t));
  get_memory_dump(kernel_base + 0x34 + sizeof(uint16_t), (uint64_t *)&elf_header_entry_size, sizeof(uint16_t));
  get_memory_dump(kernel_base + 0x34 + (sizeof(uint16_t) * 2), (uint64_t *)&num_of_elf_entries, sizeof(uint16_t));

  printf_debug("elf_header_size: %u bytes\n", elf_header_size);
  printf_debug("elf_header_entry_size: %u bytes\n", elf_header_entry_size);
  printf_debug("num_of_elf_entries: %u\n", num_of_elf_entries);

  uint64_t max = 0;
  for (int i = 0; i < num_of_elf_entries; i++) {
    uint64_t temp_memsz;
    uint64_t temp_vaddr;
    uint64_t temp_align;
    uint64_t temp_max;

    uint64_t memsz_offset = elf_header_size + (i * elf_header_entry_size) + 0x28;
    uint64_t vaddr_offset = elf_header_size + (i * elf_header_entry_size) + 0x10;
    uint64_t align_offset = elf_header_size + (i * elf_header_entry_size) + 0x30;
    get_memory_dump(kernel_base + memsz_offset, &temp_memsz, sizeof(uint64_t));
    get_memory_dump(kernel_base + vaddr_offset, &temp_vaddr, sizeof(uint64_t));
    get_memory_dump(kernel_base + align_offset, &temp_align, sizeof(uint64_t));

    temp_vaddr -= kernel_base;
    temp_vaddr += 0xFFFFFFFF82200000;

    temp_max = (temp_vaddr + temp_memsz + (temp_align - 1)) & ~(temp_align - 1);

    if (temp_max > max) {
      max = temp_max;
    }
  }

  return max - 0xFFFFFFFF82200000;
}

int _main(struct thread *td) {
  UNUSED(td);

  char fw_version[6] = {0};
  char usb_name[7] = {0};
  char usb_path[13] = {0};
  char output_root[PATH_MAX] = {0};
  char saveFile[PATH_MAX] = {0};
  char completion_check[PATH_MAX] = {0};

  initKernel();
  initLibc();
  initPthread();

#ifdef DEBUG_SOCKET
  initNetwork();
  DEBUG_SOCK = SckConnect(DEBUG_IP, DEBUG_PORT);
#endif

  jailbreak();

  initSysUtil();

  get_firmware_string(fw_version);
  uint64_t kernel_base = get_kernel_base();

  ScePthread nthread;
  memset_s(&nthread, sizeof(ScePthread), 0, sizeof(ScePthread));
  scePthreadCreate(&nthread, NULL, nthread_func, NULL, "nthread");

  printf_notification("Running Kernel Dumper\nPS4 Firmware %s", fw_version);

  snprintf_s(notify_buf, sizeof(notify_buf), "Waiting for USB device...");
  wait_for_usb(usb_name, usb_path);
  notify_buf[0] = '\0';

  snprintf_s(output_root, sizeof(output_root), "%s/PS4", usb_path);
  mkdir(output_root, 0777);
  snprintf_s(output_root, sizeof(output_root), "%s/%s", output_root, fw_version);
  mkdir(output_root, 0777);

  snprintf_s(saveFile, sizeof(saveFile), "%s/PS4/%s/kernel.bin", usb_path, fw_version);

  snprintf_s(completion_check, sizeof(completion_check), "%s/kernel.complete", output_root);
  if (file_exists(completion_check)) {
    printf_notification("Kernel already dumped for %s, skipping dumping", fw_version);
    return 0;
  } else {
    unlink(saveFile);
  }

  int fd = open(saveFile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
  if (fd < 0) {
    printf_notification("Unabled to create kernel dump! Quitting...");
    return 0;
  }

  printf_notification("USB device detected.\n\nStarting kernel dumping to %s.", usb_name);

  uint64_t kernel_size = get_kernel_size(kernel_base);
  uint64_t num_of_kernel_chunks = (kernel_size + (KERNEL_CHUNK_SIZE / 2)) / KERNEL_CHUNK_SIZE;

  printf_debug("Kernel Size: %lu bytes\n", kernel_size);
  printf_debug("Kernel Chunks: %lu\n", num_of_kernel_chunks);

  notify_time = 5;
  uint64_t *dump = mmap(NULL, 0x4000, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
  uint64_t pos = 0;
  for (uint64_t i = 0; i < num_of_kernel_chunks; i++) {
    get_memory_dump(kernel_base + pos, dump, KERNEL_CHUNK_SIZE);
    lseek(fd, pos, SEEK_SET);
    write(fd, (void *)dump, KERNEL_CHUNK_SIZE);
    int percent = ((double)(KERNEL_CHUNK_SIZE * i) / ((double)KERNEL_CHUNK_SIZE * (double)num_of_kernel_chunks)) * 100;
    snprintf_s(notify_buf, sizeof(notify_buf), "Kernel dumping to %s\nDone: %i%%", usb_name, percent);
    pos = pos + KERNEL_CHUNK_SIZE;
  }
  notify_buf[0] = '\0';
  nthread_run = 0;

  close(fd);
  munmap(dump, 0x4000);

  touch_file(completion_check);

  printf_notification("Kernel dumped successfully!");

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
