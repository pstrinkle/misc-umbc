PROJ=random1

SCC=spu-gcc
CFLAGS=-Wall

MPM_DIR=/opt/cell/sdk/prototype/usr/spu
MPM_LIB=-lmc_rand

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ -I$(MPM_DIR)/include -L$(MPM_DIR)/lib $(CFLAGS) $(MPM_LIB)
	
.PHONY: clean

clean:
	rm spu_$(PROJ) 