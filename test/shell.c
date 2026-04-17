#include <system.h>

#define ATTR_VOLUMELABEL	0x08
#define ATTR_ARCHIVE		0x20

typedef struct FAT_ENTRY {
	uint8_t		filename[11];
	uint8_t		attr;
	uint8_t		lcase;
	uint8_t		ctime_cs;
	uint16_t	ctime;
	uint16_t	cdate;
	uint16_t	adate;
	uint16_t	starthi;
	uint16_t	mtime;
	uint16_t	mdate;
	uint16_t	start;
	uint32_t	size;
} __attribute__((packed)) FAT_ENTRY_t;

void dump_floppy(uint32_t addr);
void dump_mem(uint32_t addr);
char *itoa(char*, int);
void load(char *name, uint32_t addr);
uint32_t search(char*);
int strcmp(const char*, const char*);
char *strncpy(char*, const char*, int);
int strncmp(const char*, const char*, int);

void dir(char *buffer) {
	struct FAT_ENTRY *entry;
	static char s[32];

	int n, b, used;

	n = 0;
	used = 0;

	entry = (struct FAT_ENTRY *)buffer;
	while (entry->attr != 0) {
		if (entry->attr & ATTR_VOLUMELABEL) {
			print("\r\n");
			print(" Volume in drive A is ");
			strncpy(s, (char*)entry->filename, 8);
			s[8] = 0;
			print(s);
			print("\r\n");
			print(" Volume Serial Number is ");
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
			b = entry->size;							/* file size */
			used = used + b;
			print(itoa(s, b));
			b = entry->mdate & 0x001f;					/* day */
			print(" ");
			print(itoa(s, b));
														/* month */
														/* year */
			print("\r\n");

			n++;
		}

		buffer = buffer + 32;
		entry = (struct FAT_ENTRY *)buffer;
	}

	print("        ");
	print(itoa(s, n));
	print(" files");
	print("        ");
	print(itoa(s, used));
	print(" bytes\r\n");

	print("        ");
	print(" bytes free\r\n");


	return;
}

void dump_floppy(uint32_t addr) {
	return;
}

void dump_mem(uint32_t addr) {
	return;
}

void execute(char *cmd) {
	static char buffer[512];

	if (strcmp(cmd, "start") == 0) {
		print("CMD: start\r\n");
	} else if (strcmp(cmd, "dir") == 0) {
		print("CMD: dir\r\n");
		floppy_reset();
		floppy_read(buffer, 2, 0, 1, 1);
		dir(buffer);
	} else if (strcmp(cmd, "halt") == 0) {
		print("CMD: halt\r\n");
		halt();
	} else if (strncmp(cmd, "load ", 5) == 0) {
		print("CMD: load\r\n");
		load(cmd+5, 0x4100);
	} else {
		print(cmd);
		print(" not found\r\n");
	}

	return;
}

char *itoa(char *dest, int src) {
	int i, n;

	if (src == 0) {
		dest[0] = '0';
		dest[1] = 0;
	} else {
		n=0;
		dest[n] = 0;

		while (src > 0) {
			for (i=++n; i>0; i--) {
				dest[i] = dest[i-1];
			}
			dest[0] = (src%10)+0x30;
			src = src/10;
		}
	}

	return dest;
}

void load(char *name, uint32_t addr) {
	search(name);

	return;
}

uint32_t search(char *name) {
	struct FAT_ENTRY *entry;
	static char s[32];
	static char buffer[512];
	char *pbuffer;

	print("search ");
	print(name);
	print("\r\n");

	floppy_reset();
	floppy_read(buffer, 2, 0, 1, 1);

	pbuffer = buffer;
	entry = (struct FAT_ENTRY *)pbuffer;
	while (entry->attr != 0) {
		if (entry->attr & ATTR_ARCHIVE) {
			strncpy(s, (char*)entry->filename, 8);
			s[8] = 0;
			if (strcmp(name, s) == 0) {
				break;
			}
		}

		pbuffer = pbuffer + 32;
		entry = (struct FAT_ENTRY *)pbuffer;
	}

	print("name");
	print(s);
	print("\r\n");
	print("addr\r\n");
	print("size\r\n");

	return 0;
}

void shell(void) {
	static char s[80];
	char c;

	int i = 0;
	s[0] = '\0';

	print("c:> ");
	while (1) {
		if ((c = getchar())) {
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

int strncmp(const char *s1, const char *s2, int n) {
	int rc = 0;
	int i;

	for (i=0; i<n; i++) {
		if (s1[i] != s2[i]) {
			rc = -1;
			break;
		} else if (s1[i] == '\0') {
			break;
		}
	}

	return rc;
}

char *strncpy(char *dest, const char * src, int n) {
	int i;
	for (i=0; i<n; i++) {
		dest[i] = src[i];
	}
	return dest;
}
