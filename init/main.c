#include <stdint.h>

#include <gpio.h>
#include <timer.h>

extern int _kernel_start;
extern int _kernel_end;

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	gpio_select_function(47, 1); // turn ack LED into output
	gpio_set_pin(47, 1); // turn LED on
	while(1){
		wait(500000);
		gpio_set_pin(47, 0);
		wait(500000);
		gpio_set_pin(47, 1);
	}
}
