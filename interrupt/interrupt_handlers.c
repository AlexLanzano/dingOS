#include <stdint.h>

#include <interrupt.h>


static interrupt_controller_t *interrupt_controller = (interrupt_controller_t *)IC_BASE;

interrupt_controller_t* get_interrupt_controller(void)
{
	return interrupt_controller;
}

void __attribute__((interrupt("ABORT"))) reset_handler(void)
{

	
}

void __attribute__((interrupt("UNDEF"))) undefined_instruction_handler(void)
{
	while( 1 )
		{
			/* Do Nothing! */
			    
		}
	
}

void __attribute__((interrupt("SWI"))) software_interrupt_handler(void)
{
	while( 1 )
		{
			/* Do Nothing! */
			    
		}
	
}

void __attribute__((interrupt("ABORT"))) prefetch_abort_handler(void)
{

	
}

void __attribute__((interrupt("ABORT"))) data_abort_handler(void)
{

	
}

void __attribute__((interrupt("IRQ"))) irq_handler(void)
{
	
}

void __attribute__((interrupt("FIQ"))) fiq_handler(void)
{

	
}
