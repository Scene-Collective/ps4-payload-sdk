#pragma once

#ifndef SYSUTIL_H
#define SYSUTIL_H

#include "debug.h"
#include "kernel.h"
#include "libc.h"
#include "network.h"
#include "types.h"

#define SCE_USER_SERVICE_MAX_LOGIN_USERS 4
#define SCE_USER_SERVICE_MAX_USER_NAME_LENGTH 16

extern int (*sceSysUtilSendSystemNotificationWithText)(int messageType, char *message);

typedef struct SceUserServiceLoginUserIdList {
  int32_t userId[SCE_USER_SERVICE_MAX_LOGIN_USERS];
} SceUserServiceLoginUserIdList;

void initSysUtil(void);
void openBrowser(char *uri);
int getUserIDList(SceUserServiceLoginUserIdList *userIdList);
int32_t getUserID();
char *getUserName(int32_t userId);
int32_t getInitialUser();
void reboot();
void shutdown();

// HUGE shoutout to OSM-Made for removing the need to use the football/soccer icon in the notifications
// https://github.com/OSM-Made/PS4-Notify
#define printf_notification(...)                                                                             \
  do {                                                                                                       \
    SceNotificationRequest noti_buffer = {};                                                                 \
    char icon_uri[38] = "cxml://psnotification/tex_icon_system";                                             \
    noti_buffer.use_icon_image_uri = 1;                                                                      \
    noti_buffer.target_id = -1;                                                                              \
    snprintf_s(noti_buffer.uri, sizeof(noti_buffer.uri), "%s", icon_uri);                                    \
    const int len = snprintf_s(noti_buffer.message, sizeof(noti_buffer.message), ##__VA_ARGS__);             \
    const int len2 = len - 1;                                                                                \
    if (len > 0 && noti_buffer.message[len2] == '\n') {                                                      \
      noti_buffer.message[len2] = 0;                                                                         \
    }                                                                                                        \
    printf_debug("[NOTIFICATION: %s (%s:%d)]: %s\n", __FILE__, __FUNCTION__, __LINE__, noti_buffer.message); \
    sceKernelSendNotificationRequest(0, (SceNotificationRequest *)&noti_buffer, sizeof(noti_buffer), 0);     \
  } while (0)

#endif
