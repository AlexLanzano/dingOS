#ifndef ARM_TIMER_H
#define ARM_TIMER_H

#include <stdint.h>

#define ARM_TIMER_BASE 0x3f00b400

#define ARM_TIMER_CTRL_23BIT         ( 1 << 1 )

#define ARM_TIMER_CTRL_PRESCALE_1    ( 0 << 2 )
#define ARM_TIMER_CTRL_PRESCALE_16   ( 1 << 2 )
#define ARM_TIMER_CTRL_PRESCALE_256  ( 2 << 2 )

#define ARM_TIMER_CTRL_INT_ENABLE    ( 1 << 5 )
#define ARM_TIMER_CTRL_INT_DISABLE   ( 0 << 5 )

#define ARM_TIMER_CTRL_ENABLE        ( 1 << 7 )
#define ARM_TIMER_CTRL_DISABLE       ( 0 << 7 )

typedef struct{
	volatile uint32_t load;
	volatile uint32_t value;
	volatile uint32_t control;
	volatile uint32_t irq_clear;
	volatile uint32_t raw_irq;
	volatile uint32_t masked_irq;
	volatile uint32_t reload;
	volatile uint32_t predivider;
	volatile uint32_t free_running_counter;
	
} arm_timer_t;

arm_timer_t* get_arm_timer(void);



#endif
