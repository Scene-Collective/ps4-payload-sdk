#pragma once

#ifndef PROC_H
#define PROC_H

#include "types.h"

#define CTL_KERN 1
#define KERN_PROC 14
#define KERN_PROC_ALL 0     /* everything */
#define KERN_PROC_PID 1     /* by process id */
#define KERN_PROC_PGRP 2    /* by process group id */
#define KERN_PROC_SESSION 3 /* by session of pid */
#define KERN_PROC_TTY 4     /* by controlling tty */
#define KERN_PROC_UID 5     /* by effective uid */
#define KERN_PROC_RUID 6    /* by real uid */

#define PT_TRACE_ME 0 /* child declares it's being traced */
#define PT_READ_I 1   /* read word in child's I space */
#define PT_READ_D 2   /* read word in child's D space */
/* was PT_READ_U 3  * read word in child's user structure */
#define PT_WRITE_I 4 /* write word in child's I space */
#define PT_WRITE_D 5 /* write word in child's D space */
/* was PT_WRITE_U 6  * write word in child's user structure */
#define PT_CONTINUE 7    /* continue the child */
#define PT_KILL 8        /* kill the child process */
#define PT_STEP 9        /* single step the child */
#define PT_ATTACH 10     /* trace some running process */
#define PT_DETACH 11     /* stop tracing a process */
#define PT_IO 12         /* do I/O to/from stopped process. */
#define PT_LWPINFO 13    /* Info about the LWP that stopped. */
#define PT_GETNUMLWPS 14 /* get total number of threads */
#define PT_GETLWPLIST 15 /* get thread list */
#define PT_CLEARSTEP 16  /* turn off single step */
#define PT_SETSTEP 17    /* turn on single step */
#define PT_SUSPEND 18    /* suspend a thread */
#define PT_RESUME 19     /* resume a thread */
#define PT_TO_SCE 20
#define PT_TO_SCX 21
#define PT_SYSCALL 22
#define PT_FOLLOW_FORK 23
#define PT_GETREGS 33      /* get general-purpose registers */
#define PT_SETREGS 34      /* set general-purpose registers */
#define PT_GETFPREGS 35    /* get floating-point registers */
#define PT_SETFPREGS 36    /* set floating-point registers */
#define PT_GETDBREGS 37    /* get debugging registers */
#define PT_SETDBREGS 38    /* set debugging registers */
#define PT_VM_TIMESTAMP 40 /* Get VM version (timestamp) */
#define PT_VM_ENTRY 41     /* Get VM map (entry) */

#define PIOD_READ_D 1  /* Read from D space */
#define PIOD_WRITE_D 2 /* Write to D space */
#define PIOD_READ_I 3  /* Read from I space */
#define PIOD_WRITE_I 4 /* Write to I space */

#define SIGQUIT 3  /*quit program*/
#define SIGKILL 9  /*kill program*/
#define SIGTERM 15 /*software termination signal*/

struct kinfo_proc {
  int structSize;
  int layout;
  void* args;
  void* paddr;
  void* addr;
  void* tracep;
  void* textvp;
  void* fd;
  void* vmspace;
  void* wchan;
  int pid;
  char useless[0x173];
  char name[];
};

struct ptrace_io_desc {
  int piod_op;     /* I/O operation */
  void* piod_offs; /* child offset */
  void* piod_addr; /* parent offset */
  size_t piod_len; /* request length */
};

int findProcess(char* procName);

void procAttach(int pid);
void procDetach(int pid);
void procReadBytes(int pid, void* offset, void* buffer, size_t len);
void procWriteBytes(int pid, void* offset, void* buffer, size_t len);
void closeProcess(char* procname);
void killProcess(char* procname);

#endif
