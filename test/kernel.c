#include <system.h>

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

    printHex8(c);               /* print key code */
    print("\n\r");

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
    shell();
    halt();

    return 0;
}