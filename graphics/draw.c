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
	int dx, dy;
	int step_x, step_y;
	int error;

	if(x2 >= x1){
		dx = x2 - x1;
		step_x = 1;
	}else{
		dx = x1 - x2;
		step_x = -1;
	}
	if(y2 >= y1){
		dy = y2 - y1;
		step_y = 1;
	}else{
		dy = y1 - y2;
		step_y = -1;
	}

	if(dx == 0){
		while(y1 != y2){
			draw_pixel(x1, y1, color);
			y1 += step_y;
		}
	}

	else if(dy == 0){
		while(x1 != x2){
			draw_pixel(x1, y1, color);
			x1 += step_x;
		}
	}

	
	else{
		error = (dx - dy);
		while(x1 != x2 && y1 != y2){
			draw_pixel(x1, y1, color);
			if(error * 2 >= -dy){
				x1 += step_x;
				error -= dy;
			}
			if(error *2 < dx){
				y1 += step_y;
				error += dx;
			}
		}
	}
	
	
	
}

void draw_rect(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color)
{
	int width = x2 - x1;
	int height = y2 - y1;

	draw_line(x1, y1, x1+width+1, y1, color);
	draw_line(x1, y1, x1, y1+height, color);

	draw_line(x2, y2, x2-width+1, y2, color);
	draw_line(x2, y2, x2, y2-height, color);
}

void draw_char(uint8_t c, uint32_t x, uint32_t y, uint32_t color)
{
	const uint8_t *font_data = font + c * 16;

	for(int row = 0; row < 16; ++row){
		uint8_t row_data = font_data[row];
		for(uint8_t bit = 0; bit < 8; ++bit){
			uint8_t mask = (1 << bit);
			if(mask & row_data)
				draw_pixel(x+bit, y, color);
		}
		++y;
	}
}

void draw_string(char *string, uint32_t x, uint32_t y, uint32_t color)
{
	int x1 = x;
	while(string != 0){
		draw_char(*string, x1, y, color);
		x1 += 8;
		++string;
	}
}
