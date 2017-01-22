PROJ=spu_shright

AS=spu-as
SCC=spu-gcc

AS_FLAGS=--gdwarf-2
SCC_FLAGS=-nostartfiles -Wl,-Ttext=0x0

$(PROJ): $(PROJ).o
	$(SCC) -o $@ $^ $(SCC_FLAGS)
     
$(PROJ).o: $(PROJ).s
	$(AS) -o $@ $^ $(AS_FLAGS)

.PHONY: clean

clean:
	rm *.o $(PROJ)