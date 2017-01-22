PROJ=fbmulti

PCC=ppu-gcc
CFLAGS=-O3 -Wall

LIBS=-lm

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) -o $@ $^ -I$(PS3FB_DIR) $(CFLAGS) $(LIBS)
	
.PHONY: clean

clean:
	rm ppu_$(PROJ)