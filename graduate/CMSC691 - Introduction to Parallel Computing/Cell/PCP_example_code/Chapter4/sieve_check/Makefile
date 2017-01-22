PROJ=sieve_check

SCC=spu-gcc
CFLAGS=-g -Wall
PROF_DIR=/opt/ibm/systemsim-cell/include/callthru/spu

spu_$(PROJ): spu_$(PROJ).c
	$(SCC) $(CFLAGS) -I$(PROF_DIR) -o $@ $^
	
.PHONY: clean

clean:
	rm spu_$(PROJ) 