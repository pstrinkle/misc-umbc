PROJ=rect2polar

SCC=spu-gcc
LIBS=-lmassv

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ $(LIBS)
	
.PHONY: clean

clean:
	rm spu_$(PROJ)