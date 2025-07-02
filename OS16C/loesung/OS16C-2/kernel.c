#include <system.h>

int kmain(void) {
    print("starting kernel ...\r\n");

    registerinterrupt(9, keyboardhandler);

    while (1) {        /* pausing CPU while waiting for keyboard action */
        __asm__ volatile (
            "hlt"
        );
    }

    return 0;
}