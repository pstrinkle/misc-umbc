PROJ=fbcheck

PCC=ppu-gcc
CFLAGS=-Wall

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) -o $@ $^ $(CFLAGS)
	
.PHONY: clean

clean:
	rm ppu_$(PROJ)