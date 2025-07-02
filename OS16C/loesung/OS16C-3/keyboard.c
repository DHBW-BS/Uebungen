#include <system.h>

void keyboardhandler(void) {
    uint8_t a, c;
    char *keymap = "--1234567890----qwertzuiop----asdfghjkl-----yxcvbnm";

    __asm__ volatile (
        "    pusha"
        : /* no output */
        : /* no input */
        : /* no globber */);

    c = inb(0x60);              /* get key data*/
    a = inb(0x61);              /* get keyboard control */
    outb(a & 0x80, 0x61);
    outb(a, 0x61);
    outb(0x20, 0x20);

    if ((c & 0x80) == 0) {      /* ignore key release */
        printHex8(c);           /* print key code */
        putchar(' ');
        putchar(keymap[c]);     /* print cahracter pressed */
        print("\r\n");
    }

    __asm__ volatile (
        "    popa\n"
        "    leave\n"
        "    iretw"
        : /* no output */
        : /* no input */
        : /* no globber */);

	return;
}
