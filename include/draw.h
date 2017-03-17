#ifndef DRAW_H
#define DRAW_H

#include <stdint.h>

void init_screen_buffer(uint32_t *fb, uint32_t w, uint32_t h, uint32_t d);
void draw_pixel(uint32_t x, uint32_t y, uint32_t color); // ADD DIFFERENT BIT COLORS LATER
void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void draw_rect(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color);
void draw_char(uint8_t c, uint32_t x, uint32_t y, uint32_t color);
void draw_string(char *string, uint32_t x, uint32_t y, uint32_t color);


#endif
