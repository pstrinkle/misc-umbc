PROJ=rsa

SCC=spu-gcc
CFLAGS=-Wall

MPM_DIR=/opt/cell/sdk/usr/spu
MPM_LIB=-lmpm

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ -I$(MPM_DIR)/include -L$(MPM_DIR)/lib $(CFLAGS) $(MPM_LIB)
	
.PHONY: clean

clean:
	rm spu_$(PROJ) 