PROJ=libfft

PCC=ppu32-gcc
CFLAGS=-Wall -m32 -Wl,-m,elf32ppc -maltivec -mabi=altivec

FFT_DIR=/opt/cell/sdk/prototype/usr
FFT_LIB=-lfft
MATH_LIB=-lm
SPE_LIB=-lspe2

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) $(CFLAGS) -o $@ $^ -I$(FFT_DIR)/include -L$(FFT_DIR)/lib -R$(FFT_DIR)/lib $(MATH_LIB) $(SPE_LIB) $(FFT_LIB)
	
.PHONY: clean

clean:
	rm ppu_$(PROJ) 