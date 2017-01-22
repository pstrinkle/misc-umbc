PROJ=spu_addreg

AS=spu-as
SCC=spu-gcc

AS_FLAGS=--gdwarf-2
SCC_FLAGS=-nostartfiles

$(PROJ): $(PROJ).o
	$(SCC) -o $@ $^ $(SCC_FLAGS)

$(PROJ).o: $(PROJ).s
	$(AS) -o $@ $^ $(AS_FLAGS)

.PHONY: clean

clean:
	rm *.o $(PROJ)