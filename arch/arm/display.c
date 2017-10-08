#include <display.h>
#include <stdint.h>
#include <bcm2836/io/gpio.h>
#include <mem_rw.h>
#include <VideoCore_4/frame_buffer.h>

void init_display(display_t *display, uint32_t width, uint32_t height, uint32_t depth)
{
	display->width = width;
	display->height = height;
	display->depth = depth;

	uint32_t *framebuffer_info = frame_buffer_init(width, height, depth);

	display->pitch = get_pitch();
	display->framebuffer = get_frame_buffer();
}

void clear_display(display_t *display, uint32_t color)
{
	for(uint32_t i = 0; i < (display->width * display->height); ++i){
		display->framebuffer[i] = color;
	}
}

void clear_section(display_t *display, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t color)
{
	for(uint32_t x1 = x; x1 < w; ++x1){
		for(uint32_t y1 = y; y1 < h; ++y1){
			draw_pixel(display, x1, y1, color);
		}
	}
}


void inline draw_pixel(display_t *display, uint32_t x, uint32_t y, uint32_t color) // ADD DIFFERENT BIT COLORS LATER
{
	display->framebuffer[y * display->width + x] = color;
}


void draw_line(display_t *display, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color)
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
			draw_pixel(display, x1, y1, color);
			y1 += step_y;
		}
	}

	else if(dy == 0){
		while(x1 != x2){
			draw_pixel(display, x1, y1, color);
			x1 += step_x;
		}
	}

	
	else{
		error = (dx - dy);
		while(x1 != x2 && y1 != y2){
			draw_pixel(display, x1, y1, color);
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

void draw_rect(display_t *display, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2, uint32_t color)
{
	int width = x2 - x1;
	int height = y2 - y1;

	draw_line(display, x1, y1, x1+width+1, y1, color);
	draw_line(display, x1, y1, x1, y1+height, color);

	draw_line(display, x2, y2, x2-width+1, y2, color);
	draw_line(display, x2, y2, x2, y2-height, color);
}


void draw_string(display_t *display, char *string, uint32_t x, uint32_t y, uint32_t color)
{
	int x1 = x;
	while(*string != 0){
		draw_char(display, *string++, x1, y, color);
		x1 += 8;
	}
}

