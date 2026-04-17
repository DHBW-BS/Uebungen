#include <system.h>

static int read_pos = 0;
static int write_pos = 0;
static char key_buffer[256];

static char keymap[] = {
	'\0', '\0', '1',  '2',  '3',  '4',  '5',  '6',		/* 00 */
	'7',  '8',  '9',  '0',  '\0', '\0', '\0', '\0',		/* 08 */
	'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',		/* 10 */
	'o',  'p',  '\0', '\0', '\n', '\0', 'a',  's',		/* 18 */
	'd',  'f',  'g',  'h',  'j',  'k',  'l',  '\0',		/* 20 */
	'\0', '\0', '\0', '\0', 'z',  'x', 'c',  'v',		/* 28 */
	'b',  'n',  'm',  '\0', '\0', '\0', '\0', '\0',		/* 30 */
	'\0', ' ',  '\0', '\0', '\0', '\0', '\0', '\0',		/* 38 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 40 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 48 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 50 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 58 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 60 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 68 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0',		/* 70 */
	'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'		/* 78 */
};

void bufferhandler(uint8_t c) {
	if (!(c&0x80)) {			// key press
		if (keymap[c] != '\0') {
			key_buffer[write_pos++] = keymap[c];
			sys_putchar(keymap[c]);
		} else {
			sys_puthex(c);
		}
	}

	return;
}

char getchar(void) {
	if (write_pos > read_pos) {
		return key_buffer[read_pos++];
	} else {
		return 0;
	}
}

void keyboardhandler(void) {
    uint8_t a, c;

    __asm__ volatile (
        "    pusha"
        : /* no output */
        : /* no input */
        : /* no globber */);

    c = inb(0x60);              /* get key data */
    a = inb(0x61);              /* get keyboard control */
    outb(a & 0x80, 0x61);
    outb(a, 0x61);
    outb(0x20, 0x20);

	bufferhandler(c);

    __asm__ volatile (
        "    popa\n"
        "    leave\n"
        "    iretw"
        : /* no output */
        : /* no input */
        : /* no globber */);

	return;
}
