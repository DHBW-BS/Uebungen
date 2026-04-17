#include <system.h>

void print(char *s) {
    char *c;

    while (*(c = s++) != 0) {
        putchar(*c);
    }

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
