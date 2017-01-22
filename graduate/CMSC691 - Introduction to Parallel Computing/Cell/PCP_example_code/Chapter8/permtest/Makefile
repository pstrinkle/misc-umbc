PROJ=permtest

PCC=ppu-gcc
CFLAGS=-g -Wall -mno-string -mno-multiple -maltivec -mabi=altivec

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) $(CFLAGS) -o $@ $^
	
.PHONY: clean

clean:
	rm ppu_$(PROJ) 