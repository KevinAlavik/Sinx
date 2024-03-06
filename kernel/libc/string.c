#include "string.h"

size_t strlen(const char *str) {
    size_t len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

char *strcpy(char *dest, const char *src) {
    char *temp = dest;
    while ((*temp++ = *src++) != '\0');
    return dest;
}

char *strncpy(char *dest, const char *src, size_t n) {
    char *temp = dest;
    while (n-- && (*temp++ = *src++));
    if (n > 0) {
        while (n--) {
            *temp++ = '\0';
        }
    }
    return dest;
}

char *strcat(char *dest, const char *src) {
    char *temp = dest;
    while (*temp) {
        temp++;
    }
    while ((*temp++ = *src++) != '\0');
    return dest;
}

char *strncat(char *dest, const char *src, size_t n) {
    char *temp = dest;
    while (*temp) {
        temp++;
    }
    while (n-- && (*temp++ = *src++));
    *temp = '\0';
    return dest;
}

int strcmp(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

int strncmp(const char *str1, const char *str2, size_t n) {
    while (n-- && *str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    if (n == 0) return 0;
    return *(const unsigned char *)str1 - *(const unsigned char *)str2;
}

char *strchr(const char *str, int c) {
    while (*str && *str != c) {
        str++;
    }
    if (*str == c) return (char *)str;
    return NULL;
}

char *strrchr(const char *str, int c) {
    const char *found = NULL;
    while (*str) {
        if (*str == c) found = str;
        str++;
    }
    return (char *)found;
}

char *strstr(const char *haystack, const char *needle) {
    size_t needle_len = strlen(needle);
    while (*haystack) {
        if (strncmp(haystack, needle, needle_len) == 0) {
            return (char *)haystack;
        }
        haystack++;
    }
    return NULL;
}

size_t strcspn(const char *str, const char *reject) {
    size_t count = 0;
    while (*str && strchr(reject, *str) == NULL) {
        count++;
        str++;
    }
    return count;
}

size_t strspn(const char *str, const char *accept) {
    size_t count = 0;
    while (*str && strchr(accept, *str) != NULL) {
        count++;
        str++;
    }
    return count;
}

char *strpbrk(const char *str, const char *accept) {
    while (*str) {
        if (strchr(accept, *str) != NULL) {
            return (char *)str;
        }
        str++;
    }
    return NULL;
}

char *strtok(char *str, const char *delim) {
    static char *last_token = NULL;
    if (str == NULL) str = last_token;
    str += strspn(str, delim);
    if (*str == '\0') return NULL;
    char *start = str;
    str = strpbrk(str, delim);
    if (str != NULL) {
        *str = '\0';
        last_token = str + 1;
    } else {
        last_token = str;
    }
    return start;
}

int strcoll(const char *str1, const char *str2) {
    return strcmp(str1, str2);
}

void *memset(void *s, int c, size_t n) {
    unsigned char *p = s;
    while (n--) {
        *p++ = (unsigned char)c;
    }
    return s;
}

int memcmp(const void *s1, const void *s2, size_t n) {
    const unsigned char *p1 = s1, *p2 = s2;
    while (n--) {
        if (*p1 != *p2) {
            return *p1 - *p2;
        }
        p1++;
        p2++;
    }
    return 0;
}

void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
    unsigned char *d = dest;
    const unsigned char *s = src;
    if (d < s) {
        while (n--) {
            *d++ = *s++;
        }
    } else {
        d += n;
        s += n;
        while (n--) {
            *--d = *--s;
        }
    }
    return dest;
}

void *memchr(const void *s, int c, size_t n) {
    const unsigned char *p = s;
    while (n--) {
        if (*p == (unsigned char)c) {
            return (void *)p;
        }
        p++;
    }
    return NULL;
}
