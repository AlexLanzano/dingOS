#ifndef VGA_H
#define VGA_H

#include <stdint.h>
#include <stdarg.h>

#define VGA_TERMINAL_BUFFER 0xb8000

typedef enum vga_terminal_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
} vga_terminal_color_t;

enum vga_cursor_direction {
	VGA_CURSOR_DIRECTION_UP,
	VGA_CURSOR_DIRECTION_DOWN,
	VGA_CURSOR_DIRECTION_LEFT,
	VGA_CURSOR_DIRECTION_RIGHT,
};

struct vga_terminal_cursor {
	uint32_t x;
	uint32_t y; 
};

struct vga_terminal {
	uint16_t *buffer;
	uint8_t color;
	uint32_t width;
	uint32_t height;
	struct vga_terminal_cursor cursor;
};


void init_vga_terminal(uint32_t width, uint32_t height);
void vga_terminal_clear();
void vga_terminal_putc(char c);
void vga_terminal_puts(char *str);
void vga_terminal_printf(char *format, ...);


#endif
