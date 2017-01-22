PROJ=rounding

PCC=ppu-gcc
CFLAGS=-g -Wall -mno-string -mno-multiple -maltivec -mabi=altivec
LIBS=-lsimdmath

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) $(CFLAGS) -o $@ $^ $(LIBS)
	
.PHONY: clean

clean:
	rm ppu_$(PROJ) 