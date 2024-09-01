//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"

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

  SceUserServiceLoginUserIdList userIdList;
  memset_s(&userIdList, sizeof(SceUserServiceLoginUserIdList), 0, sizeof(SceUserServiceLoginUserIdList));

  char fw_version[6] = {0};
  get_firmware_string(fw_version);
  printf_notification("Running History Blocker\nPS4 Firmware %s", fw_version);

  if (getUserIDList(&userIdList) == 0) {
    for (int i = 0; i < SCE_USER_SERVICE_MAX_LOGIN_USERS; i++) {
      if (userIdList.userId[i] != -1 && userIdList.userId[i] != 0) {
        char hfile[PATH_MAX] = {0};
        snprintf_s(hfile, sizeof(hfile), "/user/home/%x/webbrowser/endhistory.txt", userIdList.userId[i]);
        if (!file_exists(hfile) && !dir_exists(hfile)) {
          mkdir(hfile, 0777);
          printf_notification("History blocker enabled for: %s\n\nRun payload again to disable", getUserName(userIdList.userId[i]));
        } else {
          if (dir_exists(hfile)) {
            rmdir(hfile);
            printf_notification("History blocker disabled for: %s\n\nRun payload again to enable", getUserName(userIdList.userId[i]));
          } else if (file_exists(hfile)) {
            unlink(hfile);
            mkdir(hfile, 0777);
            printf_notification("History blocker enabled for: %s\n\nRun payload again to disable", getUserName(userIdList.userId[i]));
          }
        }
      }
    }
  } else {
    printf_notification("Unable to get user ID list");
  }

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
