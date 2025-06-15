PRGS = hello

CFLAGS = -Wall -O2 -fno-asynchronous-unwind-tables

all:	$(PRGS)

hello.s:	hello.c
		$(CC) $(CFLAGS) -S $<

clean:
		rm -f $(PRGS)
		rm -f hello.s