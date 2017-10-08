#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#define COLOR_BLACK 0x00000000
#define COLOR_WHITE 0xffffffff

typedef struct {
	uint8_t *font;
	uint32_t *framebuffer;
	uint32_t width;
	uint32_t height;
	uint32_t depth;
	uint32_t pitch;
} display_t;

void init_display(display_t *display, uint32_t w, uint32_t h, uint32_t d);

void clear_display(display_t *display, uint32_t color);
void clear_region(display_t *display, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color);

void draw_pixel(display_t *display, uint32_t x, uint32_t y, uint32_t color); // ADD DIFFERENT BIT COLORS LATER
void draw_line(display_t *display, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void draw_rect(display_t *display, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void draw_char(display_t *display, char ch, uint32_t x, uint32_t y, uint32_t color);
void draw_string(display_t *display, char *string, uint32_t x, uint32_t y, uint32_t color);


#endif
