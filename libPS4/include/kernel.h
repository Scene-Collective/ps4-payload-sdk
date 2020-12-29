#pragma once

#ifndef KERNEL_H
#define KERNEL_H

#include "types.h"

typedef struct {
  uint64_t unk1;
  char version_string[0x1C];
  uint32_t version;
} SceFwInfo;

typedef struct timeval SceKernelTimeval;
typedef uint64_t SceKernelEqueue;

extern int libKernelHandle;

extern int **__stack_chk_guard;
extern void (*__stack_chk_fail)(void);
extern int *(*__error)();
#define errno (*__error())

extern int (*sceKernelError)(int);

extern int (*sceKernelLoadStartModule)(const char *name, size_t argc, const void *argv, unsigned int flags, int, int);

extern int (*sceKernelAllocateDirectMemory)(off_t searchStart, off_t searchEnd, size_t length, size_t alignment, int type, off_t *physicalAddressDestination);
extern int (*sceKernelMapDirectMemory)(void **addr, size_t length, int protection, int flags, off_t start, size_t alignment);
extern size_t (*sceKernelGetDirectMemorySize)();

extern int (*sceKernelStat)(const char *path, void *buf);
extern int (*sceKernelOpen)(const char *path, int flags, int mode);
extern int (*sceKernelRead)(int fd, void *buf, size_t nbyte);
extern int (*sceKernelLseek)(int fd, off_t offset, int whence);
extern int (*sceKernelClose)(int fd);

extern unsigned int (*sceKernelSleep)(unsigned int seconds);
extern int (*sceKernelUsleep)(unsigned int microseconds);
extern int (*sceKernelGettimeofday)(SceKernelTimeval *tp);
extern uint64_t (*sceKernelGetProcessTime)(void);
extern int (*sceKernelGetCurrentCpu)(void);

extern int (*sysctl)(int *name, unsigned int namelen, char *oldval, size_t *oldlen, char *newval, size_t newlen);
extern int (*sysctlbyname)(char *name, char *oldval, size_t *oldlen, char *newval, size_t newlen);
extern int (*sysarch)(int type, void *arg);
extern int (*execve)(char *path, char *argv[], char *envp[]);
int ioctl(int fd, unsigned long com, void *data);

extern void *(*pthread_self)();
extern int (*pthread_setaffinity_np)(void *one, long unsigned int two, void *three);

extern int (*sceKernelCreateEqueue)(SceKernelEqueue *eq, const char *name);
extern int (*sceKernelDeleteEqueue)(SceKernelEqueue eq);
extern int (*sceKernelAddUserEvent)(SceKernelEqueue eq, int id);
extern int (*sceKernelAddReadEvent)(SceKernelEqueue eq, int fd, size_t size, void *udata);

extern int (*getuid)();
extern int (*getgid)();
extern int (*getpid)();

extern int (*setuid)(int uid);
extern int (*setgid)(int gid);
extern int (*setreuid)(int ruid, int euid);
extern int (*setregid)(int rgid, int egid);

extern const char* (*sceKernelGetFsSandboxRandomWord)();
extern int (*sceKernelGetSystemSwVersion)(SceFwInfo* fw_info);

int kill(int pid, int signum);

void initKernel(void);

int kexec(void *func, void *user_arg);

#endif
