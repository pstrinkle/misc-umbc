PROJ=addlarge

SCC=spu-gcc

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) -o $@ $^
	
.PHONY: clean

clean:
	rm spu_$(PROJ)