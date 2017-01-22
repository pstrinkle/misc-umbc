PROJ=rotate

SCC=spu-gcc
CFLAGS=-Wall

MATRIX_DIR=/opt/cell/sdk/src/lib/matrix
MATRIX_LIB=-lmatrix

VECTOR_DIR=/opt/cell/sdk/src/lib/vector
VECTOR_LIB=-lvector
     
spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^ -I$(MATRIX_DIR) -I$(VECTOR_DIR) -L$(MATRIX_DIR)/spu -L$(VECTOR_DIR)/spu $(CFLAGS) $(MATRIX_LIB) $(VECTOR_LIB)
	
.PHONY: clean

clean:
	rm spu_$(PROJ) 