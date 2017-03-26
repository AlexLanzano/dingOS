#include <aux.h>
#include <stdint.h>
#include <mem.h>
#include <gpio.h>

#define SYS_FREQ 250000000

void aux_mini_uart_init(int baud, int bits)
{
	mem_write(AUX_ENABLES, 1);

	mem_write(AUX_MU_IER_REG, 0);
	mem_write(AUX_MU_CNTL_REG, 0);
	mem_write(AUX_MU_LCR_REG, 3);

	mem_write(AUX_MU_MCR_REG, 0);
	mem_write(AUX_MU_IER_REG, 0);
	mem_write(AUX_MU_IIR_REG, 0xc6);
	mem_write(AUX_MU_BAUD_REG, 270);

	uint32_t ra;
	ra = mem_read(GPIO_GPFSEL1);
	ra &= ~(7<<12);
	ra |= 2 << 12;

	mem_write(GPIO_GPFSEL1, ra);
	volatile int i;
	
	mem_write(GPIO_GPPUD, 0);
	for(i = 0; i < 150; ++i){}
	mem_write(GPIO_GPPUDCLK0, (1 << 14));
	for(i = 0; i < 150; ++i){}	
	mem_write(GPIO_GPPUDCLK0, 0);

	mem_write(AUX_MU_CNTL_REG, 2);
	
}

void aux_mini_uart_putc(char c)
{
	while((mem_read(AUX_MU_LSR_REG) & (1 << 5)) == 0){}

	mem_write(AUX_MU_IO_REG, c);
}
