#pragma once
#include <stdint.h>
#include <types.h>

typedef struct _bls_entry {
  uint32_t block_offset;
  uint32_t size;
  uint8_t reserved[8];
  char name[32];
}
bls_entry;

typedef struct _bls_header {
  uint32_t magic;
  uint32_t version;
  uint32_t flags;
  uint32_t file_count;
  uint32_t block_count;
  uint8_t unknown[12];
  struct _bls_entry entry_list[0];
}
bls_header;
