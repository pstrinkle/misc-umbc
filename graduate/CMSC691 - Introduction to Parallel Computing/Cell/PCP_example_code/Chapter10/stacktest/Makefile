PROJ=stacktest

SCC=spu-gcc
CFLAGS=-g -Wall
     
spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm spu_$(PROJ)