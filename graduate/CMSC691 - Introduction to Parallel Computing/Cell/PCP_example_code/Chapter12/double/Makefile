PROJ=double

PCC=ppu-gcc
SCC=spu-gcc
CFLAGS=-Wall -O3
EMBED=ppu-embedspu
PROC_TYPE=-m64
LIBS=-lspe2

ppu_$(PROJ): ppu_$(PROJ).c spu_$(PROJ).o
	$(PCC) $(CFLAGS) -o $@ $^ $(LIBS)
     
spu_$(PROJ).o: spu_$(PROJ)
	$(EMBED) $(PROC_TYPE) spu_$(PROJ) spu_$(PROJ) $@
     
spu_$(PROJ): spu_$(PROJ).c
	$(SCC) $(CFLAGS) -o $@ $^
	
.PHONY: clean

clean:
	rm *.o ppu_$(PROJ) spu_$(PROJ) 