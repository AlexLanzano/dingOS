#include <arm_timer.h>
#include <stdint.h>



static arm_timer_t *arm_timer = (arm_timer_t *)ARM_TIMER_BASE;

arm_timer_t* get_arm_timer(void)
{
	return arm_timer;
}
