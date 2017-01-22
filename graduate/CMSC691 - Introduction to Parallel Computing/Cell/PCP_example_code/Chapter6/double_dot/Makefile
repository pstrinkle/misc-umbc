PROJ=double_dot

PCC=ppu-gcc
CFLAGS=-g -Wall -mno-string -mno-multiple
THREAD_LIB=-lpthread

$(PROJ): $(PROJ).c
	$(PCC) $(CFLAGS) -o $@ $^ $(THREAD_LIB)
	
.PHONY: clean

clean:
	rm $(PROJ) 