#pragma once

#ifndef PAYLOAD_UTILS_H
#define PAYLOAD_UTILS_H

#include "types.h"

struct auditinfo_addr {
  char useless[184];
};

struct ucred {
  uint32_t useless1;
  uint32_t cr_uid;
  uint32_t cr_ruid;
  uint32_t useless2;
  uint32_t useless3;
  uint32_t cr_rgid;
  uint32_t useless4;
  void *useless5;
  void *useless6;
  void *cr_prison;
  void *useless7;
  uint32_t useless8;
  void *useless9[2];
  void *useless10;
  struct auditinfo_addr useless11;
  uint32_t *cr_groups;
  uint32_t useless12;
};

struct filedesc {
  void *useless1[3];
  void *fd_rdir;
  void *fd_jdir;
};

struct proc {
  char useless[64];
  struct ucred *p_ucred;
  struct filedesc *p_fd;
};

struct thread {
  void *useless;
  struct proc *td_proc;
};

struct kpayload_kbase_info {
  uint16_t fw_version;
  uint64_t uaddr;
};

struct kpayload_kbase_args {
  void *syscall_handler;
  struct kpayload_kbase_info *kpayload_kbase_info;
};

struct kpayload_dump_info {
  uint16_t fw_version;
  uint64_t kaddr;
  uint64_t uaddr;
  size_t size;
};

struct kpayload_dump_args {
  void *syscall_handler;
  struct kpayload_dump_info *kpayload_dump_info;
};

struct kpayload_firmware_info {
  uint16_t fw_version;
};

struct kpayload_firmware_args {
  void *syscall_handler;
  struct kpayload_firmware_info *kpayload_firmware_info;
};

struct kpayload_kclock_info {
  uint16_t fw_version;
  uint64_t set_time;
};

struct kpayload_kclock_args {
  void *syscall_handler;
  struct kpayload_kclock_info *kpayload_kclock_info;
};

struct kpayload_target_id_info {
  uint16_t fw_version;
  uint8_t spoof;
};

struct kpayload_target_id_args {
  void *syscall_handler;
  struct kpayload_target_id_info *kpayload_target_id_info;
};

#define X86_CR0_WP (1 << 16)

static inline __attribute__((always_inline)) uint64_t __readmsr(unsigned long __register) {
  unsigned long __edx;
  unsigned long __eax;
  __asm__("rdmsr"
          : "=d"(__edx), "=a"(__eax)
          : "c"(__register));
  return (((uint64_t)__edx) << 32) | (uint64_t)__eax;
}

static inline __attribute__((always_inline)) uint64_t readCr0(void) {
  uint64_t cr0;
  __asm__ volatile("movq %0, %%cr0"
                   : "=r"(cr0)
                   :
                   : "memory");
  return cr0;
}

static inline __attribute__((always_inline)) void writeCr0(uint64_t cr0) {
  __asm__ volatile("movq %%cr0, %0"
                   :
                   : "r"(cr0)
                   : "memory");
}

#define kernel_base_macro(x)                                                \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL];

#define kernel_ptr_macro(x)                                                 \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base;

#define copyout_macro(x)                                                    \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  copyout = (void *)(kernel_base + K##x##_COPYOUT);

