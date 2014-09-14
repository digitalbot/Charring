CC				= clang
CFLAGS			= -O4 -I/usr/local/include -Wall
DEST			= /usr/local/bin
LDFLAGS			= -L/usr/local/lib

TARGETS			= t_new_charring bobobo

all:				$(TARGETS)
.SUFFIXES: 		.c .o

t_new_charring:	t_new_charring.o charring.o
					$(CC) -o $@ $^

bobobo:			bobobo.o charring.o
					$(CC) -o $@ $^

.c.o:
					$(CC) $(CFLAGS) -c $<

charring.o:			../charring.c
					$(CC) $(CFLAGS) -c $<

.PHONY:			test

test:
					make all && for f in $(TARGETS); do ./$$f; done;

.PHONY:			clean

clean:
					$(RM) *.o *- $(TARGETS)
