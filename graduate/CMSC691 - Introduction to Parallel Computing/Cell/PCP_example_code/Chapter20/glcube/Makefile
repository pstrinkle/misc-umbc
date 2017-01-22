PROJ=glcube

PCC=ppu32-g++
CFLAGS=-Wall

MESA_DIR=$(HOME)/mesa
GL_LIBS=-lGL -lGLU -lglut

ppu_$(PROJ): ppu_$(PROJ).c
	$(PCC) -o $@ -I$(MESA_DIR)/include -L$(MESA_DIR)/lib -R$(MESA_DIR)/lib $^ $(GL_LIBS)

.PHONY: clean

clean:
	rm ppu_$(PROJ)