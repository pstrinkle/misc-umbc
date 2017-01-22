PROJ=sign

PCC=ppu-gcc
SCC=spu-gcc
EMBED=ppu-embedspu
SIGN=spu-isolated-app
PROC_TYPE=-m64
CFLAGS=-Wall -m64 -maltivec
LIBS=-lspe2

CRT_ISO_DIR=/opt/cell/sdk/prototype/usr/spu/lib
CRT_ISO=$(CRT_ISO_DIR)/iso_crt0.o
ISO_LD_FLAGS=-Wl,-T,/usr/spu/lib/ldscripts/elf32_spu.xi -Wl,-N -nostartfiles
EMULATED_BIN=/usr/lib64/spe

SIGN_DIR=/opt/cell/sdk/prototype/usr/bin
SIGN=$(SIGN_DIR)/spu-isolated-app

KEYSTORE=/opt/cell/sdk/prototype/src/examples/isolation/keystore
PRIV_KEY=$(KEYSTORE)/user_sign_key.pem
CERT=$(KEYSTORE)/user_signed_crt.pem
CRYPT_SECT=

ppu_$(PROJ): ppu_$(PROJ).c spu_$(PROJ).o
	$(PCC) -o $@ $^ $(CFLAGS) $(LIBS)

spu_$(PROJ).o: spu_$(PROJ)
	$(EMBED) $(PROC_TYPE) spu_$(PROJ) spu_$(PROJ) $@

spu_$(PROJ): spu_$(PROJ)_pre
	$(SIGN) spu_$(PROJ)_pre spu_$(PROJ) $(PRIV_KEY) $(CERT) $(CRYPT_SECT)

spu_$(PROJ)_pre: spu_$(PROJ)_pre.o $(CRT_ISO)
	$(SCC) -o $@ $^ $(ISO_LD_FLAGS) -L$(EMULATED_BIN)
   
spu_$(PROJ)_pre.o: spu_$(PROJ).c
	$(SCC) -c -o $@ $^

.PHONY: clean

clean:
	rm *.o ppu_$(PROJ) spu_$(PROJ) spu_$(PROJ)_pre