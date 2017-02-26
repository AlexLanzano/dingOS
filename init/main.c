#include <stdint.h>

#include <gpio.h>
#include <timer.h>
#include <interrupt.h>
#include <arm_timer.h>
#include <mailbox.h>

#define WIDTH 100
#define HEIGHT 100
#define DEPTH 16

#define COLOR_DELTA 0.05

typedef struct{
	float r;
	float g;
	float b;
	float a;
} color_t;

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


	mailbox_property_init();
	mailbox_property_add_tag(ALLOCATE_BUFFER);
	mailbox_property_add_tag(SET_PHYSICAL_SIZE, WIDTH, HEIGHT);
	mailbox_property_add_tag(SET_VIRTUAL_BUFFER, WIDTH, HEIGHT *2);
	mailbox_property_add_tag(SET_DEPTH, DEPTH);
	while(1);

	
	

	
	/*
	gpio_set_pin(47, 1); // turn LED on
	while(1){
		wait(500000);
		gpio_set_pin(47, 0);
		wait(500000);
		gpio_set_pin(47, 1);
	}
	*/

	
}
