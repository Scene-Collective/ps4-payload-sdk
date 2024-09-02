#pragma once
#include <stdint.h>
#include <types.h>

typedef struct _verify_blsheader_args {
  void *buffer;     // rbx (rsi)
  uint64_t length;  // r14 (rdx)
  uint64_t unknown; // rax
}
verify_blsheader_args;

typedef struct _decrypt_header_args {
  void *buffer;
  size_t length;
  int type;
}
decrypt_header_args;

typedef struct _verify_segment_args {
  uint16_t index;
  void *buffer;
  size_t length;
}
verify_segment_args;

typedef struct _decrypt_segment_args {
  uint16_t index;
  void *buffer;
  size_t length;
}
decrypt_segment_args;

typedef struct _decrypt_segment_block_args {
  uint16_t entry_index;
  uint16_t block_index;
  void *block_buffer;
  size_t block_length;
  void *table_buffer;
  size_t table_length;
}
decrypt_segment_block_args;