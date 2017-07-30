#include <stdint.h>
#include <stddef.h>
#include <bcm2836/io/gpio.h>
#include <bcm2836/clock/timer.h>
#include <bcm2836/interrupt.h>
#include <alloc.h>
#include <display.h>
#include <bcm2836/serial/mini_uart.h>
#include <string.h>
#include <mem_rw.h>

#define WIDTH 1440
#define HEIGHT 900
#define DEPTH 32

extern int _kernel_start;
extern int _kernel_end;


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
	init_interrupts();
	
    display_t display;
	init_display(&display, WIDTH, HEIGHT, DEPTH);

	clear_display(&display, COLOR_WHITE);
	
	while(1){}
}
