#include <stdint.h>
#include <gpio.h>
#include <draw.h>
#include <stdarg.h>

uint32_t cursor_x;
uint32_t cursor_y;
uint32_t bg_color;
uint32_t fg_color;
void term_init()
{
	bg_color = COLOR_BLACK;
	fg_color = COLOR_WHITE;
	term_clear();
}


void term_clear()
{
	clear_screen(bg_color);
	cursor_x = 0;
	cursor_y = 0;
}

void term_putc(char data)
{
	if(data == '\n'){
		++cursor_y;
		cursor_x = 0;
	} else {
		draw_char(data, cursor_x, cursor_y, fg_color);
		if(cursor_x + 1 == width){
			++cursor_y;
			cursor_x = 0;
		} else {
			++cursor_x;
		}
	}
}

void term_puts(char *data)
{
	while(*data++){
		term_putc(*data);
	}
}

void term_delc(uint32_t x, uint32_t y)
{
	clear_section(x, y, 8, 16, bg);
}

