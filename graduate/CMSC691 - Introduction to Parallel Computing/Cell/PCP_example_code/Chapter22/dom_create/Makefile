PROJ=dom_create

PCC=     g++
COLLADA_DIR=/root/colladadom/dom
LIBS=   -lxml2 -lcollada14dom 
CFLAGS= -Wall

$(PROJ): $(PROJ).cpp
	$(PCC) $(CFLAGS) -o $@ $^ -I$(COLLADA_DIR)/include -I$(COLLADA_DIR)/include/1.4 -L$(COLLADA_DIR)/build/linux-1.4 $(LIBS)

.PHONY: clean

clean:
	rm $(PROJ)