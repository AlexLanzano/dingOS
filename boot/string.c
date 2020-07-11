#include "types.h"
#include "string.h"

void *memcpy(void *dest, void *src, uint64_t count)
{
    uint8_t *d = dest;
    uint8_t *s = src;

    while (count--) {
        *d++ = *s++;
    }

    return dest;
}

void *memset(void *dest, char value, uint64_t count)
{
    uint8_t *tmp = dest;
    while (count--) {
        *tmp++ = value;
    }

    return dest;
}
