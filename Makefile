PROGRAM = chexdump
VERSION	= 1.0.0
FILES	= src/main.c src/hexprint.c
OBJS	= $(FILES:.c=.o)
CFLAGS	= -O2 -pipe
LDFLAGS	= 
SHELL	= /bin/sh
.SUFFIXES:
.SUFFIXES: .c .o

all: $(PROGRAM)

$(PROGRAM): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm $(PROGRAM) $(OBJS)

dist:
	mkdir $(PROGRAM)-$(VERSION)
	ln -t $(PROGRAM)-$(VERSION) Makefile $(FILES)
	tar cjvf $(PROGRAM)-$(VERSION).tar.bz2 $(PROGRAM)-$(VERSION)
	rm -r $(PROGRAM)-$(VERSION)
