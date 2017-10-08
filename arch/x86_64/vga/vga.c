#include "vga.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

struct vga_terminal terminal = {0};

static inline uint8_t vga_entry_color(vga_terminal_color_t fg, vga_terminal_color_t bg)
{
	return fg | (bg << 4);
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
	return (uint16_t) uc | ((uint16_t) color << 8);
}


void init_vga_terminal(uint32_t width, uint32_t height)
{
	terminal.buffer = (uint16_t *)VGA_TERMINAL_BUFFER;
	terminal.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_DARK_GREY);
	terminal.width = width;
	terminal.height = height;
	terminal.cursor.x = 0;
	terminal.cursor.y = 0;
}

void vga_terminal_clear()
{
	for (uint32_t i = 0; i < terminal.width * terminal.height; i++) {
		terminal.buffer[i] = vga_entry(' ', terminal.color);
	}
	terminal.cursor.x = 0;
	terminal.cursor.y = 0;
}

bool vga_terminal_move_cursor(enum vga_cursor_direction direction)
{
	switch (direction) {

	case VGA_CURSOR_DIRECTION_UP:
		if (terminal.cursor.y > 0) {
			--terminal.cursor.y;
			return true;
		}
		return false;

	case VGA_CURSOR_DIRECTION_DOWN:
		if (terminal.cursor.y < terminal.height - 1) {
			++terminal.cursor.y;
			return true;
		}
		return false;

	case VGA_CURSOR_DIRECTION_LEFT:
		if (terminal.cursor.x > 0) {
			--terminal.cursor.x;
			return true;
		}
		return false;

	case VGA_CURSOR_DIRECTION_RIGHT:
		if (terminal.cursor.x < terminal.width - 1) {
			++terminal.cursor.x;
			return true;
		}
		return false;
	}

	return false;
}

void vga_terminal_putc(char c)
{
	if (c == '\n') {
		vga_terminal_move_cursor(VGA_CURSOR_DIRECTION_DOWN);
		terminal.cursor.x = 0;
		return;
	}

	uint32_t index = terminal.cursor.y * terminal.width + terminal.cursor.x;
	terminal.buffer[index] = vga_entry(c, terminal.color);
	if (vga_terminal_move_cursor(VGA_CURSOR_DIRECTION_RIGHT) == false) {
		vga_terminal_move_cursor(VGA_CURSOR_DIRECTION_DOWN);
		terminal.cursor.x = 0;
	}
}


void vga_terminal_puts(char *str)
{
	while (*str)
		vga_terminal_putc(*str++);
}



size_t itoa(int32_t i, char *str, int32_t base)
{
	char *digits = "0123456789ABCDEF";
	char inverse_str[10];
	int32_t inverse_str_i = 0;
	while(i > 0){
		int32_t digits_i = i % base;
		i -= digits_i;
		i /= base;
		inverse_str[inverse_str_i++] = digits[digits_i];
	}

	for(i = inverse_str_i - 1; i >= 0; --i){
		*str++ = inverse_str[i];
	}
	/*
	if (inverse_str_i == 2)
		vga_terminal_puts("its 2!\n");
	*/
	return inverse_str_i;
}



size_t vga_terminal_vsprintf(char *buffer, char *format, va_list args)
{
	char *arg_str;
	uint32_t buffer_i = 0;
	while (*format) {
		if (*format != '%') {
			buffer[buffer_i++] = *format++;
		} else {
			++format;
			switch (*format) {
			case 'i':
			case 'd':
				buffer_i += itoa(va_arg(args, int), &buffer[buffer_i], 10);
				break;
			case 'l':
				buffer_i += itoa(va_arg(args, long), &buffer[buffer_i], 10);
				break;
			case 'c':
				buffer[buffer_i++] = va_arg(args, int);
				break;
			case 's':
				arg_str = va_arg(args, char*);
				while(*arg_str && buffer_i < 10242)
					buffer[buffer_i++] = *arg_str++;
				break;
			case 'o':

				break;
			case 'x':
				buffer_i += itoa(va_arg(args, int), &buffer[buffer_i], 16);
				break;
			case 'p':

				break;
			}

			++format;

		}
	}
	return buffer_i;


}

void vga_terminal_printf(char *format, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, format);
	size_t size = vga_terminal_vsprintf(buffer, format, args);
	va_end(args);
	buffer[size] = 0;

	vga_terminal_puts(buffer);
}
