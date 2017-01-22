PROJ=overlay

PCC=ppu-gcc
SCC=spu-gcc
EMBED=ppu-embedspu
PROC_TYPE=-m64
CFLAGS=-Wall
LIBS=-lspe2
OFILE1 = overlay1
OFILE2 = overlay2

LD_NAME = ld.script
LD_FLAGS = -Wl,-T,$(LD_NAME)

ppu_$(PROJ): ppu_$(PROJ).c spu_$(PROJ).o
	$(PCC) -o $@ $^ -I$(MISC_DIR) $(CFLAGS) $(LIBS)
     
spu_$(PROJ).o: spu_$(PROJ)
	$(EMBED) $(PROC_TYPE) spu_$(PROJ) spu_$(PROJ) $@
     
spu_$(PROJ): spu_$(PROJ).c $(OFILE1).o $(OFILE2).o
	$(SCC) $(LD_FLAGS) -o $@ $^

$(OFILE1).o: $(OFILE1).c
	$(SCC) -c -o $@ $^
   
$(OFILE2).o: $(OFILE2).c
	$(SCC) -c -o $@ $^

.PHONY: clean

clean:
	rm *.o ppu_$(PROJ) spu_$(PROJ) 