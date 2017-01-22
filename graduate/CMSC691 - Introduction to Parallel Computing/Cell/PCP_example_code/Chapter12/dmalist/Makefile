PROJ=dmalist

PCC=ppu-gcc
SCC=spu-gcc
EMBED=ppu-embedspu
PROC_TYPE=-m64
CFLAGS=-Wall
LIBS=-lspe2

ppu_$(PROJ): ppu_$(PROJ).c spu_$(PROJ).o
	$(PCC) $(CFLAGS) -o $@ $^ $(LIBS)
     
spu_$(PROJ).o: spu_$(PROJ)
	$(EMBED) $(PROC_TYPE) spu_$(PROJ) spu_$(PROJ) $@
     
spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^
	
.PHONY: clean

clean:
	rm *.o ppu_$(PROJ) spu_$(PROJ) 