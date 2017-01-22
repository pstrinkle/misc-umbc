PROJ=polar

PCC=ppu-gcc
CFLAGS=-g -Wall -mno-string -mno-multiple -maltivec
LIBS=-lmassv_64

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) $(CFLAGS) -o $@ $^ $(LIBS)
	
.PHONY: clean

clean:
	rm ppu_$(PROJ) 