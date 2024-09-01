#pragma once

typedef struct _pup_file_header
{
  uint32_t magic;
  uint32_t unknown_04;
  uint16_t unknown_08;
  uint8_t flags;
  uint8_t unknown_0B;
  uint16_t unknown_0C;
  uint16_t unknown_0E;
}
pup_file_header;

typedef struct _pup_header
{
  pup_file_header file_header;
  uint64_t file_size;
  uint16_t segment_count;
  uint16_t unknown_1A;
  uint32_t unknown_1C;
}
pup_header;

typedef struct _pup_segment
{
  uint32_t flags;
  ssize_t offset;
  size_t compressed_size;
  size_t uncompressed_size;
}
pup_segment;

typedef struct _pup_block_info
{
  uint32_t offset;
  uint32_t size;
}
pup_block_info;
