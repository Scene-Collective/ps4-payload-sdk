#include <ps4.h>
#include "decrypt.h"

//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

extern int DEBUG_SOCK;

time_t prevtime;

int _main(struct thread* td) {
  initKernel();
  initLibc();
  initNetwork();

  char fw_version[6] = {0};

  get_firmware_string(fw_version);

  printf_notification("Running PS4 PUP Decrypter\nPS4 Firmware %s", fw_version);

#ifdef DEBUG_SOCKET
  initNetwork();
  DEBUG_SOCK = SckConnect(DEBUG_IP, DEBUG_PORT);
#endif

  jailbreak();

  decrypt_pups("/mnt/usb0/safe.PS4UPDATE.PUP", "/mnt/usb0/%s.dec");
  printf_notification("Finished PS4 PUP Decrypter");

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
