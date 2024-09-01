//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"

uint8_t THRESHOLDTEMP = 60;

int _main(struct thread *td) {
  UNUSED(td);

  initKernel();
  initLibc();

#ifdef DEBUG_SOCKET
  initNetwork();
  DEBUG_SOCK = SckConnect(DEBUG_IP, DEBUG_PORT);
#endif

  jailbreak();

  initSysUtil();

  int fd = open("/dev/icc_fan", O_RDONLY, 0);
  if (fd <= 0) {
    printf_notification("Unable to Open Fan Settings!");
    return 0;
  }

  char data[10] = {0x00, 0x00, 0x00, 0x00, 0x00, THRESHOLDTEMP, 0x00, 0x00, 0x00, 0x00};
  ioctl(fd, 0xC01C8F07, data);
  close(fd);

  float fahrenheit = ((THRESHOLDTEMP * 9) / 5) + 32;
  char fw_version[6] = {0};
  get_firmware_string(fw_version);
  printf_notification("Fan Threshold Set to %i°C/%i°F!\nPS4 Firmware %s", THRESHOLDTEMP, (int)fahrenheit, fw_version);

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
