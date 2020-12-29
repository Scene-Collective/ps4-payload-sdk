#pragma once

#ifndef NETWORK_H
#define NETWORK_H

#include "types.h"

#define IP(a, b, c, d) (((a) << 0) + ((b) << 8) + ((c) << 16) + ((d) << 24))
#define htons(a) __builtin_bswap16(a)

#define AF_INET 0x0002

#define IN_ADDR_ANY 0

#define SOCK_STREAM 1
#define SOCK_DGRAM 2

#define SOL_SOCKET 0xffff
#define SO_NBIO 0x1200

#define MSG_DONTWAIT 0x80
#define MSG_WAITALL 0x40

#define IPPROTO_TCP 6
#define TCP_NODELAY 1

enum {
  SCE_NET_IPPROTO_IP = 0,
  SCE_NET_IPPROTO_ICMP = 1,
  SCE_NET_IPPROTO_IGMP = 2,
  SCE_NET_IPPROTO_TCP = 6,
  SCE_NET_IPPROTO_UDP = 17,
  SCE_NET_SOL_SOCKET = 0xffff
};

enum {
  SCE_NET_SO_REUSEADDR = 0x00000004,
};

enum {
  SCE_NET_ERROR_EINTR = 0x80410104,
};

enum {
  SCE_NET_SOCKET_ABORT_FLAG_RCV_PRESERVATION = 0x00000001,
  SCE_NET_SOCKET_ABORT_FLAG_SND_PRESERVATION = 0x00000002
};

struct in_addr {
  unsigned int s_addr;
};

struct sockaddr_in {
  unsigned char sin_len;
  unsigned char sin_family;
  unsigned short sin_port;
  struct in_addr sin_addr;
  unsigned short sin_vport;
  char sin_zero[6];
};

struct sockaddr {
  unsigned char sin_len;
  unsigned char sa_family;
  char sa_data[14];
};

typedef unsigned int socklen_t;

/* info code */
#define SCE_NET_CTL_INFO_DEVICE 1
#define SCE_NET_CTL_INFO_ETHER_ADDR 2
#define SCE_NET_CTL_INFO_MTU 3
#define SCE_NET_CTL_INFO_LINK 4
#define SCE_NET_CTL_INFO_BSSID 5
#define SCE_NET_CTL_INFO_SSID 6
#define SCE_NET_CTL_INFO_WIFI_SECURITY 7
#define SCE_NET_CTL_INFO_RSSI_DBM 8
#define SCE_NET_CTL_INFO_RSSI_PERCENTAGE 9
#define SCE_NET_CTL_INFO_CHANNEL 10
#define SCE_NET_CTL_INFO_IP_CONFIG 11
#define SCE_NET_CTL_INFO_DHCP_HOSTNAME 12
#define SCE_NET_CTL_INFO_PPPOE_AUTH_NAME 13
#define SCE_NET_CTL_INFO_IP_ADDRESS 14
#define SCE_NET_CTL_INFO_NETMASK 15
#define SCE_NET_CTL_INFO_DEFAULT_ROUTE 16
#define SCE_NET_CTL_INFO_PRIMARY_DNS 17
#define SCE_NET_CTL_INFO_SECONDARY_DNS 18
#define SCE_NET_CTL_INFO_HTTP_PROXY_CONFIG 19
#define SCE_NET_CTL_INFO_HTTP_PROXY_SERVER 20
#define SCE_NET_CTL_INFO_HTTP_PROXY_PORT 21
#define SCE_NET_CTL_INFO_RESERVED1 22
#define SCE_NET_CTL_INFO_RESERVED2 23

#define SCE_NET_ETHER_ADDR_LEN 6

typedef struct SceNetEtherAddr {
  uint8_t data[SCE_NET_ETHER_ADDR_LEN];
} SceNetEtherAddr;

#define SCE_NET_CTL_SSID_LEN (32 + 1)
#define SCE_NET_CTL_HOSTNAME_LEN (255 + 1)
#define SCE_NET_CTL_AUTH_NAME_LEN (127 + 1)
#define SCE_NET_CTL_IPV4_ADDR_STR_LEN (16)

typedef union SceNetCtlInfo {
  uint32_t device;
  SceNetEtherAddr ether_addr;
  uint32_t mtu;
  uint32_t link;
  SceNetEtherAddr bssid;
  char ssid[SCE_NET_CTL_SSID_LEN];
  uint32_t wifi_security;
  uint8_t rssi_dbm;
  uint8_t rssi_percentage;
  uint8_t channel;
  uint32_t ip_config;
  char dhcp_hostname[SCE_NET_CTL_HOSTNAME_LEN];
  char pppoe_auth_name[SCE_NET_CTL_AUTH_NAME_LEN];
  char ip_address[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
  char netmask[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
  char default_route[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
  char primary_dns[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
  char secondary_dns[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
  uint32_t http_proxy_config;
  char http_proxy_server[SCE_NET_CTL_HOSTNAME_LEN];
  uint16_t http_proxy_port;
} SceNetCtlInfo;

extern int (*sceNetSocket)(const char *, int, int, int);
extern int (*sceNetSocketClose)(int);
extern int (*sceNetConnect)(int, struct sockaddr *, int);
extern int (*sceNetSend)(int, const void *, size_t, int);
extern int (*sceNetBind)(int, struct sockaddr *, int);
extern int (*sceNetListen)(int, int);
extern int (*sceNetAccept)(int, struct sockaddr *, unsigned int *);
extern int (*sceNetRecv)(int, void *, size_t, int);
extern int (*sceNetSocketAbort)(int, int);

extern int (*sceNetGetsockname)(int, struct sockaddr *, unsigned int *);
extern int (*sceNetGetsockopt)(int s, int level, int optname, void *restrict optval, socklen_t *restrict optlen);
extern int (*sceNetSetsockopt)(int s, int level, int optname, const void *optval, socklen_t optlen);

extern char (*sceNetInetNtop)(int af, const void *src, char *dst, int size);
extern int (*sceNetInetPton)(int af, const char *src, void *dst);

extern uint64_t (*sceNetHtonll)(uint64_t host64);
extern uint32_t (*sceNetHtonl)(uint32_t host32);
extern uint16_t (*sceNetHtons)(uint16_t host16);
extern uint64_t (*sceNetNtohll)(uint64_t net64);
extern uint32_t (*sceNetNtohl)(uint32_t net32);
extern uint16_t (*sceNetNtohs)(uint16_t net16);

extern int (*sceNetCtlInit)(void);
extern void (*sceNetCtlTerm)(void);
extern int (*sceNetCtlGetInfo)(int code, SceNetCtlInfo *info);

void initNetwork(void);
int SckConnect(char *hostIP, int hostPort);
void SckClose(int socket);
void SckSend(int socket, char *sdata, int length);
char *SckRecv(int socket);
void SckRecvf(int socket, char *destfile);

#endif
