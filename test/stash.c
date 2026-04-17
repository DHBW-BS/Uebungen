asm (
	".code16gcc\n"
	".align 4\n"
	"call kernel\n"
//
	".align 4\n"
	"hang:\n"
	"jmp hang\n");

#include "kernel.h"

void buffer_add(uint8_t c) {
	if (!(c&0x80)) {			// key press
		if (keymap[c] != '\0') {
			key_buffer.s[key_buffer.w_pos] = keymap[c];
			putchar(key_buffer.s[key_buffer.w_pos]);
			key_buffer.w_pos = (key_buffer.w_pos + 1) % BUFFERSIZE;
		}
	}

	return;
}

void dir(void) {
	static char buffer[512];
	char *p;
	struct FAT_BS *bs;
	struct FAT_BSEXT *bsext;
	struct FAT_ENTRY *entry;
	static char s[32];
	int serial_1, serial_2;
	int n, b, free, used;

	floppy_reset();
	floppy_read(buffer, 1, 0, 0, 1);

	p = buffer;
	bs = (struct FAT_BS *)p;
	n = 5;		/* number of files needs to be fixed */
	free = bs->total_sectors_16 * bs->bytes_per_sector
	       - (bs->table_size_16 * bs->table_count + 1) * bs->bytes_per_sector	// Boot Sector + FATs
	       - n * bs->bytes_per_sector											// one sector per file
	       - bs->root_entry_count * 32;											// directory entries

	p = buffer+36;
	bsext = (struct FAT_BSEXT *)p;
	serial_1 = (bsext->serial & 0xffff0000)/0x10000;
	serial_2 = bsext->serial & 0xffff;
	floppy_reset();
	floppy_read(buffer, 2, 0, 1, 1);

	n = 0;
	used = 0;

	p = buffer;
	entry = (struct FAT_ENTRY *)p;

	while (entry->attr != 0) {
		if (entry->attr & ATTR_VOLUMELABEL) {
			print("\r\n");
			print(" Volume in drive A is ");
			strncpy(s, (char*)entry->filename, 8);
			s[8] = 0;
			print(s);
			print("\r\n");
			print(" Volume Serial Number is ");
			puthex((serial_1 >> 8) & 0x00ff);
			puthex(serial_1 & 0x00ff);
			print("-");
			puthex((serial_2 >> 8) & 0x00ff);
			puthex(serial_2 & 0x00ff);
			print("\r\n");
			print(" Directory of A:\\");
			print("\r\n");
			print("\r\n");
		} else if (entry->attr & ATTR_ARCHIVE) {
			strncpy(s, (char*)entry->filename, 8);
			s[8] = 0;
			print(s);
			print(" ");
			strncpy(s, (char*)entry->filename+8, 3);
			s[3] = 0;
			print(s);
			print("            ");
			b = entry->size;								// file size
			used = used + b;
			print(itoa(b));
			b = entry->mdate & 0x001f;						// day
			print(" ");
			if (b<10) print("0");
			print(itoa(b));
			b = (entry->mdate & 0x1e0) / 32;				// month
			print(".");
			if (b<10) print("0");
			print(itoa(b));
			b = (80 + (entry->mdate & 0xf700) / 512)%100;	// year
			print(".");
			if (b<10) print("0");
			print(itoa(b));
			print("   ");
			b = (entry->mtime & 0xf800) / 2048;				// hour
			if (b<10) print("0");
			print(itoa(b));
			print(":");
			b = (entry->mtime & 0x07e0) / 32;				// minute
			if (b<10) print("0");
			print(itoa(b));
			print("\r\n");

			n++;
		}

		p = p + 32;
		entry = (struct FAT_ENTRY *)p;
	}

	print("        ");
	print(itoa(n));
	print(" file(s)");
	print("        ");
	print(itoa(used));
	print(" bytes\r\n");

	print("        ");
	print(itoa(free));
	print(" bytes free\r\n");

	return;
}

