PROJ=spu_caller

AS=spu-as
SCC=spu-gcc

AS_FLAGS=--gdwarf-2
SCC_FLAGS=-nostartfiles -Wl,-Ttext=0x0

$(PROJ): $(PROJ).o spu_func.c
	$(SCC) -g -o $@ $^ $(SCC_FLAGS)

$(PROJ).o: $(PROJ).s
	$(AS) -o $@ $^ $(AS_FLAGS)   
   
.PHONY: clean

clean:
	rm *.o $(PROJ)