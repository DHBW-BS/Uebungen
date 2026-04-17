static void floppy_read(char *buffer, int sector, int track, int head, int drive) {
	int ax, cx, dx;
	int command, ndata;

	command = 2;
	ndata = 1;

	ax = (command << 8) | ndata;
	cx = (track << 8) | sector;
	dx = (head << 8) | drive;

	asm volatile (
		"    int  $0x13"
		: /* no output */
		: "b"(buffer), "a"(ax), "c"(cx), "d"(dx)
		: "memory");

	return;
}

static void floppy_reset(void) {
	asm volatile (				/* reset floppy controller */
		"    mov  $0x00, %%ah\n"
		"    int  $0x13"
		: /* no output */
		: /* no input */
		: "%ax", "%dx");

	return;
}
