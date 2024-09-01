#include "decryptio.h"

#define chunksize 2097152

ssize_t readbytes(const decrypt_state * state, size_t offset, size_t bytes, void * buffer, size_t buffersize) {

  if (bytes > buffersize) {
     printf_debug("ReadBytes failed! - Error: Buffer is too small!\n");
     return -1;
  }

  ssize_t result = -1;

  if (offset != 0) {

      switch (offset) {
      case DIO_RESET:
          result = lseek(state->input_file, 0, SEEK_SET);
          break;
      case DIO_BASEOFFSET:
          result = lseek(state->input_file, state->input_base_offset, SEEK_SET);
          break;
      default:
          result = lseek(state->input_file, state->input_base_offset + offset, SEEK_SET);
          break;
      }

      if (result == -1) {
          int errcode = errno;
          printf_debug("ReadBytes seek_set failed! - Error: %d (%s)\n", errcode, strerror(errcode));
          return -1;
      }

      printf_debug("Seeked to position %zd in input file.\n", result);
  }

  size_t rchunksize = (bytes >= chunksize) ? chunksize : bytes;

  size_t bytesread = 0;
  size_t bytesremaining = bytes;

  while (bytesremaining > 0) {
    result = read(state->input_file, buffer+bytesread, (bytesremaining >= rchunksize) ? rchunksize : bytesremaining);

    if (result < 1) {
       break;
    }

    bytesread += result;
    bytesremaining -= result;
  }

  if ((result == -1) || (bytesread != bytes)) {
      int errcode = errno;
      printf_debug("Read failed; Read %zd of %zd bytes - Result: %d (%s)\n", bytesread, bytes,
												  errcode,
												  strerror(errcode));
      return -1;
  }

//  printf_debug("Read %zd of %zd bytes to from input file.\n", bytesread, byte);

  return bytesread;

}

ssize_t writebytes(const decrypt_state * state, size_t offset, size_t bytes, void * buffer, size_t buffersize) {

  if (bytes > buffersize) {
     printf_debug("WriteBytes failed! - Error: Buffer is too small!\n");
     return -1;
  }

  ssize_t result = -1;

  if (offset != 0) {

      switch (offset) {
      case DIO_RESET:
          result = lseek(state->output_file, 0, SEEK_SET);
          break;
      case DIO_BASEOFFSET:
          result = lseek(state->output_file, state->output_base_offset, SEEK_SET);
          break;
      default:
          result = lseek(state->output_file, state->output_base_offset + offset, SEEK_SET);
          break;
      }

      if (result == -1) {
          int errcode = errno;
          printf_debug("WriteBytes seek_set failed! - Error: %d (%s)\n", errcode, strerror(errcode));
          return -1;
      }

      printf_debug("Seeked to position %zd in output file.\n", result);
  }

  size_t wchunksize = (bytes >= chunksize) ? chunksize : bytes;

  size_t byteswritten = 0;
  size_t bytesremaining = bytes;

  while (bytesremaining > 0) {
    result = write(state->output_file, buffer+byteswritten, (bytesremaining >= wchunksize) ? wchunksize : bytesremaining);

    if (result < 1) {
       break;
    }

    byteswritten += result;
    bytesremaining -= result;
  }

  if ((result == -1) || (byteswritten != bytes)) {
      int errcode = errno;
      printf_debug("Write failed; Write %zd of %zd bytes - Result: %d (%s)\n", byteswritten,
												    bytes, errcode,
												    strerror(errcode));
      return -1;
  }

//  printf_debug("Write %zd of %zd bytes to output file.\n", byteswritten, bytes);

  return byteswritten;

}


