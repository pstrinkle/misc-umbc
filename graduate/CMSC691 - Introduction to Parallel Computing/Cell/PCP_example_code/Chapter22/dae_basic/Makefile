PROJ=dae_basic

PCC=     g++
COLLADA_DIR=/root/colladadom/dom
LIBS=   -lxml2 -lcollada14dom 
CFLAGS= -Wall

$(PROJ): $(PROJ).cpp
	$(PCC) $(CFLAGS) -o $@ $^ -I$(COLLADA_DIR)/include -L$(COLLADA_DIR)/build/linux-1.4 $(LIBS)

.PHONY: clean

clean:
	rm $(PROJ)