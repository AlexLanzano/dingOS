#include <stdint.h>
#include <stddef.h>

#include <gpio.h>
#include <timer.h>
#include <interrupt.h>
#include <arm_timer.h>
#include <mailbox.h>
#include <alloc.h>


#define WIDTH 320
#define HEIGHT 240
#define DEPTH 32


extern int _kernel_start;
extern int _kernel_end;

int _enable_interrupts(void);

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{

	gpio_select_function(47, 1); // turn ack LED into output
	get_interrupt_controller()->enable_basic_irq = ARM_TIMER;
	get_arm_timer()->load = 0x400;

	get_arm_timer()->control =
		ARM_TIMER_CTRL_23BIT |
		ARM_TIMER_CTRL_ENABLE |
		ARM_TIMER_CTRL_INT_ENABLE |
		ARM_TIMER_CTRL_PRESCALE_256;

	_enable_interrupts();

	
	uint32_t *framebuffer = frame_buffer_init(WIDTH, HEIGHT, DEPTH);
	if(framebuffer == 0)
		ACK_ON();
	ACK_ON();
	while(1){

	    
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
