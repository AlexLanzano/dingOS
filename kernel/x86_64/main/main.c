#include <types.h>

int main()
{
    uint64_t a = 45;
    a += 10;
    __asm__("hlt");
    return a;
}
