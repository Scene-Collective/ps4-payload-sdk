#include "module.h"
#include "syscall.h"

#include "kernel.h"

int libKernelHandle;

int **__stack_chk_guard;
void (*__stack_chk_fail)(void);
int *(*__error)();

int (*sceKernelError)(int);

int (*sceKernelLoadStartModule)(const char *name, size_t argc, const void *argv, unsigned int flags, int, int);

int (*sceKernelAllocateDirectMemory)(off_t searchStart, off_t searchEnd, size_t length, size_t alignment, int type, off_t *physicalAddressDestination);
int (*sceKernelMapDirectMemory)(void **addr, size_t length, int protection, int flags, off_t start, size_t alignment);
size_t (*sceKernelGetDirectMemorySize)();

int (*sceKernelStat)(const char *path, void *buf);
int (*sceKernelOpen)(const char *path, int flags, int mode);
int (*sceKernelRead)(int fd, void *buf, size_t nbyte);
int (*sceKernelLseek)(int fd, off_t offset, int whence);
int (*sceKernelClose)(int fd);

int (*sceKernelLwfsAllocateBlock)(int fd, off_t size);
int (*sceKernelLwfsSetAttribute)(int fd, int flags);
int (*sceKernelLwfsTrimBlock)(int fd, off_t size);
off_t (*sceKernelLwfsLseek)(int fd, off_t offset, int whence);
ssize_t (*sceKernelLwfsWrite)(int fd, const void *buf, size_t nbytes);

unsigned int (*sceKernelSleep)(unsigned int seconds);
int (*sceKernelUsleep)(unsigned int microseconds);
int (*usleep)(unsigned int microseconds);
int (*sceKernelGettimeofday)(SceKernelTimeval *tp);
uint64_t (*sceKernelGetProcessTime)(void);
int (*sceKernelGetCurrentCpu)(void);

int (*sysctl)(int *name, unsigned int namelen, char *oldval, size_t *oldlen, char *newval, size_t newlen);
int (*sysctlbyname)(char *name, char *oldval, size_t *oldlen, char *newval, size_t newlen);
int (*sysarch)(int type, void *arg);
int (*execve)(char *path, char *argv[], char *envp[]);

void *(*pthread_self)();
int (*pthread_setaffinity_np)(void *one, long unsigned int two, void *three);

int (*sceKernelCreateEqueue)(SceKernelEqueue *eq, const char *name);
int (*sceKernelDeleteEqueue)(SceKernelEqueue eq);
int (*sceKernelAddUserEvent)(SceKernelEqueue eq, int id);
int (*sceKernelAddReadEvent)(SceKernelEqueue eq, int fd, size_t size, void *udata);

int (*getuid)();
int (*getgid)();
int (*getpid)();

int (*setuid)(int uid);
int (*setgid)(int gid);
int (*setreuid)(int ruid, int euid);
int (*setregid)(int rgid, int egid);

int (*sceKernelSendNotificationRequest)(int device, SceNotificationRequest *req, size_t size, int blocking);
const char *(*sceKernelGetFsSandboxRandomWord)();
int (*sceKernelGetSystemSwVersion)(SceFwInfo *fw_info);

uint32_t (*sceKernelGetCpuTemperature)(uint32_t *);

uint32_t (*sceKernelGetIdPs)(void *);
uint32_t (*sceKernelGetOpenPsId)(void *);
uint32_t (*sceKernelGetOpenPsIdForSystem)(void *);

SYSCALL(kill, 37);
SYSCALL(ioctl, 54);

SYSCALL(kexec, 11);

SYSCALL(is_in_sandbox, 585);

void initKernel(void) {
  if (libKernelHandle) {
    return;
  }

  __error = NULL;

  if (loadModule("libkernel.sprx", &libKernelHandle)) {
    if (loadModule("libkernel_web.sprx", &libKernelHandle)) {
      loadModule("libkernel_sys.sprx", &libKernelHandle);
    }
  }

  RESOLVE(libKernelHandle, __stack_chk_guard);
  RESOLVE(libKernelHandle, __stack_chk_fail);
  RESOLVE(libKernelHandle, __error);

  RESOLVE(libKernelHandle, sceKernelError);

  RESOLVE(libKernelHandle, sceKernelLoadStartModule);

  RESOLVE(libKernelHandle, sceKernelAllocateDirectMemory);
  RESOLVE(libKernelHandle, sceKernelMapDirectMemory);
  RESOLVE(libKernelHandle, sceKernelGetDirectMemorySize);

  RESOLVE(libKernelHandle, sceKernelStat);
  RESOLVE(libKernelHandle, sceKernelOpen);
  RESOLVE(libKernelHandle, sceKernelRead);
  RESOLVE(libKernelHandle, sceKernelLseek);
  RESOLVE(libKernelHandle, sceKernelClose);
  
  RESOLVE(libKernelHandle, sceKernelLwfsAllocateBlock);
  RESOLVE(libKernelHandle, sceKernelLwfsSetAttribute);
  RESOLVE(libKernelHandle, sceKernelLwfsTrimBlock);
  RESOLVE(libKernelHandle, sceKernelLwfsLseek);
  RESOLVE(libKernelHandle, sceKernelLwfsWrite);

  RESOLVE(libKernelHandle, sceKernelSleep);
  RESOLVE(libKernelHandle, sceKernelUsleep);
  RESOLVE(libKernelHandle, usleep);
  RESOLVE(libKernelHandle, sceKernelGettimeofday);
  RESOLVE(libKernelHandle, sceKernelGetProcessTime);
  RESOLVE(libKernelHandle, sceKernelGetCurrentCpu);

  RESOLVE(libKernelHandle, sysctl);
  RESOLVE(libKernelHandle, sysctlbyname);
  RESOLVE(libKernelHandle, sysarch);
  RESOLVE(libKernelHandle, execve);

  RESOLVE(libKernelHandle, pthread_self);
  RESOLVE(libKernelHandle, pthread_setaffinity_np);

  RESOLVE(libKernelHandle, sceKernelCreateEqueue);
  RESOLVE(libKernelHandle, sceKernelDeleteEqueue);
  RESOLVE(libKernelHandle, sceKernelAddUserEvent);
  RESOLVE(libKernelHandle, sceKernelAddReadEvent);

  RESOLVE(libKernelHandle, getuid);
  RESOLVE(libKernelHandle, getgid);
  RESOLVE(libKernelHandle, getpid);

  RESOLVE(libKernelHandle, setuid);
  RESOLVE(libKernelHandle, setgid);
  RESOLVE(libKernelHandle, setreuid);
  RESOLVE(libKernelHandle, setregid);

  RESOLVE(libKernelHandle, sceKernelSendNotificationRequest);
  RESOLVE(libKernelHandle, sceKernelGetFsSandboxRandomWord);
  RESOLVE(libKernelHandle, sceKernelGetSystemSwVersion);

  RESOLVE(libKernelHandle, sceKernelGetCpuTemperature);

  RESOLVE(libKernelHandle, sceKernelGetIdPs);
  RESOLVE(libKernelHandle, sceKernelGetOpenPsId);
  RESOLVE(libKernelHandle, sceKernelGetOpenPsIdForSystem);
}
