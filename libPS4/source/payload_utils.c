#include "debug.h"
#include "elf.h"
#include "file.h"
#include "fw_defines.h"
#include "kernel.h"
#include "libc.h"
#include "memory.h"

#include "payload_utils.h"

uint16_t g_firmware;

int is_fw_spoofed() {
  SceFwInfo ssv_fw;
  char ssv_fw_trimmed[5];
  uint16_t ssv_fw_final;

  uint16_t libc_fw = get_firmware();
  sceKernelGetSystemSwVersion(&ssv_fw);

  char temp[0x1C];
  snprintf(temp, 0x1C, "%s", ssv_fw.version_string);

  char *first = strtok(temp, ".");
  char *second = strtok(NULL, ".");

  sprintf(ssv_fw_trimmed, "%s%c%c", first, second[0], second[1]);

  ssv_fw_final = atoi(ssv_fw_trimmed);

  if (ssv_fw_final != libc_fw) {
    return 1;
  }

  return 0;
}

int is_jailbroken() {
  if (getuid() == 0 && is_in_sandbox() == 0) {
    return 1;
  }
  return 0;
}

int kpayload_kbase(struct thread *td, struct kpayload_kbase_args *args) {
  UNUSED(td);
  void *kernel_base;

  int (*copyout)(const void *kaddr, void *uaddr, size_t len);

  uint16_t fw_version = args->kpayload_kbase_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, copyout_macro);

  uint64_t uaddr = args->kpayload_kbase_info->uaddr;
  copyout(&kernel_base, (uint64_t *)uaddr, 8);

  return 0;
}

int kpayload_dump(struct thread *td, struct kpayload_dump_args *args) {
  UNUSED(td);
  void *kernel_base;

  int (*copyout)(const void *kaddr, void *uaddr, size_t len);

  uint16_t fw_version = args->kpayload_dump_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, copyout_macro);

  uint64_t kaddr = args->kpayload_dump_info->kaddr;
  uint64_t uaddr = args->kpayload_dump_info->uaddr;
  size_t size = args->kpayload_dump_info->size;

  int ret = copyout((uint64_t *)kaddr, (uint64_t *)uaddr, size);

  if (ret == -1) {
    memset((uint64_t *)uaddr, 0, size);
  }

  return ret;
}

int kpayload_jailbreak(struct thread *td, struct kpayload_firmware_args *args) {
  struct filedesc *fd;
  struct ucred *cred;
  fd = td->td_proc->p_fd;
  cred = td->td_proc->p_ucred;

  void *kernel_base;
  uint8_t *kernel_ptr;
  void **prison0;
  void **rootvnode;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, jailbreak_macro);

  cred->cr_uid = 0;
  cred->cr_ruid = 0;
  cred->cr_rgid = 0;
  cred->cr_groups[0] = 0;

  cred->cr_prison = *prison0;
  fd->fd_rdir = fd->fd_jdir = *rootvnode;

  void *td_ucred = *(void **)(((char *)td) + 304);

  uint64_t *sonyCred = (uint64_t *)(((char *)td_ucred) + 96);
  *sonyCred = 0xffffffffffffffff;

  uint64_t *sceProcessAuthorityId = (uint64_t *)(((char *)td_ucred) + 88);
  *sceProcessAuthorityId = 0x3801000000000013;

  uint64_t *sceProcCap = (uint64_t *)(((char *)td_ucred) + 104);
  *sceProcCap = 0xffffffffffffffff;

  return 0;
}

int kpayload_mmap(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  uint8_t *kmem;
  uint8_t *mmap_patch_1;
  uint8_t *mmap_patch_2;
  uint8_t *mmap_patch_3;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, mmap_macro);

  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  kmem = (uint8_t *)mmap_patch_1;
  kmem[0] = 0xB8;
  kmem[1] = 0x01;
  kmem[2] = 0x00;
  kmem[3] = 0x00;
  kmem[4] = 0x00;
  kmem[5] = 0xC3;

  kmem = (uint8_t *)mmap_patch_2;
  kmem[0] = 0xB8;
  kmem[1] = 0x01;
  kmem[2] = 0x00;
  kmem[3] = 0x00;
  kmem[4] = 0x00;
  kmem[5] = 0xC3;

  kmem = (uint8_t *)mmap_patch_3;
  kmem[0] = 0x31;
  kmem[1] = 0xC0;
  kmem[2] = 0xEB;
  kmem[3] = 0x01;

  writeCr0(cr0);

  return 0;
}

int kpayload_aslr(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  uint8_t *kmem;
  uint8_t *aslr_patch;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, aslr_macro);

  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  // This may change depending on new firmware's function structure
  kmem = (uint8_t *)aslr_patch;
  kmem[0] = 0xEB;
  if (fw_version < 600 || fw_version > 755) {
    // 3.50-5.56 and 8.00-13.04
    kmem[1] = 0x00;
  }

  writeCr0(cr0);

  return 0;
}

