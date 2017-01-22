PROJ=HelloWorld

PCC=ppu-gcc
CFLAGS=-Wall

$(PROJ): $(PROJ).o
	$(PCC) $(CFLAGS) -o $@ $^

$(PROJ).o: $(PROJ).c
	$(PCC) -c $(CFLAGS) -o $@ $^
	
.PHONY: clean

clean:
	rm $(PROJ).o $(PROJ)