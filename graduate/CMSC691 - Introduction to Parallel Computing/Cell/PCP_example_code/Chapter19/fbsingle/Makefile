PROJ=fbsingle

PCC=ppu-gcc
CFLAGS=-O3 -Wall

LIBS=-lm

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) -o $@ $^ $(CFLAGS) $(LIBS)
	
.PHONY: clean

clean:
	rm ppu_$(PROJ)