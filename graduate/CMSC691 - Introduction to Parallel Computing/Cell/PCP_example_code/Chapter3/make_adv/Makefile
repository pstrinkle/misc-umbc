# Create variables
FILE=a
PCC=ppu-gcc
SCC=spu-gcc

# Tell make to build both applications
all: ppu_$(FILE) spu_$(FILE)

# Build the PPU executable
ppu_$(FILE): $(FILE).o
	$(PCC) $^ -o $@ 
   
# Build the SPU executable
spu_$(FILE): $(FILE).c
	$(SCC) $^ -o $@ 
	
.PHONY: clean

clean:
	rm *.o