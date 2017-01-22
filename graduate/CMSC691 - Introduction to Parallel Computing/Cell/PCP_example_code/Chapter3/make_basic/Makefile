# Create macros for the source and build tools
FILE=a
PCC=ppu-gcc
SCC=spu-gcc
HDIR=./head_dir

# Tell make to build both applications
all: ppu_$(FILE) spu_$(FILE)

# Build the PPU executable
ppu_$(FILE): $(FILE).c
	$(PCC) -I$(HDIR) $(FILE).c -o ppu_$(FILE)
   
# Build the SPU executable
spu_$(FILE): $(FILE).c
	$(SCC) -I$(HDIR) $(FILE).c -o spu_$(FILE)
