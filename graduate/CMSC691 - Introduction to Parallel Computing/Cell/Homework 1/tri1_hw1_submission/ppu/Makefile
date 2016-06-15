PROJ=only

PCC=ppu-gcc
EMBED=ppu-embedspu
PROC_TYPE=-m64
CFLAGS=-Wall

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -rf *.o *~ ppu_$(PROJ)
