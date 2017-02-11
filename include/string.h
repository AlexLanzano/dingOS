#ifndef STRING_H
#define STRING_H


void memcpy(void *dst, const void *src, size_t num);
int memcmp(const void *ptr1, const void *ptr2, size_t num);
void* memchr(const void *ptr, int value, size_t num);
void* memset(void *ptr, int value, size_t num);

char* strcpy(char *dst, const char *src);
char* strncpy(char *dst, const char *src, size_t num);
char* strcat(char *dst, const char *src);
char* strncat(char *dst, const char *src, size_t num);
int strcmp(const char *str1, const char *str2);
int strncmp(const char *str1, const char *str2, size_t num);
char* strchr(const char *str, int ch);
char* strtok(char *str, const char *delim);
size_t strlen(const char* str);
	
	

#endif
