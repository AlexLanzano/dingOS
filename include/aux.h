#ifndef AUX_H
#define AUX_H

#include <stdint.h>

#define AUX_BASE 0x3f215000

#define AUX_IRQ (AUX_BASE + 0x0)
#define AUX_ENABLES (AUX_BASE + 0x4)

#define AUX_MU_IO_REG (AUX_BASE + 0x40)
#define AUX_MU_IER_REG (AUX_BASE + 0x44)
#define AUX_MU_IIR_REG (AUX_BASE + 0x48)
#define AUX_MU_LCR_REG (AUX_BASE + 0x4C)
#define AUX_MU_MCR_REG (AUX_BASE + 0x50)
#define AUX_MU_LSR_REG (AUX_BASE + 0x54)
#define AUX_MU_MSR_REG (AUX_BASE + 0x58)
#define AUX_MU_SCRATCH (AUX_BASE + 0x5C)
#define AUX_MU_CNTL_REG (AUX_BASE + 0x60)
#define AUX_MU_STAT_REG (AUX_BASE + 0x64)
#define AUX_MU_BAUD_REG (AUX_BASE + 0x68)

#define AUX_SPI0_CNTL0_REG (AUX_BASE + 0x80)
#define AUX_SPI0_CNTL1_REG (AUX_BASE + 0x84)
#define AUX_SPI0_STAT_REG (AUX_BASE + 0x88)
#define AUX_SPI0_IO_REG (AUX_BASE + 0x90)
#define AUX_SPI0_PEEK_REG (AUX_BASE + 0x94)

#define AUX_SPI1_CNTL0_REG (AUX_BASE + 0xC0)
#define AUX_SPI1_CNTL1_REG (AUX_BASE + 0xC4)
#define AUX_SPI1_STAT_REG (AUX_BASE + 0xC8)
#define AUX_SPI1_IO_REG (AUX_BASE + 0xD0)
#define AUX_SPI1_PEEK_REG (AUX_BASE + 0xD4)

void aux_mini_uart_init(int baud, int bits);
void aux_mini_uart_putc(char c);
	
#endif
