#pragma once

#ifndef DEBUG_H
#define DEBUG_H

#include "libc.h"
#include "network.h"
#include "syscall.h"
#include "types.h"

extern int DEBUG_SOCK;

#define printf_debug(...)                                                                                                  \
  do {                                                                                                                     \
    {                                                                                                                      \
      char debug_message[256] = {0};                                                                                       \
      int size = snprintf_s(debug_message, sizeof(debug_message), "[DEBUG] [%s %s:%d]", __FILE__, __FUNCTION__, __LINE__); \
      syscall(601, 7, debug_message, 0);                                                                                   \
      if (DEBUG_SOCK >= 0) {                                                                                               \
        SckSend(DEBUG_SOCK, debug_message, size);                                                                          \
      }                                                                                                                    \
    }                                                                                                                      \
    char debug_message[512] = {0};                                                                                         \
    int size = snprintf_s(debug_message, sizeof(debug_message), ##__VA_ARGS__);                                            \
    syscall(601, 7, debug_message, 0);                                                                                     \
    if (DEBUG_SOCK >= 0) {                                                                                                 \
      SckSend(DEBUG_SOCK, debug_message, size);                                                                            \
    }                                                                                                                      \
  } while (0);

#endif
