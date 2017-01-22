PROJ=heaptest

SCC=spu-gcc
CFLAGS=-g -Wall

MISC_DIR=/opt/cell/sdk/usr/spu
MISC_LIB=-lmisc
     
spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ -I$(MISC_DIR)/include -L$(MISC_DIR)/lib $(CFLAGS) $(MISC_LIB)
	
.PHONY: clean

clean:
	rm spu_$(PROJ)