#include <stdint.h>


extern const uint8_t *font;
uint32_t *buffer;
uint32_t width;
uint32_t height;
uint32_t depth;


void init_screen_buffer(uint32_t *fb, uint32_t w, uint32_t h, uint32_t d)
{
	buffer = fb;
	width = w;
	height = h;
	depth = d;
}


void draw_pixel(uint32_t x, uint32_t y, uint32_t color) // ADD DIFFERENT BIT COLORS LATER
{
	buffer[y*width +x] = color;
}

void draw_line(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color)
{
	int x_d, y_d;

	x_d = x2 - x1;
	y_d = y2 - y1;

	for(int y = y1; y != y2; y += y_d){
		for(int x = x1; x != x2; x += x_d)
			draw_pixel(x, y, color);
	}
}

void draw_rect(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color)
{
	int width = x2 - x1;
	int height = y2 - y1;

	draw_line(x1, y1, x1+width, y1, color);
	draw_line(x1, y1, x1, y1+height, color);

	draw_line(x2, y2, x2-width, y2, color);
	draw_line(x2, y2, x2, y2-height, color);
}

void draw_char(char c, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t char_addr = font + c * 16;

	for(int row = 0; row < 16; ++row){
		
	}
}

void draw_string(char *string, uint32_t x, uint32_t y, uint32_t color)
{
	
}
