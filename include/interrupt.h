#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

#define IC_BASE 0x3f00b200

#define ARM_TIMER       (1 << 0)
#define ARM_MAILBOX     (1 << 1)
#define ARM_DOORBELL0   (1 << 2)
#define ARM_DOORBELL1   (1 << 3)
#define GPU0_HALTED     (1 << 4)
#define GPU1_HALTED     (1 << 5)
#define ILLEGAL_ACCESS1 (1 << 6)
#define ILLEGAL_ACCESS0 (1 << 7)



typedef struct{
	volatile uint32_t irq_basic_pending;
	volatile uint32_t irq_pending1;
	volatile uint32_t irq_pending2;
	volatile uint32_t fiq_control;
	volatile uint32_t enable_irq1;
	volatile uint32_t enable_irq2;
	volatile uint32_t enable_basic_irq;
	volatile uint32_t disable_irq1;
	volatile uint32_t disable_irq2;
	volatile uint32_t disable_basic_irq;
} interrupt_controller_t;

interrupt_controller_t* get_interrupt_controller(void);


#endif
