#ifndef MINI_UART_H
#define MINI_UART_H

#include <stdint.h>

void uart_init(void);
void uart_putc(uint32_t c);
uint32_t uart_getc(void);
void uart_puts(const char *str);


#endif
