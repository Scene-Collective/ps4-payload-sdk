//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"

int internal_backup() {
  unlink("/system_data/priv/mms/app.bak");
  unlink("/system_data/priv/mms/addcont.bak");
  unlink("/system_data/priv/mms/av_content_bg.bak");
  unlink("/user/system/webkit/secure/appcache/ApplicationCache.bak");
  unlink("/user/system/webkit/webbrowser/appcache/ApplicationCache.bak");
  copy_file("/system_data/priv/mms/app.db", "/system_data/priv/mms/app.bak");
  copy_file("/system_data/priv/mms/addcont.db", "/system_data/priv/mms/addcont.bak");
  copy_file("/system_data/priv/mms/av_content_bg.db", "/system_data/priv/mms/av_content_bg.bak");
  copy_file("/user/system/webkit/secure/appcache/ApplicationCache.db", "/user/system/webkit/secure/appcache/ApplicationCache.bak");
  copy_file("/user/system/webkit/webbrowser/appcache/ApplicationCache.db", "/user/system/webkit/webbrowser/appcache/ApplicationCache.bak");
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
  
  touch_file("/mnt/usb0/.probe");
  if (!file_exists("/mnt/usb0/.probe")) {
    touch_file("/mnt/usb1/.probe");
    if (!file_exists("/mnt/usb1/.probe")) {
      internal_backup();
      printf_notification("Internal backup complete.\nThis was only a database backup, use a USB device for a full backup.\nPS4 Firmware %s", fw_version);
    } else {
      printf_notification("Backing up to USB1\nPS4 Firmware %s", fw_version);
      unlink("/mnt/usb1/.probe");
      internal_backup();
      mkdir("/mnt/usb1/PS4/", 0777);
      rmtree("/mnt/usb1/PS4/Backup/");
      mkdir("/mnt/usb1/PS4/Backup/", 0777);
      copy_file("/system_data/priv/mms/app.db", "/mnt/usb1/PS4/Backup/app.db");
      copy_file("/system_data/priv/mms/addcont.db", "/mnt/usb1/PS4/Backup/addcont.db");
      copy_file("/system_data/priv/mms/av_content_bg.db", "/mnt/usb1/PS4/Backup/av_content_bg.db");
      mkdir("/mnt/usb1/PS4/Backup/UserData/", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/system_data/", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/system_data/savedata", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/system_data/priv", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/system_data/priv/home", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/system_data/priv/license", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/system_data/priv/activation", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/user/", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/user/home/", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/user/trophy", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/user/license", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/user/settings", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/user/system", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/user/system/webkit", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/user/system/webkit/secure", 0777);
      mkdir("/mnt/usb1/PS4/Backup/UserData/user/system/webkit/webbrowser", 0777);
      printf_notification("Copying user data\nPlease wait...");
      copy_dir("/system_data/savedata", "/mnt/usb1/PS4/Backup/UserData/system_data/savedata");
      copy_dir("/user/home", "/mnt/usb1/PS4/Backup/UserData/user/home");
      copy_dir("/user/trophy", "/mnt/usb1/PS4/Backup/UserData/user/trophy");
      copy_dir("/user/license", "/mnt/usb1/PS4/Backup/UserData/user/license");
      copy_dir("/user/settings", "/mnt/usb1/PS4/Backup/UserData/user/settings");
      copy_dir("/user/system/webkit/secure", "/mnt/usb1/PS4/Backup/UserData/user/system/webkit/secure");
      copy_dir("/user/system/webkit/webbrowser", "/mnt/usb1/PS4/Backup/UserData/user/system/webkit/webbrowser");
      copy_dir("/system_data/priv/home", "/mnt/usb1/PS4/Backup/UserData/system_data/priv/home");
      copy_dir("/system_data/priv/license", "/mnt/usb1/PS4/Backup/UserData/system_data/priv/license");
      copy_dir("/system_data/priv/activation", "/mnt/usb1/PS4/Backup/UserData/system_data/priv/activation");
      printf_notification("USB backup complete!");
    }
  } else {
    printf_notification("Backing up to USB0\nPS4 Firmware %s", fw_version);
    unlink("/mnt/usb0/.probe");
    internal_backup();
    mkdir("/mnt/usb0/PS4/", 0777);
    rmtree("/mnt/usb0/PS4/Backup/");
    mkdir("/mnt/usb0/PS4/Backup/", 0777);
    copy_file("/system_data/priv/mms/app.db", "/mnt/usb0/PS4/Backup/app.db");
    copy_file("/system_data/priv/mms/addcont.db", "/mnt/usb0/PS4/Backup/addcont.db");
    copy_file("/system_data/priv/mms/av_content_bg.db", "/mnt/usb0/PS4/Backup/av_content_bg.db");
    mkdir("/mnt/usb0/PS4/Backup/UserData/", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/system_data/", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/system_data/savedata", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/system_data/priv", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/system_data/priv/home", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/system_data/priv/license", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/system_data/priv/activation", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/user/", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/user/home/", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/user/trophy", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/user/license", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/user/settings", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/user/system", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/user/system/webkit", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/user/system/webkit/secure", 0777);
    mkdir("/mnt/usb0/PS4/Backup/UserData/user/system/webkit/webbrowser", 0777);
    printf_notification("Copying user data\nPlease wait...");
    copy_dir("/system_data/savedata", "/mnt/usb0/PS4/Backup/UserData/system_data/savedata");
    copy_dir("/user/home", "/mnt/usb0/PS4/Backup/UserData/user/home");
    copy_dir("/user/trophy", "/mnt/usb0/PS4/Backup/UserData/user/trophy");
    copy_dir("/user/license", "/mnt/usb0/PS4/Backup/UserData/user/license");
    copy_dir("/user/settings", "/mnt/usb0/PS4/Backup/UserData/user/settings");
    copy_dir("/user/system/webkit/secure", "/mnt/usb0/PS4/Backup/UserData/user/system/webkit/secure");
    copy_dir("/user/system/webkit/webbrowser", "/mnt/usb0/PS4/Backup/UserData/user/system/webkit/webbrowser");
    copy_dir("/system_data/priv/home", "/mnt/usb0/PS4/Backup/UserData/system_data/priv/home");
    copy_dir("/system_data/priv/license", "/mnt/usb0/PS4/Backup/UserData/system_data/priv/license");
    copy_dir("/system_data/priv/activation", "/mnt/usb0/PS4/Backup/UserData/system_data/priv/activation");
    printf_notification("USB backup complete!");
  }

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
