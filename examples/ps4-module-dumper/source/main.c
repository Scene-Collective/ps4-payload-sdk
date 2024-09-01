//#define DEBUG_SOCKET
#define DEBUG_IP "192.168.2.2"
#define DEBUG_PORT 9023

#include "ps4.h"

int nthread_run = 1;
int notify_time = 20;
char notify_buf[512] = {0};

void *nthread_func(void *arg) {
  UNUSED(arg);
  time_t t1 = 0;
  while (nthread_run) {
    if (notify_buf[0]) {
      time_t t2 = time(NULL);
      if ((t2 - t1) >= notify_time) {
        t1 = t2;
        printf_notification("%s", notify_buf);
      }
    } else {
      t1 = 0;
    }
    sceKernelSleep(1);
  }
  return NULL;
}

int dump_dir_macro(char *src, char *dest, char *root) {
  char output_loc[PATH_MAX] = {0};
  printf_notification("Dumping %s", src);
  snprintf_s(output_loc, sizeof(output_loc), dest, root);
  decrypt_dir(src, output_loc);

  return 0;
}

int dump_file_macro(char *src, char *dest, char *root) {
  char output_loc[PATH_MAX] = {0};
  printf_notification("Dumping %s", src);
  snprintf_s(output_loc, sizeof(output_loc), dest, root);
  decrypt_and_dump_self(src, output_loc);

  return 0;
}

int _main(struct thread *td) {
  UNUSED(td);

  char fw_version[6] = {0};
  char usb_name[7] = {0};
  char usb_path[13] = {0};
  char output_root[PATH_MAX] = {0};
  char completion_check[PATH_MAX] = {0};

  initKernel();
  initLibc();
  initPthread();

#ifdef DEBUG_SOCKET
  initNetwork();
  DEBUG_SOCK = SckConnect(DEBUG_IP, DEBUG_PORT);
#endif

  jailbreak();
  mmap_patch();

  initSysUtil();

  get_firmware_string(fw_version);

  ScePthread nthread;
  memset_s(&nthread, sizeof(ScePthread), 0, sizeof(ScePthread));
  scePthreadCreate(&nthread, NULL, nthread_func, NULL, "nthread");

  printf_notification("Running Module Dumper\nPS4 Firmware %s", fw_version);

  snprintf_s(notify_buf, sizeof(notify_buf), "Waiting for USB device...");
  wait_for_usb(usb_name, usb_path);
  notify_buf[0] = '\0';
  nthread_run = 0;

  snprintf_s(output_root, sizeof(output_root), "%s/PS4", usb_path);
  mkdir(output_root, 0777);
  snprintf_s(output_root, sizeof(output_root), "%s/%s", output_root, fw_version);
  mkdir(output_root, 0777);
  snprintf_s(output_root, sizeof(output_root), "%s/modules", output_root);

  snprintf_s(completion_check, sizeof(completion_check), "%s/.complete", output_root);
  if (file_exists(completion_check)) {
    printf_notification("Modules already dumped for %s, skipping dumping", fw_version);
    return 0;
  } else {
    rmtree(output_root);
  }

  mkdir(output_root, 0777);

  printf_notification("USB device detected.\n\nStarting module dumping to %s.", usb_name);

  dump_dir_macro("/system", "%s/system", output_root);
  dump_dir_macro("/system_ex", "%s/system_ex", output_root);
  dump_dir_macro("/update", "%s/update", output_root);
  dump_file_macro("/mini-syscore.elf", "%s/mini-syscore.elf", output_root);
  dump_file_macro("/safemode.elf", "%s/safemode.elf", output_root);
  dump_file_macro("/SceSysAvControl.elf", "%s/SceSysAvControl.elf", output_root);

  //cleanup(output_root);

  touch_file(completion_check);

  printf_notification("Modules dumped successfully!");

#ifdef DEBUG_SOCKET
  printf_debug("Closing socket...\n");
  SckClose(DEBUG_SOCK);
#endif

  return 0;
}
