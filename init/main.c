#include <stdint.h>
#include <stddef.h>
#include <gpio.h>
#include <timer.h>
#include <interrupt.h>
#include <arm_timer.h>
#include <alloc.h>
#include <draw.h>
#include <mini_uart.h>
#include <string.h>

#define WIDTH 1440
#define HEIGHT 900
#define DEPTH 32

#define ARM_TIMER_CTL 0x3f00B408
#define ARM_TIMER_CNT 0x3f00B420


extern int _kernel_start;
extern int _kernel_end;

uint32_t* frame_buffer_init(uint32_t width, uint32_t height, uint32_t depth);
uint32_t get_frame_buffer(void);
uint32_t get_pitch(void);
void draw_char(char c, uint32_t x, uint32_t y, uint32_t color);

void write32(uint32_t addr, uint32_t value);

void itoa(uint32_t i, char *str)
{
	
	char inverse_str[10];
	uint32_t inv_str_i = 0;
	while(i != 0){
		char c = (char)((i % 10) + 48);
		inverse_str[inv_str_i++] = c;
		i /= 10;
	}
	inverse_str[inv_str_i] = 0;
	int str_i = 0;
	int i_str_i = inv_str_i - 1;
	while(i_str_i > -1){
		str[str_i++] = inverse_str[i_str_i--];
	}
	str[str_i] = 0;
}


void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	
	uart_init();
	
	
}
