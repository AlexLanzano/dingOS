#include <stdint.h>


#define SYS_TIMER_BASE    0x3f003000
#define SYS_TIMER_CS      0
#define SYS_TIMER_CLO     1
#define SYS_TIMER_CHI     2
#define SYS_TIMER_C0      3
#define SYS_TIMER_C1      4
#define SYS_TIMER_C2      5
#define SYS_TIMER_C3      6

void wait(uint32_t msec);




#define TIMER_BASE        0x3f00b000
#define TIMER_LOAD        TIMER_BASE + 0x400
#define TIMER_VALUE       TIMER_BASE + 0x404
#define TIMER_CONTROL     TIMER_BASE + 0x408
#define TIMER_IRQ_CLEAR   TIMER_BASE + 0x40c
#define TIMER_RAW_IRQ     TIMER_BASE + 0x410
#define TIMER_MASKED_IRQ  TIMER_BASE + 0x414
#define TIMER_RELOAD      TIMER_BASE + 0x418

void init_timer();

