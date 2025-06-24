SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)
PRG  = sched

CFLAGS  = -Wall -lpthread

all:	$(OBJS)
	$(CC) $(CFLAGS) -o $(PRG) $(OBJS)

clean:
	rm -f $(PRG) $(OBJS)
