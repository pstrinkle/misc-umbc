PROJ=host_matrix

PCC=ppu-gcc
SCC=spu-gcc
CFLAGS=-Wall
PPU_LIBS=-lalf -lspe2 -ldl

SPU_LIBS=-L/usr/spu/lib -lalf
EMBED=ppu-embedspu
PROC_TYPE=-m64
PPU_LD=ppu-ld
SHARED=-shared

all: ppu_$(PROJ) spu_$(PROJ).so

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) -o $@ $^ $(CFLAGS) $(PPU_LIBS)
   
spu_$(PROJ).so: spu_$(PROJ).o
	$(PPU_LD) $(SHARED) -o $@ $^

spu_$(PROJ).o: spu_$(PROJ)
	$(EMBED) $(PROC_TYPE) spu_$(PROJ) spu_$(PROJ) $@
     
spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ $(CFLAGS) $(SPU_LIBS)
   
.PHONY: clean

clean:
	rm ppu_$(PROJ) spu_$(PROJ) spu_$(PROJ).so spu_$(PROJ).o
   
