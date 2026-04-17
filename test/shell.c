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
		halt();
	} else {
		print(cmd);
		print(" not found\r\n");
	}

	return;
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