int kpayload_kernel_clock(struct thread *td, struct kpayload_kclock_args *args) {
  UNUSED(td);
  void *kernel_base;

  void (*sceSblSrtcSetTime)(uint64_t tm);
  void (*sceSblSrtcClearTimeDifference)(uint64_t value);

  uint16_t fw_version = args->kpayload_kclock_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, kclock_macro);

  uint64_t set_time = args->kpayload_kclock_info->set_time;

  sceSblSrtcSetTime(set_time);

  return 0;
}

int kpayload_enable_browser(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;

  uint64_t (*sceRegMgrSetInt)(uint32_t regId, int value);

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, enable_browser_macro);

  sceRegMgrSetInt(0x3C040000, 0);

  return 0;
}

int kpayload_target_id(struct thread *td, struct kpayload_target_id_args *args) {
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  uint8_t *kmem;
  uint8_t *tid_patch;

  uint16_t fw_version = args->kpayload_target_id_info->fw_version;
  uint8_t spoof = args->kpayload_target_id_info->spoof;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, tid_macro);

  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  kmem = (uint8_t *)tid_patch;
  kmem[0] = spoof;

  writeCr0(cr0);

  return 0;
}

int kpayload_perm_uart(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;

  uint64_t (*icc_nvs_write)(uint32_t block, uint32_t offset, uint32_t size, void *value);

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, icc_nvs_write_macro);

  char uart = 1;
  icc_nvs_write(4, 0x31F, 1, &uart);

  return 0;
}

int kpayload_exit_idu(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;

  uint64_t (*icc_nvs_write)(uint32_t block, uint32_t offset, uint32_t size, void *value);

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, icc_nvs_write_macro);

  char flag = 0;
  icc_nvs_write(4, 0x1600, 1, &flag);

  return 0;
}

int kpayload_npdrm_patch(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  uint8_t *kmem;
  uint8_t *npdrm_close;
  uint8_t *npdrm_open;
  uint8_t *npdrm_ioctl;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, npdrm_macro);

  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  kmem = (uint8_t *)npdrm_open;
  kmem[0] = 0x31;
  kmem[1] = 0xC0;
  kmem[2] = 0xC3;

  kmem = (uint8_t *)npdrm_close;
  kmem[0] = 0x31;
  kmem[1] = 0xC0;
  kmem[2] = 0xC3;

  // This may change depending on new firmware's function structure
  kmem = (uint8_t *)npdrm_ioctl;
  kmem[0] = 0xEB;
  if (fw_version < 500) {
    // 3.50-4.74
    kmem[1] = 0x04;
  } else {
    // 5.00-13.04
    kmem[1] = 0x00;
  }

  writeCr0(cr0);

  return 0;
}

int kpayload_no_bd(struct thread *td, struct kpayload_firmware_args *args) {
  UNUSED(td);
  void *kernel_base;
  uint8_t *kernel_ptr;

  // Use "kmem" for all patches
  uint8_t *kmem;

  // Pointers to be assigned in build_kpayload macro
  uint8_t *no_bd_patch;

  uint16_t fw_version = args->kpayload_firmware_info->fw_version;

  // NOTE: This is a C preprocessor macro
  build_kpayload(fw_version, no_bd_macro);

  // Disable write protection
  uint64_t cr0 = readCr0();
  writeCr0(cr0 & ~X86_CR0_WP);

  kmem = (uint8_t *)no_bd_patch;
  kmem[0] = 0xC7;
  kmem[1] = 0x02;
  kmem[2] = 0x03;
  kmem[3] = 0x00;
  kmem[4] = 0x00;
  kmem[5] = 0x00;
  kmem[6] = 0x48;
  kmem[7] = 0x31;
  kmem[8] = 0xC0;
  kmem[9] = 0xEB;
  kmem[10] = 0x00;

  // Restore write protection
  writeCr0(cr0);

  return 0;
}

