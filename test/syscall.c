#include <system.h>

void syscall(void) {
	uint16_t ds;
	uint32_t nr, edx;
	int irq = 0x21;

	__asm__ volatile (
		""
		: "=a"(nr), "=d"(edx)
		: /* no input */
		: /* no globber */);

	__asm__ volatile (
		"    shl $2, %%bx\n"
		"    mov %%ax, %%gs\n"
		"    mov %%ds, %%ax\n"
		"    mov %%gs:2(%%bx), %%ds"
		: "=a"(ds)
		: "ax"(0), "bx"(irq)
		: /* no globber */);

	print("System Call\n\r");

	if ((nr & 0xff00) == 0x0900) {
		syscall_09_write(ds-0x1000, (uint16_t)(edx & 0xffff));
	} else if ((nr & 0xff00) == 0x4c00) {
		syscall_4C_exit();
	}

	__asm__ volatile (
		"    mov %%ax, %%ds\n"
		"    mov $0x41, %%al\n"
		"    mov $0x0e, %%ah\n"
		"    int $0x10\n"
		"    mov  $0x20, %%al\n"
		"    out  %%al, $0x20\n"
		"    leave\n"
		"    iretw"
		: /* no output */
		: "ax"(ds)
		: /* no globber */);

	return;
}

/* 09 - WRITE STRING TO STANDARD OUTPUT */
void syscall_09_write(uint16_t ds, uint16_t dx) {
	char *p;
	char s;

	p = (char*)(uint16_t*)((ds << 4) + dx);
	while ((s=*p) != '$') {
		putchar(s);
		p++;
	}

	return;
}

/* 4C - EXIT - TERMINATE WITH RETURN CODE */
void syscall_4C_exit(void) {
	/* enable interrupts */

	/* should we worry about the stack ? */

	__asm__ volatile (
		"    mov  $0x20, %%al\n"
		"    out  %%al, $0x20\n"
		"    leave"
		: /* no output */
		: /* no input */
		: /* no globber */);

	/* reenable interrupts */
	enable_irq();

	/* return to shell */
	shell();

	return;
}
