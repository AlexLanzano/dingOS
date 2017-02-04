#include <stdint.h>


#define TIMER_BASE    0x3f003000

#define TIMER_CS      0
#define TIMER_CLO     1
#define TIMER_CHI     2
#define TIMER_C0      3
#define TIMER_C1      4
#define TIMER_C2      5
#define TIMER_C3      6

void wait(uint32_t msec);
