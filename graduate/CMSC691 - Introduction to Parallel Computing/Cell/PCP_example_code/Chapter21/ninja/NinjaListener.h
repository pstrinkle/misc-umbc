#ifndef NINJALISTENER_H
#define NINJALISTENER_H

#include <Ogre.h>
#include <OIS/OIS.h>

using namespace Ogre;

class NinjaListener : public FrameListener {
public:
   NinjaListener(OIS::Keyboard* keyboardInput, Entity* ninjaEntity);
   virtual bool frameStarted(const FrameEvent& evt);
private:
   OIS::Keyboard* keyboard;
   AnimationState* state;
   Entity* ninja;
};

#endif
