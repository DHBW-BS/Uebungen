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

void registerinterrupt(int irq, void* handler) {
    print("Register Interrupt Handler\n\r");

    __asm__ volatile (
        "    cli\n"
        "    shl $2, %%bx\n"
        "    xor %%ax, %%ax\n"
        "    mov %%gs, %%ax\n"
        "    mov %%cx, %%gs:(%%bx)\n"
        "    mov %%ds, %%gs:2(%%bx)\n"
        "    sti"
        : /* no output */
        : "bx"(irq), "cx"(handler)
        : "%ax");

    return;
}
