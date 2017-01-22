PROJ=twodfft

SCC=spu-gcc
CFLAGS=-Wall

FFT_DIR=/opt/cell/sdk/src/lib/fft
FFT_LIB=-lfft_example
MATH_LIB=-lm

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) $(CFLAGS) -o $@ $^ -I$(FFT_DIR) -L$(FFT_DIR)/spu $(FFT_LIB) $(MATH_LIB)
	
.PHONY: clean

clean:
	rm spu_$(PROJ) 