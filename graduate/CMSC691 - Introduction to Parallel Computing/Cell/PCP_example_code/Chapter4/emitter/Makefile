PROJ=eread

CC=gcc
CFLAGS=-g -Wall

$(PROJ): $(PROJ).c $(SYSTEMSIM_TOP)/emitter/emitter_reader.c
	$(CC) $(CFLAGS) -o $@ $^ -I$(SYSTEMSIM_TOP)/include
	
.PHONY: clean

clean:
	rm $(PROJ) 