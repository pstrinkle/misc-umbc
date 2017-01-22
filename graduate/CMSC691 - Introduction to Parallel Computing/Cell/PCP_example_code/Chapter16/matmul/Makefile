PROJ=matmul

SCC=spu-gcc
CFLAGS=-Wall

MATRIX_DIR=/opt/cell/sdk/src/lib/matrix
MATRIX_LIB=-lmatrix
     
spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ -I$(MATRIX_DIR) -L$(MATRIX_DIR)/spu $(CFLAGS) $(MATRIX_LIB)
	
.PHONY: clean

clean:
	rm spu_$(PROJ) 