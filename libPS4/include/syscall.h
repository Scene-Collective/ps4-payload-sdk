#pragma once

#ifndef SYSCALL_H
#define SYSCALL_H

#include "types.h"

#define SYSCALL(name, number)        \
  __asm__ (".intel_syntax noprefix\n\n" ".globl " #name "\n" #name ":\n" "mov rax, " #number "\n" "jmp syscall_macro\n")

unsigned long syscall(unsigned long n, ...);

#endif
