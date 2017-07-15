#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <termio.h>
#include <string.h>

#define PRINT_MAX 1024
#define ITOA_BUFFER_MAX 20

size_t printf(char *format, ...)
{
	char buffer[PRINT_MAX];

	va_list args;
	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	term_puts(buffer);
}


size_t vsprintf(char *buffer, char *format, va_list args)
{
	char *arg_str;
	uint32_t buffer_i = 0;
	while(*format){
		if(*format != '%'){
			buffer[buffer_i++] = *format++; 
		} else {
			++format;
			switch(*format){
			case 'i':
			case 'd':
				buffer_i += itoa(va_arg(args, int), buffer, 10);
				break;
			case 'l':
				buffer_i += itoa(va_arg(args, long), buffer, 10);
				break;
			case 'c':
				buffer[buffer_i++] = va_arg(args, int);
				break;
			case 's':
				arg_str = va_arg(args, char*);
				while(*arg_str && buffer_i < PRINT_MAX)
					buffer[buffer_i++] = *arg_str++;
				break;
			case 'o':

				break;
			case 'x':
				buffer_i += itoa(va_args(args, int), buffer, 16);
				break;
			case 'p':

				break
			}
		}
	}

	
}



size_t itoa(size_t i, char *str, uint32_t base)
{
	char *digits = "0123456789ABCDEF";
	char inverse_str[ITOA_BUFFER_MAX];
	size_t inverse_str_i = 0;
	while(i > 0){
		uint32_t digits_i = i % base;
		i -= digits_i;
		i /= base;
		inverse_str[inverse_str_i++] = digits[digits_i];
	}
	
	for(i = inverse_str_i; i >= 0; --i){
		*str++ = inverse_str[i];
	}
	return inverse_str_i;
}
