PROJ=alf_simple

PCC=ppu-gcc
CFLAGS=-Wall
LIBS=-lalf -lspe2 -ldl

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) -o $@ $^ $(CFLAGS) $(LIBS)
	
.PHONY: clean

clean:
	rm ppu_$(PROJ)