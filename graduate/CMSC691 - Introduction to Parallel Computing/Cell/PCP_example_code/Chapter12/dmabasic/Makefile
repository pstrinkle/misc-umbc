PROJ=dmabasic

PCC=ppu-gcc
SCC=spu-gcc
EMBED=ppu-embedspu
PROC_TYPE=-m64
CFLAGS=-Wall
LIBS=-lspe2

MISC_DIR=/opt/ibm/cell-sdk/prototype/src/lib/misc

ppu_$(PROJ): ppu_$(PROJ).c spu_$(PROJ).o
	$(PCC) -o $@ $^ -I$(MISC_DIR) $(CFLAGS) $(LIBS)
     
spu_$(PROJ).o: spu_$(PROJ)
	$(EMBED) $(PROC_TYPE) spu_$(PROJ) spu_$(PROJ) $@
     
spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^
	
.PHONY: clean

clean:
	rm *.o ppu_$(PROJ) spu_$(PROJ) 