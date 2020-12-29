#include "kernel.h"
#include "libc.h"
#include "module.h"
#include "syscall.h"

#include "sysutil.h"

int (*sceSysUtilSendSystemNotificationWithText)(int messageType, char *message);
int (*sceSystemServiceLaunchWebBrowser)(const char *uri, void *);
int (*sceUserServiceInitialize)(void *);
int (*sceUserServiceGetLoginUserIdList)(SceUserServiceLoginUserIdList *);
int (*sceUserServiceGetUserName)(int32_t userId, char *userName, const size_t size);
int (*sceUserServiceGetInitialUser)(int32_t *);
int (*sceUserServiceTerminate)();
int (*sceKernelReboot)();

void initSysUtil(void) {
  int sysUtilHandle = sceKernelLoadStartModule("/system/common/lib/libSceSysUtil.sprx", 0, NULL, 0, 0, 0);
  int libSceSystemService = sceKernelLoadStartModule("/system/common/lib/libSceSystemService.sprx", 0, NULL, 0, 0, 0);
  RESOLVE(sysUtilHandle, sceSysUtilSendSystemNotificationWithText);
  RESOLVE(libSceSystemService, sceSystemServiceLaunchWebBrowser);
}

void systemMessage(char *msg) {
  char buffer[512];
  sprintf(buffer, "%s", msg);
  sceSysUtilSendSystemNotificationWithText(0xDE, buffer);
}

void openBrowser(char *uri) {
  sceSystemServiceLaunchWebBrowser(uri, NULL);
}

int getUserIDList(SceUserServiceLoginUserIdList *userIdList) {
  int libSceUserService = sceKernelLoadStartModule("/system/common/lib/libSceUserService.sprx", 0, NULL, 0, 0, 0);
  RESOLVE(libSceUserService, sceUserServiceInitialize);
  RESOLVE(libSceUserService, sceUserServiceGetLoginUserIdList);
  RESOLVE(libSceUserService, sceUserServiceTerminate);
  if (sceUserServiceInitialize(NULL) == 0) {
    if (sceUserServiceGetLoginUserIdList(userIdList) == 0) {
      sceUserServiceTerminate();
      return 0;
    }
  }
  return -1;
}

int32_t getUserID() {
  SceUserServiceLoginUserIdList userIdList;
  getUserIDList(&userIdList);
  for (int i = 0; i < 1; i++) {
    if (userIdList.userId[i] != -1) {
      return userIdList.userId[i];
    }
  }
  return -1;
}

char *getUserName(int32_t userId) {
  char *retval = malloc(SCE_USER_SERVICE_MAX_USER_NAME_LENGTH + 1);
  if (retval == NULL) {
    return NULL;
  }
  int libSceUserService = sceKernelLoadStartModule("/system/common/lib/libSceUserService.sprx", 0, NULL, 0, 0, 0);
  RESOLVE(libSceUserService, sceUserServiceInitialize);
  RESOLVE(libSceUserService, sceUserServiceGetUserName);
  RESOLVE(libSceUserService, sceUserServiceTerminate);
  if (sceUserServiceInitialize(NULL) == 0) {
    char username[SCE_USER_SERVICE_MAX_USER_NAME_LENGTH + 1];
    if (sceUserServiceGetUserName(userId, username, sizeof(username)) == 0) {
      strcpy(retval, username);
      sceUserServiceTerminate();
      return retval;
    }
  }
  free(retval);
  return NULL;
}

int32_t getInitialUser() {
  int32_t userId;
  int libSceUserService = sceKernelLoadStartModule("/system/common/lib/libSceUserService.sprx", 0, NULL, 0, 0, 0);
  RESOLVE(libSceUserService, sceUserServiceGetInitialUser);
  RESOLVE(libSceUserService, sceUserServiceInitialize);
  RESOLVE(libSceUserService, sceUserServiceTerminate);
  if (sceUserServiceInitialize(NULL) == 0) {
    if (sceUserServiceGetInitialUser(&userId) == 0) {
      sceUserServiceTerminate();
      return userId;
    }
  }
  return -1;
}

void shutdown() {
  int evf = syscall(540, "SceSysCoreReboot");
  syscall(546, evf, 0x4000, 0);
  syscall(541, evf);
  syscall(37, 1, 30);
}

void reboot() {
  int libkernel = sceKernelLoadStartModule("/system/common/lib/libkernel.sprx", 0, NULL, 0, 0, 0);
  RESOLVE(libkernel, sceKernelReboot);
  sceKernelReboot();
}
