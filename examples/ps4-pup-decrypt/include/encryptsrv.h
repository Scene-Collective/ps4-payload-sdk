#pragma once

int encsrv_verify_blsheader(int fd, void *buffer, uint64_t length, uint64_t unknown);

int encsrv_decrypt_header(int fd, void *buffer, size_t length, int type);

int encsrv_verify_segment(int fd, uint16_t index, void *buffer, size_t length, int additional);

int encsrv_decrypt_segment(int fd, uint16_t index, void *buffer, size_t length);

int encsrv_decrypt_segment_block(int fd, uint16_t entry_index, uint16_t block_index, void *block_buffer,
                                 size_t block_length, void *table_buffer, size_t table_length);
