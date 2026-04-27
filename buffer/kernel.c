#include <system.h>

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
    print("starting kernel ... \r\n");

    registerinterrupt(9, keyboardhandler);

    shell();
    halt();

    return 0;
}