PROJ=dectest

SCC=spu-gcc
CFLAGS=-O3
LIBS=-lmassv -lsimdmath

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) $(CFLAGS) -o $@ $^ $(LIBS)
	
.PHONY: clean

clean:
	rm spu_$(PROJ)