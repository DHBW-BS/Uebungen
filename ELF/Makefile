AS = nasm

all:

hello:	hello.c

readelf:	readelf.c

print:	print.asm
	$(AS) -o print.o -f elf64 $<
	$(LD) -o $@ print.o

clean:
	rm -f readelf print hello
	rm -f *.o *.lst