void execute(char *cmd) {
	if (strcmp(cmd, "start") == 0) {
		print("CMD: start\r\n");
	} else if (strcmp(cmd, "dir") == 0) {
		print("CMD: dir\r\n");
		dir();
	} else if (strcmp(cmd, "halt") == 0) {
		print("CMD: halt\r\n");
		systemhalt();
	} else {
		print(cmd);
		print(" not found\r\n");
	}

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

char getchar(void) {
	char c;

	if (key_buffer.w_pos != key_buffer.r_pos) {
		c = key_buffer.s[key_buffer.r_pos];
		key_buffer.r_pos = (key_buffer.r_pos + 1) % BUFFERSIZE;
		return c;
	} else {
		return 0;
	}
}

static inline uint8_t inb(uint16_t port) {
	uint8_t v;
	asm volatile (
		"inb %1, %0"
		: "=a" (v)
		: "dN" (port));
	return v;
}

char *itoa(int src) {
	char *digit = "0123456789";
	static char dst[32];
	int i, n;

	if (src == 0) {
		dst[0] = '0';
		dst[1] = 0;
	} else {
		n = 0;
		dst[0] = 0;

		while (src > 0) {
			for (i=++n; i>0; i--) {
				dst[i] = dst[i-1];
			}
			dst[0] = *(digit + src%10);
			src = src/10;
		}
	}

	return dst;
}

int kernel(void) {
	print("starting kernel ...\r\n");

	registerinterrupt(9, keyboardhandler);

	shell();

	print("exit kernel\r\n");

	return 0;
}

void keyboardhandler(void) {
	char a, c;

	asm volatile (
		"    pusha"
		: /* no output */
		: /* no input */);

	c = inb(0x60);
	a = inb(0x61);
	outb(a & 0x80, 0x61);
	outb(a, 0x61);
	outb(0x20, 0x20);

	buffer_add(c);

	asm volatile (
		"    popa\n"
		"    leave\n"
		"    iretw"
		: /* no output */
		: /* no input */);

	return;
}

static inline void outb(uint8_t v, uint16_t port) {
	asm volatile (
		"outb %0, %1"
		: /* no output */
		: "a" (v), "dN" (port));
}

static void print(char *s) {
	char *c;

	while (*(c = s++) != 0) {
		putchar(*c);
	}

	return;
}

static void putchar(char c) {
	asm volatile (
		"    mov  %0, %%al\n"
		"    mov  $0x0e, %%ah\n"
		"    int  $0x10"
		: /* no output */
		: "d" (c)
		: "ax");

	return;
}

static void puthex(uint8_t i) {
	char *s = "0123456789ABCDEF";
	char c;

	c = *(s + (i >> 4 & 0x0f));
	putchar(c);
	c = *(s + (i & 0x0f));
	putchar(c);

	return;
}

void registerinterrupt(int irq, void *handler) {
	print("register interrupt handler\n\r");

	asm volatile (
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

void shell(void) {
	static char s[80];
	char c;

	int i = 0;
	s[0] = '\0';

	print("c:> ");
	while (1) {
		if (key_buffer.w_pos != key_buffer.r_pos) {
			c = getchar();
			if (c == '\n') {
				print("\r");
				execute(s);
				s[0] = '\0';
				i = 0;
				print("c:> ");
			} else {
				s[i++] = c;
				s[i] = '\0';
			}
		}
	}

	print("exit shell\r\n");

	return;
}

int strcmp(const char *s1, const char *s2) {
	char c;
	int rc = 0;
	int i=0;

	while((c = s1[i]) != '\0') {
		if (s2[i] == '\0') {
			rc = -1;
			break;
		} else if (s2[i] != c) {
			rc = -1;
			break;
		}
		i++;
	}

	if (s2[i] != '\0') {
		rc = 1;
	}

	return rc;
}

char *strncpy(char *dest, const char *src, int n) {
	int i;
	for (i=0; i<n; i++) {
		dest[i] = src[i];
	}
	return dest;
}

void systemhalt(void) {
	print("system halted\n\r");

	asm volatile (
		"cli\n"
		"hlt"
		: /* no output */
		: /* no input */);

	return;
}
