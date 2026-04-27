#include <system.h>

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