#define jailbreak_macro(x)                                                  \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base;                                      \
  prison0 = (void **)&kernel_ptr[K##x##_PRISON_0];                          \
  rootvnode = (void **)&kernel_ptr[K##x##_ROOTVNODE];

#define mmap_macro(x)                                                       \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base;                                      \
  mmap_patch_1 = &kernel_ptr[K##x##_MMAP_SELF_1];                           \
  mmap_patch_2 = &kernel_ptr[K##x##_MMAP_SELF_2];                           \
  mmap_patch_3 = &kernel_ptr[K##x##_MMAP_SELF_3];

#define aslr_macro(x)                                                       \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base;                                      \
  aslr_patch = &kernel_ptr[K##x##_DISABLE_ASLR];

#define kclock_macro(x)                                                                   \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL];               \
  if (atoi(#x) > 407) {                                                                   \
    sceSblSrtcClearTimeDifference = (void *)(kernel_base + K##x##_CLEAR_TIME_DIFFERENCE); \
    sceSblSrtcClearTimeDifference(15);                                                    \
  }                                                                                       \
  sceSblSrtcSetTime = (void *)(kernel_base + K##x##_SET_TIME);

#define enable_browser_macro(x)                                             \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  sceRegMgrSetInt = (void *)(kernel_base + K##x##_REG_MGR_SET_INT);

#define tid_macro(x)                                                        \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base;                                      \
  tid_patch = &kernel_ptr[K##x##_TARGET_ID];

#define icc_nvs_write_macro(x)                                              \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  icc_nvs_write = (void *)(kernel_base + K##x##_ICC_NVS_WRITE);

#define npdrm_macro(x)                                                      \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base;                                      \
  npdrm_open = &kernel_ptr[K##x##_NPDRM_OPEN];                              \
  npdrm_close = &kernel_ptr[K##x##_NPDRM_CLOSE];                            \
  npdrm_ioctl = &kernel_ptr[K##x##_NPDRM_IOCTL];

#define no_bd_macro(x)                                                      \
  kernel_base = &((uint8_t *)__readmsr(0xC0000082))[-K##x##_XFAST_SYSCALL]; \
  kernel_ptr = (uint8_t *)kernel_base;                                      \
  no_bd_patch = &kernel_ptr[K##x##_NO_BD_PATCH];

#define caseentry(id, macro) \
  case id:                   \
    macro(id);               \
    break;

#define build_kpayload(id, macro)         \
  switch (id) {                           \
    caseentry(350, macro);                \
    caseentry(355, macro);                \
    caseentry(370, macro);                \
    caseentry(400, macro);                \
    caseentry(401, macro);                \
    caseentry(405, macro);                \
    caseentry(406, macro);                \
    caseentry(407, macro);                \
    caseentry(450, macro);                \
    caseentry(455, macro);                \
    caseentry(470, macro);                \
    caseentry(471, macro);                \
    caseentry(472, macro);                \
    caseentry(473, macro);                \
    caseentry(474, macro);                \
    caseentry(500, macro);                \
    caseentry(501, macro);                \
    caseentry(503, macro);                \
    caseentry(505, macro);                \
    caseentry(507, macro);                \
    caseentry(550, macro);                \
    caseentry(553, macro);                \
    caseentry(555, macro);                \
    caseentry(556, macro);                \
    caseentry(600, macro);                \
    caseentry(602, macro);                \
    caseentry(620, macro);                \
    caseentry(650, macro);                \
    caseentry(651, macro);                \
    caseentry(670, macro);                \
    caseentry(671, macro);                \
    caseentry(672, macro);                \
    caseentry(700, macro);                \
    caseentry(701, macro);                \
    caseentry(702, macro);                \
    caseentry(750, macro);                \
    caseentry(751, macro);                \
    caseentry(755, macro);                \
    caseentry(800, macro);                \
    caseentry(801, macro);                \
    caseentry(803, macro);                \
    caseentry(850, macro);                \
    caseentry(852, macro);                \
    caseentry(900, macro);                \
    caseentry(903, macro);                \
    caseentry(904, macro);                \
    caseentry(950, macro);                \
    caseentry(951, macro);                \
    caseentry(960, macro);                \
    caseentry(1000, macro);               \
    caseentry(1001, macro);               \
    caseentry(1050, macro);               \
    caseentry(1070, macro);               \
    caseentry(1071, macro);               \
    caseentry(1100, macro);               \
    caseentry(1102, macro);               \
    caseentry(1150, macro);               \
    caseentry(1152, macro);               \
    caseentry(1200, macro);               \
    caseentry(1202, macro);               \
    caseentry(1250, macro);               \
    caseentry(1252, macro);               \
    caseentry(1300, macro);               \
    caseentry(1302, macro);               \
  default:                                \
    printf_debug("Unsupported firmware"); \
    return -1;                            \
  }

int is_fw_spoofed();
int is_jailbroken();

uint16_t get_firmware();
int get_firmware_string(char *fw_string);

uint64_t get_kernel_base();
int get_memory_dump(uint64_t kaddr, uint64_t *dump, size_t size);
int jailbreak();
int mmap_patch();
int disable_aslr();
int kernel_clock(uint64_t value);
int enable_browser();
int spoof_target_id(uint8_t id);
int enable_perm_uart();
int exit_idu();
int npdrm_patch();
int no_bd_patch();

#endif
