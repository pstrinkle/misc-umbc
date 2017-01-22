CC=ppu-gcc
CFLAGS=-Wall
FPIC=-c -fPIC

LIB=libsimple
DYNFLAGS=-shared -Wl,-soname,$(LIB).so.1

LINK=ln
LINK_FLAGS=-sf

LIBNAME=simple
LIBPATH=.

all: libsimple.so libcall

libcall: libcall.c
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBPATH) -R$(LIBPATH) -l$(LIBNAME)

$(LIB).so: $(LIB).so.1
	$(LINK) $(LINK_FLAGS) $^ $@

$(LIB).so.1: $(LIB).so.1.0.1
	$(LINK) $(LINK_FLAGS) $^ $@
   
$(LIB).so.1.0.1: hello.o goodbye.o
	$(CC) $(CFLAGS) $(DYNFLAGS) -o $@ $^

hello.o goodbye.o: hello.c goodbye.c
	$(CC) $(CFLAGS) $(FPIC) $^
   
.PHONY: clean

clean:
	rm hello.o goodbye.o $(LIB).so $(LIB).so.1 $(LIB).so.1.0.1 libcall