PROJ=glut_basic

PCC=ppu32-g++
CFLAGS=-Wall

MESA_DIR=$(HOME)/mesa
GLUT_LIB=-lglut

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) -o $@ -I$(MESA_DIR)/include -L$(MESA_DIR)/lib -R$(MESA_DIR)/lib $^ $(GLUT_LIB)
	
.PHONY: clean

clean:
	rm ppu_$(PROJ)