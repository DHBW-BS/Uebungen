#include <system.h>

char keymap[] = {
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

uint8_t inb(uint16_t port) {
	uint8_t v;
	__asm__ volatile (
		"inb %1, %0"
		: "=a" (v)
		: "dN" (port)
		: /* no globber */);
	return v;
}

void outb(uint8_t v, uint16_t port) {
	__asm__ volatile (
		"outb %0, %1"
		: /* no output */
		: "a" (v), "dN" (port)
		: /* no globber */);
}

void printHex16(uint16_t n) {
    char hexstring[] = "0123456789ABCDEF";
    char outstring[] = "  ";
	int i;

    for (i=0; i<2;i++) {
        outstring[1-i] = hexstring[n&0x0f];
    	n = n >> 4;
    }
    print(outstring);

    return;
}

void keyboardhandler(void) {
    uint8_t a, c;

    __asm__ volatile (
        "    pusha"
        : /* no output */
        : /* no input */
        : /* no globber */);

    c = inb(0x60);                  /* get key data */
    a = inb(0x61);                  /* get keyboard control */
    outb(a & 0x80, 0x61);
    outb(a, 0x61);
    outb(0x20, 0x20);

	if (!(c&0x80)) {			    /* key press */
        printHex8(c);               /* print key code */
        print("  ");
        printHex16(c);
        print("  ");
        printHex8(keymap[c]);
        print("  ");
        print(keymap[c & 0xff]);
        print("\n\r");
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

void registerinterrupt(int irq, void* handler) {
    print("Register Interrupt Handler\n\r");

    __asm__ volatile (
        "    cli\n"                      /* disable interrupts */
        "    shl $2, %%bx\n"             /* each entry is 4 bytes */
        "    xor %%ax, %%ax\n"           /* clear ax */
        "    mov %%gs, %%ax\n"           /* IVT base address is 0 */
        "    mov %%cx, %%gs:(%%bx)\n"    /* store handler address in IRQ vector */
        "    mov %%ds, %%gs:2(%%bx)\n"   /* store segment register in IRQ vector */
        "    sti"                        /* enable interrupts */
        : /* no output */
        : "bx"(irq), "cx"(handler)
        : "%ax");

    return;
}

void printHex8(uint8_t n) {
    char hexstring[] = "0123456789ABCDEF";
    char outstring[] = "  ";
	int i;

    for (i=0; i<2;i++) {
        outstring[1-i] = hexstring[n&0x0f];
    	n = n >> 4;
    }
    print(outstring);

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

    return 0;
}