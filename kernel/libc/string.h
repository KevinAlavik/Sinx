#ifndef __STRING_H__
#define __STRING_H__

#include <stddef.h>

size_t strlen(const char *str);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, size_t n);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t n);
char *strchr(const char *str, int c);
char *strrchr(const char *str, int c);
char *strstr(const char *haystack, const char *needle);
size_t strcspn(const char *str, const char *reject);
size_t strspn(const char *str, const char *accept);
char *strpbrk(const char *str, const char *accept);
char *strtok(char *str, const char *delim);
int strcoll(const char *str1, const char *str2);
void *memset(void *s, int c, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memchr(const void *s, int c, size_t n);

#endif // __STRING_H__
