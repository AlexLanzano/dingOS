#include <bcm2836/interrupt.h>
#include <bcm2836/clock/timer.h>
#include <memory/mem_rw.h>
#include <bcm2836/io/gpio.h>


__attribute__ ((interrupt ("UNDEF"))) void undefined_instruction_handler(void)
{
	while(1);
}


__attribute__ ((interrupt ("SWI"))) void software_interrupt_handler(void)
{
	ACK_ON();
}


__attribute__ ((interrupt ("ABORT"))) void prefetch_abort_handler(void)
{
	while(1);
}


__attribute__ ((interrupt ("ABORT"))) void data_abort_handler(void)
{
	while(1);
}


__attribute__ ((naked)) void unused_handler(void)
{
	while(1);
}

__attribute__ ((interrupt ("IRQ"))) void irq_handler(void)
{
	while(1);
}

__attribute__ ((interrupt ("FIQ"))) void fast_irq_handler(void)
{
	while(1);
}

void init_interrupts(void)
{
	write32(INTERRUPT_ENABLE_IRQ_BASIC, BASIC_ARM_TIMER_IRQ); // enable timer

}
