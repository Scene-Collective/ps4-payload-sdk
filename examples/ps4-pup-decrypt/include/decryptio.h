#include <ps4.h>

typedef struct _decrypt_state {
  char *input_path;
  ssize_t input_base_offset;
  int input_file;

  char *output_path;
  ssize_t output_base_offset;
  int output_file;

  int device_fd;

  char *entryname;
  int entryid;
  int totalentries;
  int pup_type;

  char *notifystr;
}
decrypt_state;

#define DIO_NOSEEK 0
#define DIO_RESET -1
#define DIO_BASEOFFSET -2

ssize_t readbytes(const decrypt_state *state, size_t offset, size_t bytes, void *buffer, size_t buffersize);
ssize_t writebytes(const decrypt_state *state, size_t offset, size_t bytes, void *buffer, size_t buffersize);
