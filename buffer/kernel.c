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
    print("starting kernel ...\r\n");

    registerinterrupt(9, keyboardhandler);

    while (1) {        /* pausing CPU while waiting for keyboard action */
        __asm__ volatile (
            "hlt"
        );
    }

    shell();
    shell();
    halt();

    return 0;
}