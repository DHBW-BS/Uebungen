AS = nasm

all:	boot.flp

boot.flp:	boot.asm
	$(AS) -o $@ $<

clean:
	rm -f boot.flp