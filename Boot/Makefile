AS = nasm

all:	boot.flp keyboard.flp

boot.flp:	boot.asm
	$(AS) -o $@ $<

keyboard.flp:	keyboard.asm
	$(AS) -o $@ $<

clean:
	rm -f boot.flp keyboard.flp