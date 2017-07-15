#include <bcm2836/clock/timer.h>


void wait(uint32_t msec)
{
	volatile uint32_t *timer = (uint32_t *)TIMER_BASE;

	uint32_t current_time = timer[TIMER_CLO];

	uint32_t target_time = current_time + msec;
	
	while(current_time < target_time)
		current_time = timer[TIMER_CLO];
	
}

