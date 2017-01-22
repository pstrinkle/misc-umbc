CC=ppu-gcc

AR=ppu-ar
ARFLAGS=rcs

LIB=-lsimple
LIBPATH=.

all: libsimple.a libcall

libcall: libcall.c
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBPATH) $(LIB)

libsimple.a: hello.o goodbye.o
	$(AR) $(ARFLAGS) $@ $^
	
.PHONY: clean

clean:
	rm hello.o goodbye.o libsimple.a libcall