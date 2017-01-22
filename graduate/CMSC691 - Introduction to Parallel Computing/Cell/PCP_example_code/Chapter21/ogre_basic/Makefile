PROJ=ogre_basic

PCC=g++
CFLAGS=-Wall

OGRE_LIBDIR=/usr/local/lib/OGRE
OGRE_INCLUDE=/usr/local/include/OGRE
OGRE_LIBS=$(OGRE_LIBDIR)/Plugin_BSPSceneManager.so $(OGRE_LIBDIR)/Plugin_BSPSceneManager.so \
$(OGRE_LIBDIR)/Plugin_OctreeSceneManager.so $(OGRE_LIBDIR)/Plugin_ParticleFX.so $(OGRE_LIBDIR)/RenderSystem_GL.so 

$(PROJ): $(PROJ).cpp
	$(PCC) -o $@ -I$(OGRE_INCLUDE) -R$(OGRE_LIBDIR) -R/usr/local/lib $^ $(OGRE_LIBS)

.PHONY: clean

clean:
	rm $(PROJ)