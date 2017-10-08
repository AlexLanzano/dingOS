#include <bcm2836/serial/mini_uart.h>
#include <mem_rw.h>


#define PBASE 0x3F000000
#define ARM_TIMER_CTL   (PBASE+0x0000B408)
#define ARM_TIMER_CNT   (PBASE+0x0000B420)

#define GPFSEL1         (PBASE+0x00200004)
#define GPSET0          (PBASE+0x0020001C)
#define GPCLR0          (PBASE+0x00200028)
#define GPPUD           (PBASE+0x00200094)
#define GPPUDCLK0       (PBASE+0x00200098)

#define AUX_ENABLES     (PBASE+0x00215004)
#define AUX_MU_IO_REG   (PBASE+0x00215040)
#define AUX_MU_IER_REG  (PBASE+0x00215044)
#define AUX_MU_IIR_REG  (PBASE+0x00215048)
#define AUX_MU_LCR_REG  (PBASE+0x0021504C)
#define AUX_MU_MCR_REG  (PBASE+0x00215050)
#define AUX_MU_LSR_REG  (PBASE+0x00215054)
#define AUX_MU_MSR_REG  (PBASE+0x00215058)
#define AUX_MU_SCRATCH  (PBASE+0x0021505C)
#define AUX_MU_CNTL_REG (PBASE+0x00215060)
#define AUX_MU_STAT_REG (PBASE+0x00215064)
#define AUX_MU_BAUD_REG (PBASE+0x00215068)


void dummy(uint32_t);

uint32_t uart_getc(void)
{
	while(1)
		{
			if(read32(AUX_MU_LSR_REG)&0x01) break;
			    
		}
	return(read32(AUX_MU_IO_REG)&0xFF);
	
}

void uart_putc (uint32_t c)
{
	while(1)
		{
			if(read32(AUX_MU_LSR_REG)&0x20) break;
			    
		}
	write32(AUX_MU_IO_REG,c);
	
}

void uart_init (void)
{
	unsigned int ra;

	write32(AUX_ENABLES,1);
	write32(AUX_MU_IER_REG,0);
	write32(AUX_MU_CNTL_REG,0);
	write32(AUX_MU_LCR_REG,3);
	write32(AUX_MU_MCR_REG,0);
	write32(AUX_MU_IER_REG,0);
	write32(AUX_MU_IIR_REG,0xC6);
	write32(AUX_MU_BAUD_REG,270);
	ra=read32(GPFSEL1);
	ra&=~(7<<12); //gpio14
	ra|=2<<12;    //alt5
	ra&=~(7<<15); //gpio15
	ra|=2<<15;    //alt5
	write32(GPFSEL1,ra);
	write32(GPPUD,0);
	for(ra=0;ra<150;ra++) dummy(ra);
	write32(GPPUDCLK0,(1<<14)|(1<<15));
	for(ra=0;ra<150;ra++) dummy(ra);
	write32(GPPUDCLK0,0);
	write32(AUX_MU_CNTL_REG,3);
	
}
