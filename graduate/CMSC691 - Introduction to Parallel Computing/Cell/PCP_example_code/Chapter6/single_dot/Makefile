PROJ=single_dot

PCC=ppu-gcc
CFLAGS=-g -Wall -mno-string -mno-multiple

$(PROJ): $(PROJ).c
	$(PCC) $(CFLAGS) -o $@ $^
	
.PHONY: clean

clean:
	rm $(PROJ) 