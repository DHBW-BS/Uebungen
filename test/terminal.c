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
    char hexstring[] = "0123456789ABCDEF";
    char outstring[] = "  ";
	int i;

    for (i=0; i<2;i++) {
        outstring[2-i] = hexstring[n&0x0f]);
    	n = n >> 4;
    }
    print(outstring);

	return;
}

void puthex32(uint32_t n) {
    char hexstring[] = "0123456789ABCDEF";
    char outstring[] = "        ";
	int i;

    for (i=0; i<8;i++) {
        outstring[7-i] = hexstring[n&0x0f]);
    	n = n >> 4;
    }
    print(outstring);

	return;
}
