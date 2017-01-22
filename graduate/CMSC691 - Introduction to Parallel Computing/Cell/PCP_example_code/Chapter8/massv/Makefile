PROJ=massv

PCC=ppu-gcc
CFLAGS=-g -Wall -mno-string -mno-multiple -maltivec
MASSV_LIB=-lmassv_64

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) $(CFLAGS) -o $@ $^ $(MASSV_LIB)
	
.PHONY: clean

clean:
	rm ppu_$(PROJ) 