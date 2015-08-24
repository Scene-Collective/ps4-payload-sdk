#include "module.h"

#include "libc.h"

void *(*malloc)(size_t size);
void (*free)(void *ptr);
void *(*memset)(void *destination, int value, size_t num);
void *(*memcpy)(void *destination, const void *source, size_t num);
char *(*strcpy)(char *destination, const char *source);
char *(*strcat)(char *dest, const char *src);
char *(*strncat)(char *dest, const char *src, size_t n);
size_t (*strlen)(const char *s);
int (*strcmp)(const char *s1, const char *s2);
int (*strncmp)(const char *s1, const char *s2, size_t n);
int (*sprintf)(char *str, const char *format, ...);
int (*snprintf)(char *str, size_t size, const char *format, ...);
int (*sscanf)(const char *str, const char *format, ...);
char *(*strchr)(const char *s, int c);
char *(*strrchr)(const char *s, int c);

char *(*asctime)(const struct tm *tm);
char *(*asctime_r)(const struct tm *tm, char *buf);
extern char *(*ctime)(const time_t *timep);
char *(*ctime_r)(const time_t *timep, char *buf);
struct tm *(*gmtime)(const time_t *timep);
struct tm *(*gmtime_r)(const time_t *timep, struct tm *result);
struct tm *(*localtime)(const time_t *timep);
struct tm *(*localtime_r)(const time_t *timep, struct tm *result);
time_t (*mktime)(struct tm *tm);


void initLibc(void) {
	int libc;
	loadModule("libSceLibcInternal.sprx", &libc);

	RESOLVE(libc, malloc);
	RESOLVE(libc, free);
	RESOLVE(libc, memset);
	RESOLVE(libc, memcpy);
	RESOLVE(libc, strcpy);
	RESOLVE(libc, strcat);
	RESOLVE(libc, strncat);
	RESOLVE(libc, strlen);
	RESOLVE(libc, strcmp);
	RESOLVE(libc, strncmp);
	RESOLVE(libc, sprintf);
	RESOLVE(libc, snprintf);
	RESOLVE(libc, sscanf);
	RESOLVE(libc, strchr);
	RESOLVE(libc, strrchr);

	RESOLVE(libc, asctime);
	RESOLVE(libc, asctime_r);
	RESOLVE(libc, ctime);
	RESOLVE(libc, ctime_r);
	RESOLVE(libc, gmtime);
	RESOLVE(libc, gmtime_r);
	RESOLVE(libc, localtime);
	RESOLVE(libc, localtime_r);
	RESOLVE(libc, mktime);
}
