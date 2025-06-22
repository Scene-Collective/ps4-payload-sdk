//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"

#define SPOOF 0x87

int _main(struct thread *td) {
  UNUSED(td);

  initKernel();
  initLibc();

#ifdef DEBUG_SOCKET
  initNetwork();
  DEBUG_SOCK = SckConnect(DEBUG_IP, DEBUG_PORT);
#endif

  jailbreak();
  spoof_target_id(SPOOF);

  initSysUtil();
  char fw_version[6] = {0};
  get_firmware_string(fw_version);
  printf_notification("Spoofing Target ID: 0x%hhx!\nPS4 Firmware %s", SPOOF, fw_version);

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
