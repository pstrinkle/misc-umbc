PROJ=cashier
PROC_TYPE=-m64

PCC=ppu-gcc
SCC=spu-gcc
EMBED=ppu-embedspu
CFLAGS=-Wall
PPU_LIBS=-lspe2 -lsync
SPU_LIBS=-lsync
PPU_INCDIR=/opt/cell/sdk/usr/include
PPU_LIBDIR=/opt/cell/sdk/src/lib/sync/ppu64
SPU_INCDIR=/opt/cell/sdk/usr/spu/include
SPU_LIBDIR=/opt/cell/sdk/src/lib/sync/spu

ppu_$(PROJ): ppu_$(PROJ).c spu_$(PROJ).o
	$(PCC) $(CFLAGS) -o $@ $^ -I$(PPU_INCDIR) -L$(PPU_LIBDIR) $(PPU_LIBS) 
     
spu_$(PROJ).o: spu_$(PROJ)
	$(EMBED) $(PROC_TYPE) spu_$(PROJ) spu_$(PROJ) $@
     
spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ -I$(SPU_INCDIR) -L$(SPU_LIBDIR) $(SPU_LIBS)

.PHONY: clean

clean:
	rm *.o ppu_$(PROJ) spu_$(PROJ) 