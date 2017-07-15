#include <string.h>


void memcpy(void *dst, const void *src, size_t num)
{
	unsigned char *dst_buf = (unsigned char*) dst;
	const unsigned char *src_buf = (const unsigned char*) src;

	for(size_t i = 0; i < num; ++i){
		dst_buf[i] = src_buf[i];
		    
	}
	
}
int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	unsigned char *ptr1_buf = (unsigned char*) ptr1;
	unsigned char *ptr2_buf = (unsigned char*) ptr2;
	for(size_t i = 0; i < num; ++i){
		if(ptr1_buf[i] == ptr2_buf[i])
			continue;
		if(ptr1_buf[i] > ptr2_buf[i])
			return 1;
		else
			return -1;
		    
	}
	return 0;
	
}

void* memchr(const void *ptr, int value, size_t num)
{
	unsigned char *ptr_buf = (unsigned char*) ptr;
	for(size_t i = 0; i < num; ++i){
		if((int) ptr_buf[i] == value)
			return &ptr_buf[i];
		    
	}
	return NULL;
	
}
void* memset(void *ptr, int value, size_t num)
{
	unsigned char *ptr_buf = (unsigned char*) ptr;
	for(size_t i = 0; i < num; ++i)
		ptr_buf[i] = (unsigned char) value;

	return ptr;
	
}

char* strcpy(char *dst, const char *src)
{
	int index = 0;
	while(src[index] != '\n'){
		dst[index] = src[index];
		++index;
		    
	}
	dst[index] = '\0';
	return dst;
	
}
char* strncpy(char *dst, const char *src, size_t num)
{
	size_t index;
	for(index = 0; index < num; ++index){
		dst[index] = src[index];
		    
	}
	dst[index] = '\0';
	return dst;
	
}
char* strcat(char *dst, const char *src)
{
	int index = 0;
	//int len = strlen(dst);
	int len = 3;
	while(src[index]){
		dst[len] = src[index];
		++index;
		++len;
		    
	}
	dst[len] = '\0';
	return dst;
	
}

char* strncat(char *dst, const char *src, size_t num)
{
	int len = strlen(dst)-1;
	for(size_t i = 0; i < num; ++i){
		dst[len] = src[i];
		++len;
		    
	}
	dst[len] = '\0';
	return dst;
	
}

int strcmp(const char *str1, const char *str2)
{
	int index = 0;
	while(str1[index] || str2[index]){
		if(str1[index] == str2[index]){
			++index;
			continue;
			        
		}
		if(str1[index] > str2[index]){
			return 1;
			        
		}
		else
			return -1;
		    
	}
	if(str1[index]){
		return 1;
		    
	}else if(str2[index]){
		return -1;
		    
	}else{
		return 0;
		    
	}
	
}
int strncmp(const char *str1, const char *str2, size_t num)
{
	for(size_t i = 0; i < num; ++i){
		if(str1[i] == str2[i])
			continue;
		if(str1[i] > str2[i])
			return 1;
		else
			return -1;
		    
	}
	return 0;
	
}
char* strchr(const char *str, int ch)
{
	char *ret = (char*) str;
	int index = 0;
	while(ret[index]){
		if(ret[index] == ch){
			return &ret[index];
			        
		}
		    
	}
	return NULL;
	
}

char* strtok(char *str, const char *delim)
{
	static char *_rest;
	char *ret, *delim_ptr;
	int c, dc;

	delim_ptr = (char*) delim;

	if(str != NULL)
		_rest = str;
	else
		str = _rest;

	ret = _rest;

	for(;;){
		c = *str++;
		delim_ptr = (char*)delim;
		do{
			if((dc = *delim_ptr++) == c){
				str[-1] = 0;
				_rest = str;
				return ret;
				            
			}
			        
		} while(dc != 0);
		    
	}
	
}

size_t strlen(const char* str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;

	
}

