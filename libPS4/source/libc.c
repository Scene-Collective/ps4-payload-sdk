#include "file.h"
#include "kernel.h"
#include "module.h"

#include "libc.h"

void *(*malloc)(size_t size);
void (*free)(void *ptr);
void *(*calloc)(size_t num, size_t size);
void *(*realloc)(void *ptr, size_t size);
void *(*memalign)(size_t boundary, size_t size);
void *(*memset)(void *destination, int value, size_t num);
void *(*memcpy)(void *destination, const void *source, size_t num);
int (*memcmp)(const void *s1, const void *s2, size_t n);
char *(*strcpy)(char *destination, const char *source);
char *(*strncpy)(char *destination, const char *source, size_t num);
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
char *(*strstr)(char *str1, char *str2);
char *(*strdup)(const char *s);
char *(*strtok)(char *str, const char *sep);
char *(*index)(const char *s, int c);
char *(*rindex)(const char *s, int c);
int (*isdigit)(int c);
int (*atoi)(const char *s);
double (*atof)(const char *s);
size_t (*strlcpy)(char *dst, const char *src, size_t size);
char *(*strerror)(int errnum);
void *(*_Getpctype)();
unsigned long (*_Stoul)(const char *, char **, int);
void (*bcopy)(const void *s1, void *s2, size_t n);

void (*srand)(unsigned int seed);
int (*rand)(void);

char *(*asctime)(const struct tm *tm);
char *(*asctime_r)(const struct tm *tm, char *buf);
char *(*ctime)(const time_t *timep);
char *(*ctime_r)(const time_t *timep, char *buf);
time_t (*time)(time_t *tloc);
struct tm *(*gmtime)(const time_t *timep);
struct tm *(*gmtime_s)(const time_t *timep, struct tm *result);
struct tm *(*localtime)(const time_t *timep);
struct tm *(*localtime_r)(const time_t *timep, struct tm *result);
time_t (*mktime)(struct tm *tm);

DIR *(*opendir)(const char *filename);
struct dirent *(*readdir)(DIR *dirp);
int (*readdir_r)(DIR *dirp, struct dirent *entry, struct dirent **result);
long (*telldir)(const DIR *dirp);
void (*seekdir)(DIR *dirp, long loc);
void (*rewinddir)(DIR *dirp);
int (*closedir)(DIR *dirp);
int (*dirfd)(DIR *dirp);
char *(*getprogname)();

FILE *(*fopen)(const char *filename, const char *mode);
size_t (*fread)(void *ptr, size_t size, size_t count, FILE *stream);
size_t (*fwrite)(const void *ptr, size_t size, size_t count, FILE *stream);
int (*fseek)(FILE *stream, long int offset, int origin);
long int (*ftell)(FILE *stream);
int (*fclose)(FILE *stream);
int (*fprintf)(FILE *stream, const char *format, ...);

int memset_s(void *s, rsize_t smax, int c, rsize_t n) {
  bool violation = (s == NULL) || (smax > RSIZE_MAX) || (n > RSIZE_MAX) || (n > smax);
  if (violation) {
    if ((s != NULL) && !(smax > RSIZE_MAX)) {
      for (rsize_t i = 0; i < smax; ++i) {
        ((volatile unsigned char*)s)[i] = c;
      }
    }
    return 1;
  } else {
    for (rsize_t i = 0; i < n; ++i) {
      ((volatile unsigned char*)s)[i] = c;
    }
    return 0;
  }
}

void initLibc(void) {
  int libc = sceKernelLoadStartModule("libSceLibcInternal.sprx", 0, NULL, 0, 0, 0);

  RESOLVE(libc, malloc);
  RESOLVE(libc, free);
  RESOLVE(libc, calloc);
  RESOLVE(libc, realloc);
  RESOLVE(libc, memalign);
  RESOLVE(libc, memset);
  RESOLVE(libc, memcpy);
  RESOLVE(libc, memcmp);
  RESOLVE(libc, strcpy);
  RESOLVE(libc, strncpy);
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
  RESOLVE(libc, strstr);
  RESOLVE(libc, strdup);
  RESOLVE(libc, strtok);
  RESOLVE(libc, index);
  RESOLVE(libc, rindex);
  RESOLVE(libc, isdigit);
  RESOLVE(libc, atoi);
  RESOLVE(libc, atof);
  RESOLVE(libc, strlcpy);
  RESOLVE(libc, strerror);
  RESOLVE(libc, _Getpctype);
  RESOLVE(libc, _Stoul);
  RESOLVE(libc, bcopy);

  RESOLVE(libc, srand);
  RESOLVE(libc, rand);

  RESOLVE(libc, asctime);
  RESOLVE(libc, asctime_r);
  RESOLVE(libc, ctime);
  RESOLVE(libc, ctime_r);
  RESOLVE(libc, time);
  RESOLVE(libc, gmtime);
  RESOLVE(libc, gmtime_s);
  RESOLVE(libc, localtime);
  RESOLVE(libc, localtime_r);
  RESOLVE(libc, mktime);

  RESOLVE(libc, opendir);
  RESOLVE(libc, readdir);
  RESOLVE(libc, readdir_r);
  RESOLVE(libc, telldir);
  RESOLVE(libc, seekdir);
  RESOLVE(libc, rewinddir);
  RESOLVE(libc, closedir);
  RESOLVE(libc, dirfd);

  RESOLVE(libc, getprogname);

  RESOLVE(libc, fopen);
  RESOLVE(libc, fread);
  RESOLVE(libc, fwrite);
  RESOLVE(libc, fseek);
  RESOLVE(libc, ftell);
  RESOLVE(libc, fclose);
  RESOLVE(libc, fprintf);
}
