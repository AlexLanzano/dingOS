#include <stdint.h>

#ifndef GPIO_H
#define GPIO_H

#define ACK_ON()  do{ gpio_set_pin(47, 1);} while(0)
#define ACK_OFF() do{ gpio_set_pin(47, 0);} while(0)

#define GPIO_BASE 0x3f200000

#define GPIO_GPFSEL0    (GPIO_BASE + 0x0)
#define GPIO_GPFSEL1    (GPIO_BASE + 0x4)
#define GPIO_GPFSEL2    (GPIO_BASE + 0x8)
#define GPIO_GPFSEL3    (GPIO_BASE + 0xc)
#define GPIO_GPFSEL4    (GPIO_BASE + 0x10)
#define GPIO_GPFSEL5    (GPIO_BASE + 0x14)

#define GPIO_GPSET0     (GPIO_BASE + 0x1c)
#define GPIO_GPSET1     (GPIO_BASE + 0x20)

#define GPIO_GPCLR0     (GPIO_BASE + 0x28)
#define GPIO_GPCLR1     (GPIO_BASE + 0x2c)

#define GPIO_GPLEV0     (GPIO_BASE + 0x34)
#define GPIO_GPLEV1     (GPIO_BASE + 0x38)

#define GPIO_GPEDS0     (GPIO_BASE + 0x40)
#define GPIO_GPEDS1     (GPIO_BASE + 0x44)

#define GPIO_GPREN0     (GPIO_BASE + 0x4c)
#define GPIO_GPREN1     (GPIO_BASE + 0x50)

#define GPIO_GPFEN0     (GPIO_BASE + 0x58)
#define GPIO_GPFEN1     (GPIO_BASE + 0x5c)

#define GPIO_GPHEN0     (GPIO_BASE + 0x64)
#define GPIO_GPHEN1     (GPIO_BASE + 0x68)

#define GPIO_GPLEN0     (GPIO_BASE + 0x70)
#define GPIO_GPLEN1     (GPIO_BASE + 0x74)

#define GPIO_GPAREN0    (GPIO_BASE + 0x7c)
#define GPIO_GPAREN1    (GPIO_BASE + 0x80)

#define GPIO_GPAFEN0    (GPIO_BASE + 0x88)
#define GPIO_GPAFEN1    (GPIO_BASE + 0x8c)

#define GPIO_GPPUD      (GPIO_BASE + 0x94)
#define GPIO_GPPUDCLK0  (GPIO_BASE + 0x98)
#define GPIO_GPPUDCLK1  (GPIO_BASE + 0x9c)



#define GPIO_FS_INPUT 0
#define GPIO_FS_OUTPUT 1
#define GPIO_FS_ALT5 2
#define GPIO_FS_ALT4 3
#define GPIO_FS_ALT0 4
#define GPIO_FS_ALT1 5
#define GPIO_FS_ALT2 6
#define GPIO_FS_ALT3 7

void gpio_select_function(uint32_t pin, uint32_t function);
void gpio_set_pin(uint32_t pin, uint32_t value);

#endif
