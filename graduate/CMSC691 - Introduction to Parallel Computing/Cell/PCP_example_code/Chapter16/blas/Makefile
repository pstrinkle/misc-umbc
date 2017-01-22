PROJ=blas

SCC=spu-gcc
CFLAGS=-Wall
BLAS_LIB=-lblas

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ -L/usr/spu/lib $(BLAS_LIB)
	
.PHONY: clean

clean:
	rm spu_$(PROJ) 