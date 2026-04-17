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

void puthex8(uint8_t n) {
	int i;
    char hexstring[] = "0123456789";

    putchar(hexstring[n & 0x0f]);

	return;

    for (i=0; i<2;i++) {
        putchar(hexstring[n&0x0f]);
    	n = n >> 4;
    }

	return;
}

void puthex32(uint32_t n) {
	int i;
    char hexstring[] = "0123456789";

	return;

    for (i=0; i<8;i++) {
        putchar(hexstring[n&0x0f]);
    	n = n >> 4;
    }

	return;
}
