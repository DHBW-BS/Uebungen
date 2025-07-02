#include <system.h>

void print(char *s) {
    char *c;

    while (*(c = s++) != 0) {
        putchar(*c);
    }

    return;
}

void printHex8(uint8_t n) {
    char *hexdigit = "0123456789ABCDEF";
    uint8_t m;

    m = n >> 4;
    m = m & 0x000F;
    putchar(hexdigit[m]);
    m = n;
    m = m & 0x000F;
    putchar(hexdigit[m]);

    return;
}

void putchar(char c) {
    __asm__ volatile (
        "mov  %0, %%al\n\t"
        "mov  $0x0e, %%ah\n\t"
        "int  $0x10"
        : /* no output */
        : "d" (c)
        : "ax");

    return;
}
