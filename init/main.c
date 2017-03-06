#include <stdint.h>
#include <stddef.h>

#include <gpio.h>
#include <timer.h>
#include <interrupt.h>
#include <arm_timer.h>
#include <alloc.h>


#define WIDTH 1360
#define HEIGHT 768
#define DEPTH 32


extern int _kernel_start;
extern int _kernel_end;

int _enable_interrupts(void);
uint32_t* frame_buffer_init(uint32_t width, uint32_t height, uint32_t depth);
void mailbox_write(uint8_t channel, uint32_t value);
uint32_t mailbox_read(uint8_t channel);
uint32_t get_frame_buffer(void);

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{

	gpio_select_function(47, 1); // turn ack LED into output
	get_interrupt_controller()->enable_basic_irq = ARM_TIMER;
	get_arm_timer()->load = 0x400;

	uint32_t color = 0xff000000;
	
	get_arm_timer()->control =
		ARM_TIMER_CTRL_23BIT |
		ARM_TIMER_CTRL_ENABLE |
		ARM_TIMER_CTRL_INT_ENABLE |
		ARM_TIMER_CTRL_PRESCALE_256;

	_enable_interrupts();

	
	uint32_t *frame_buffer = frame_buffer_init(WIDTH, HEIGHT, DEPTH);
	if(frame_buffer == 0)
		ACK_ON();

	uint32_t *buffer = (uint32_t *)(get_frame_buffer());
	
	while(1){
		for(int y = 0; y < HEIGHT; ++y){
			for(int x = 0; x < WIDTH; ++x){
				buffer[y*WIDTH + x] = color;
			}
			color = (color + 1) | 0xff000000;
	    }
	}

	

	
	
	/*
	while(1){
		wait(500000);
		gpio_set_pin(47, 0);
		wait(500000);
		gpio_set_pin(47, 1);
	}
	*/

	
}
