#include <system.h>

void printHex8(uint8_t n) {
    return;
}

void halt(void) {
	print("system halted\n\r");

	__asm__ volatile (
		"cli\n"
		"hlt"
		: /* no output */
		: /* no input */);

	return;
}

int kmain(void) {
    print("starting kernel ...\r\n");

    registerinterrupt(9, keyboardhandler);

    puthex8(0xEF);
    print("\r\n");
    puthex32(0xDEADBEEF);
    print("\r\n");

    shell();
    halt();

    return 0;
}