PROJ=libfft

SCC=spu-gcc
CFLAGS=-Wall

FFT_DIR=/opt/cell/sdk/prototype/usr
SPU_FFT_DIR=$(FFT_DIR)/spu
FFT_LIB=-lfft_spu
MATH_LIB=-lm

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) $(CFLAGS) -o $@ $^ -I$(FFT_DIR)/include -I$(SPU_FFT_DIR)/include -L$(SPU_FFT_DIR)/lib $(FFT_LIB) $(MATH_LIB)
	
.PHONY: clean

clean:
	rm spu_$(PROJ) 