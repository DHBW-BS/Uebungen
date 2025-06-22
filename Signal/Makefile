SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)
PRG  = pi

CFLAGS  = -Wall -lm

all:	$(OBJS)
	$(CC) $(CFLAGS) -o $(PRG) $(OBJS)

clean:
	rm -f $(PRG) $(OBJS)
