PROJ=spu_caller

AS=spu-as
SCC=spu-gcc

AS_FLAGS=--gdwarf-2
SCC_FLAGS=-g

$(PROJ): $(PROJ).c spu_func.o
	$(SCC) -o $@ $^ $(SCC_FLAGS)

spu_func.o: spu_func.s
	$(AS) -o $@ $^ $(AS_FLAGS)
   
.PHONY: clean

clean:
	rm *.o $(PROJ)