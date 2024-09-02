#pragma once

#ifndef MAIN_H
#define MAIN_H

#include "types.h"

#define SPLIT_APP 1
#define SPLIT_PATCH 2

#define TROPHY_MAGIC 0xDCA24D00
#define NPBIND_MAGIC 0xD294A018

#define bswap16 __builtin_bswap16
#define bswap32 __builtin_bswap32
#define bswap64 __builtin_bswap64

typedef struct {
  int split;
  int notify;
  int shutdown;
} configuration;

typedef struct {
  uint32_t magic;
  uint32_t version;
  uint64_t file_size;
  uint64_t entry_size;
  uint64_t num_entries;
  char padding[96];
} npbind_header;

typedef struct {
  uint16_t type;
  uint16_t size;
  char data[0xC];
} npbind_npcommid_entry;

typedef struct {
  uint16_t type;
  uint16_t size;
  char data[0xC];
} npbind_trophy_number_entry;

typedef struct {
  uint16_t type;
  uint16_t size;
  char data[0xB0];
} npbind_unk1_entry;

typedef struct {
  uint16_t type;
  uint16_t size;
  char data[0x10];
} npbind_unk2_entry;

typedef struct {
  npbind_npcommid_entry npcommid;
  npbind_trophy_number_entry trophy_number;
  npbind_unk1_entry unk1;
  npbind_unk2_entry unk2;
  char padding[0x98];
} npbind_body;

typedef struct {
  npbind_header header;
  npbind_body body[];
} npbind_content;

typedef struct {
  npbind_content content;
  char digest[0x14];
} npbind_file;

#endif
