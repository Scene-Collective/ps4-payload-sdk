#include "kernel.h"
#include "libc.h"
#include "syscall.h"

#include "proc.h"

int findProcess(char* procName) {
  int procPID = 0;
  while (!procPID) {
    int mib[3];
    size_t len;
    mib[0] = CTL_KERN;
    mib[1] = KERN_PROC;
    mib[2] = KERN_PROC_ALL;

    if (sysctl(mib, 3, NULL, &len, NULL, 0) != -1) {
      if (len > 0) {
        void* dump = malloc(len);
        if (dump == NULL) {
          return -1;
        }
        if (sysctl(mib, 3, dump, &len, NULL, 0) != -1) {
          int structSize = *(int*)dump;
          for (size_t i = 0; i < (len / structSize); i++) {
            struct kinfo_proc* procInfo = (struct kinfo_proc*)(dump + (i * structSize));
            if (!strcmp(procInfo->name, procName)) {
              procPID = procInfo->pid;
              break;
            }
          }
        }
        free(dump);
      }
    }

    sceKernelSleep(1);
  }
  return procPID;
}

void closeProcess(char* procname) {
  int pid = findProcess(procname);
  syscall(37, pid, SIGTERM);
}

void killProcess(char* procname) {
  int pid = findProcess(procname);
  syscall(37, pid, SIGKILL);
}

int ptrace(int req, int pid, void* addr, int data);
SYSCALL(ptrace, 26);

void PTRACE(int req, int pid, void* addr, int data) {
  while (ptrace(req, pid, addr, data)) {
    ;
  }
}

void procAttach(int pid) {
  PTRACE(PT_ATTACH, pid, NULL, NULL);
}

void procDetach(int pid) {
  PTRACE(PT_DETACH, pid, NULL, NULL);
}

void procReadBytes(int pid, void* offset, void* buffer, size_t len) {
  struct ptrace_io_desc pt_desc;
  pt_desc.piod_op = PIOD_READ_D;
  pt_desc.piod_addr = buffer;
  pt_desc.piod_offs = offset;
  pt_desc.piod_len = len;
  PTRACE(PT_IO, pid, &pt_desc, NULL);
}

void procWriteBytes(int pid, void* offset, void* buffer, size_t len) {
  struct ptrace_io_desc pt_desc;
  pt_desc.piod_op = PIOD_WRITE_D;
  pt_desc.piod_addr = buffer;
  pt_desc.piod_offs = offset;
  pt_desc.piod_len = len;
  PTRACE(PT_IO, pid, &pt_desc, NULL);
}
