PROJ=prime

PCC=ppu-gcc
AS=spu-as
SCC=spu-gcc
EMBED=ppu-embedspu
PROC_TYPE=-m64
CFLAGS=-Wall
LIBSPE=-lspe2

ppu_$(PROJ): ppu_$(PROJ).c spu_$(PROJ)-embed.o
	$(PCC) -o $@ $^ $(CFLAGS) $(LIBSPE)
     
spu_$(PROJ)-embed.o: spu_$(PROJ)
	$(EMBED) $(PROC_TYPE) spu_$(PROJ)_handle spu_$(PROJ) $@
     
spu_$(PROJ): spu_$(PROJ).c toe.s
	$(SCC) -o $@ $^
   
.PHONY: clean

clean:
	rm *.o ppu_$(PROJ) spu_$(PROJ) 