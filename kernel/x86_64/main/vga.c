#include "vga.h"

struct vga_display _display;
void vga_debug() {
    return;
}
void vga_putc(char c)
{
    uint32_t cursor_pos = _display.cursor_pos;
    struct vga_entry *framebuffer = _display.framebuffer;
    struct vga_entry entry = {.ch = c, .color = VGA_COLOR};

    if (cursor_pos >= _display.framebuffer_size) {
        cursor_pos = 0;
    }
    
    framebuffer[cursor_pos++] = entry;
    _display.cursor_pos = cursor_pos;
}

void vga_print(char *str)
{
    while (*str) {
        vga_putc(*str++);
    }
}

void vga_clear()
{
    for (uint32_t i = 0; i < _display.framebuffer_size; i++) {
        vga_putc(' ');
    }
    _display.cursor_pos = 0;
}

void vga_init()
{
    _display.width = 80;
    _display.height = 25;
    _display.cursor_pos = 0;
    _display.framebuffer_size = _display.width * _display.height;
    _display.framebuffer = (struct vga_entry *)VGA_FRAMEBUFFER;
}
