#include <bcm2836/clock/timer.h>
#include <memory/mem_rw.h>

void wait(uint32_t msec)
{
	volatile uint32_t *sys_timer = (uint32_t *)SYS_TIMER_BASE;

	uint32_t current_time = sys_timer[SYS_TIMER_CLO];

	uint32_t target_time = current_time + msec;
	
	while(current_time < target_time)
		current_time = sys_timer[SYS_TIMER_CLO];
	
}


void init_timer()
{
	// interrupt every 1024 * 256 timer ticks
	write32(TIMER_LOAD, 0x400);


	/*
	 * enable free running counter
	 * enable timer
	 * enable timer interrupt
	 * pre-scale is clock / 256
	 * 23-bit counter
	 */
	write32(TIMER_CONTROL, 0xaa);
}
