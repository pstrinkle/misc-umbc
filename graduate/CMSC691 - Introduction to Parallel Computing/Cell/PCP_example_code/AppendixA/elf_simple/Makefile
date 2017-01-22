PROJ=elf_simple

PCC=ppu-gcc
CFLAGS=-Wall

$(PROJ): $(PROJ).c
	$(PCC) $(CFLAGS) -o $@ $^ /usr/lib64/libelf.so.1
	
.PHONY: clean

clean:
	rm $(PROJ)