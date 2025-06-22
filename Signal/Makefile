SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)
PRG  = pi

CFLAGS  = -Wall
LDFLAGS = -lm

all:	$(OBJS)
	$(CC) $(CFLAGS) -o $(PRG) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(PRG) $(OBJS)
