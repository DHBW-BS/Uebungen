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