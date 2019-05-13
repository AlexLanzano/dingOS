#include <types.h>
#include "vga.h"

int main()
{
    vga_init();
    vga_clear();
    vga_print("Hello, World!");
    __asm__("hlt");
    return 0;
}
