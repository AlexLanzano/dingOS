#ifndef SPI_H
#define SPI_H

#define SPI_BASE 0x3f204000

void spi_init();
void spi_set_data_mode(int mode);
void spi_set_clock_divider(int clock_divider);
void spi_chip_select(int chip);


#endif
