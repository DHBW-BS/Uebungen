ASFLAGS = -l $(basename $@).lst
AS = nasm

all:	boot.flp

boot.flp:	boot
	dd if=/dev/zero of=boot.flp bs=512 count=2880
	dd if=boot of=boot.flp bs=512 conv=notrunc

kernel.bin:	$(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)

boot:	boot.asm
	$(AS) -l $@.lst -o $@ $<

clean:
	rm -f boot boot.flp
	rm -f *.lst