uint16_t get_firmware() {
  // Return early if this has already been run
  if (g_firmware) {
    return g_firmware;
  }

  char sandbox_path[33]; // `/XXXXXXXXXX/common/lib/libc.sprx` [Char count of 32 + nullterm]
  snprintf_s(sandbox_path, sizeof(sandbox_path), "/%s/common/lib/libc.sprx", sceKernelGetFsSandboxRandomWord());
  int fd = open(sandbox_path, O_RDONLY, 0);
  if (fd < 0) {
    // Assume it's currently jailbroken
    fd = open("/system/common/lib/libc.sprx", O_RDONLY, 0);
    if (fd < 0) {
      // It's really broken
      return -1;
    }
  }

  // Read SELF header from file
  lseek(fd, 0, SEEK_SET);
  SelfHeader self_header;
  if (read(fd, &self_header, sizeof(self_header)) != sizeof(self_header)) {
    return -1;
  }

  // Calculate ELF header offset from the number of SELF segments
  uint64_t elf_header_offset = sizeof(self_header) + self_header.num_of_segments * sizeof(SelfEntry);

  // Read ELF header from file
  lseek(fd, elf_header_offset, SEEK_SET);
  Elf64_Ehdr elf_header;
  if (read(fd, &elf_header, sizeof(elf_header)) != sizeof(elf_header)) {
    return -1;
  }

  // Calculate SCE header offset from number of ELF entries
  uint64_t sce_header_offset = elf_header_offset + elf_header.e_ehsize + elf_header.e_phnum * elf_header.e_phentsize;

  // Align
  while (sce_header_offset % 0x10 != 0) {
    sce_header_offset++;
  }

  // Read SCE header
  lseek(fd, sce_header_offset, SEEK_SET);
  SceHeader sce_header;
  if (read(fd, &sce_header, sizeof(sce_header)) != sizeof(sce_header)) {
    return -1;
  }

  close(fd);

  // Format and return
  char string_fw[5] = {0}; // "0000\0"
  snprintf_s(string_fw, sizeof(string_fw), "%02lx%02lx", (sce_header.fw_version >> (5 * 8)) & 0xFF, (sce_header.fw_version >> (4 * 8)) & 0xFF);

  uint16_t ret = atoi(string_fw); // Numerical representation of the firmware version. ex: 505 for 5.05, 702 for 7.02, etc

  g_firmware = ret;
  return ret;
}

int get_firmware_string(char *fw_string) {
  uint16_t fw_version = get_firmware();

  sprintf(fw_string, "%i", fw_version);

  if (fw_version < 10) {
    sprintf(fw_string, "0.0%c", fw_string[0]);
  } else if (fw_version < 100) {
    sprintf(fw_string, "0.%c%c", fw_string[0], fw_string[1]);
  } else if (fw_version < 1000) {
    sprintf(fw_string, "%c.%c%c", fw_string[0], fw_string[1], fw_string[2]);
  } else if (fw_version < 10000) {
    sprintf(fw_string, "%c%c.%c%c", fw_string[0], fw_string[1], fw_string[2], fw_string[3]);
  } else {
    return -1;
  }

  return 0;
}

uint64_t get_kernel_base() {
  uint64_t kernel_base;
  uint64_t *kernel_base_ptr = mmap(NULL, 8, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0); // Allocate a buffer in userland
  struct kpayload_kbase_info kpayload_kbase_info;
  kpayload_kbase_info.fw_version = get_firmware();
  kpayload_kbase_info.uaddr = (uint64_t)kernel_base_ptr;
  if (kexec(&kpayload_kbase, &kpayload_kbase_info) < 0) {
    kernel_base = -1;
  } else {
    memcpy(&kernel_base, kernel_base_ptr, 8);
  }
  munmap(kernel_base_ptr, 8);
  return kernel_base;
}

int get_memory_dump(uint64_t kaddr, uint64_t *uaddr, size_t size) {
  struct kpayload_dump_info kpayload_dump_info;
  kpayload_dump_info.fw_version = get_firmware();
  kpayload_dump_info.kaddr = kaddr;
  kpayload_dump_info.uaddr = (uint64_t)uaddr;
  kpayload_dump_info.size = size;
  return kexec(&kpayload_dump, &kpayload_dump_info);
}

int jailbreak() {
  if (is_jailbroken()) {
    return 0;
  }
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_jailbreak, &kpayload_firmware_info);
}

int mmap_patch() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_mmap, &kpayload_firmware_info);
}

int disable_aslr() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_aslr, &kpayload_firmware_info);
}

int kernel_clock(uint64_t set_time) {
  struct kpayload_kclock_info kpayload_kclock_info;
  kpayload_kclock_info.fw_version = get_firmware();
  kpayload_kclock_info.set_time = set_time;
  return kexec(&kpayload_kernel_clock, &kpayload_kclock_info);
}

int enable_browser() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_enable_browser, &kpayload_firmware_info);
}

int spoof_target_id(uint8_t id) {
  struct kpayload_target_id_info kpayload_target_id_info;
  kpayload_target_id_info.fw_version = get_firmware();
  kpayload_target_id_info.spoof = id;
  return kexec(&kpayload_target_id, &kpayload_target_id_info);
}

int enable_perm_uart() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_perm_uart, &kpayload_firmware_info);
}

int exit_idu() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_exit_idu, &kpayload_firmware_info);
}

int npdrm_patch() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_npdrm_patch, &kpayload_firmware_info);
}

int no_bd_patch() {
  struct kpayload_firmware_info kpayload_firmware_info;
  kpayload_firmware_info.fw_version = get_firmware();
  return kexec(&kpayload_no_bd, &kpayload_firmware_info);
}
