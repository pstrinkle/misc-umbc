PROJ=roundfloat

SCC=spu-gcc
LIBS=-lsimdmath

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ $(LIBS)
	
.PHONY: clean

clean:
	rm spu_$(PROJ)