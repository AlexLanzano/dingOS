#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <vga.h>


void kernel_main(void)
{
	int test = 11;
	//int test2 = 12;
	init_vga_terminal(80, 25);
	vga_terminal_clear();
	vga_terminal_printf("Hello, world!\n");
	vga_terminal_printf("test = %d\n", test);
	vga_terminal_printf("Hello, world!\n");

	while(1);
}
