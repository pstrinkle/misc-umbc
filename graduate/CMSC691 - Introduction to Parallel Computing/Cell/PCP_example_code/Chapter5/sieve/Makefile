PROJ=sieve

SCC=spu-gcc
CFLAGS=-g -Wall

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) $(CFLAGS) -o $@ $^
	
.PHONY: clean

clean:
	rm spu_$(PROJ) 