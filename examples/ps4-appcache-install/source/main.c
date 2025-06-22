//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"
#include "ApplicationCache.h"

void writeCacheDB(){
  printf_notification("Start adding custom AppCache, please wait...");
  size_t len = 0;
  unsigned char* fbuf = base64_decode(ApcStr, sizeof(ApcStr), &len);
  sceKernelSleep(5);
	if (len != 0){
    mkdir("/user/system/webkit/webbrowser/appcache", 0777);
    int fid = open("/user/system/webkit/webbrowser/appcache/ApplicationCache.db", O_WRONLY | O_CREAT | O_TRUNC, 0777);
    write(fid, fbuf, len);
    close(fid);
    sceKernelSleep(3);
    printf_notification("AppCache install complete\nYou can now open the PS4 User Guide");
	}else{
		printf_notification("ERROR:\nNo internal cache found");
	}
}

void internal_backup() {
  printf_notification("Start AppCache backup...");
  unlink("/user/system/webkit/webbrowser/appcache/ApplicationCache.bak");
  copy_file("/user/system/webkit/webbrowser/appcache/ApplicationCache.db", "/user/system/webkit/webbrowser/appcache/ApplicationCache.bak");
  rmdir("/user/system/webkit/webbrowser/appcachebak");
  rename("/user/system/webkit/webbrowser/appcache", "/user/system/webkit/webbrowser/appcachebak");
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
  printf_notification("AppCache-Install\nPS4 Firmware %s", fw_version);
  
  internal_backup();
  
  writeCacheDB();
  

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
