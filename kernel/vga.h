#ifndef VGA_H
#define VGA_H

#include <types.h>

#define VGA_FRAMEBUFFER 0xB8000

#define VGA_COLOR 0x8F

__attribute__((packed)) struct vga_entry {
    char ch;
    uint8_t color;
};


struct vga_display {
    uint8_t width;
    uint8_t height;
    uint32_t cursor_pos;
    uint32_t framebuffer_size;
    struct vga_entry *framebuffer;
};

void vga_init();
void vga_putc(char c);
void vga_print(char *str);
void vga_clear();
void vga_debug();
#endif
