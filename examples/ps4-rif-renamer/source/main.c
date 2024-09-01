//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"

int rename_rifs(const char *license_path) {
  DIR *dir;
  dir = opendir(license_path);

  if (dir) {
    struct dirent *dp;
    while ((dp = readdir(dir)) != NULL) {
      char original_filename[PATH_MAX] = {0};

      struct stat info;
      snprintf_s(original_filename, sizeof(original_filename), "%s/%s", license_path, dp->d_name);

      if (stat(original_filename, &info) == -1) {
        // Failed to stat object... skip it
        continue;
      }

      // Rename if it's a file or symbolic link and starts with "fake"
      if ((S_ISREG(info.st_mode) || S_ISLNK(info.st_mode)) && strncmp("fake", dp->d_name, 4) == 0) {
        char modified_filename[PATH_MAX] = {0};
        char new_filename[PATH_MAX] = {0};
        snprintf_s(modified_filename, sizeof(modified_filename), "%s", dp->d_name);
        memmove_s(&modified_filename, sizeof(modified_filename), "free", 4);
        snprintf_s(new_filename, sizeof(new_filename), "%s/%s", license_path, modified_filename);
        rename(original_filename, new_filename);
      }
    }
    closedir(dir);
  } else {
    return -1;
  }
  return 0;
}

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

  char fw_version[6] = {0};
  get_firmware_string(fw_version);
  printf_notification("Running RIF Renamer\nPS4 Firmware %s", fw_version);

  rename_rifs("/system_data/priv/license");
  rename_rifs("/user/license");

  printf_notification("RIFs renamed!");

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
