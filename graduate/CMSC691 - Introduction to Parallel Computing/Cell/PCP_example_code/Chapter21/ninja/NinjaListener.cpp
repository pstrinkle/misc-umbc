#include "NinjaListener.h"

using namespace Ogre;

NinjaListener::NinjaListener(OIS::Keyboard* keyboardInput, Entity* ninjaEntity)
   : keyboard(keyboardInput), ninja(ninjaEntity) {
   
   // Enable Kick animation
   int i;
   std::string anims[] = {"Kick", "Crouch", "Attack1", "HighJump", "SideKick", "Attack2", "Spin", "Backflip", "Block", "Attack3"};
   for(i=0; i<10; i++) {
      state = ninja->getAnimationState(anims[i]);
      state->setEnabled(true);
      state->setLoop(true);
      state->setTimePosition(0);
   }
}

bool NinjaListener::frameStarted(const FrameEvent& evt) {
   keyboard->capture();

   if (keyboard->isKeyDown(OIS::KC_0))
      state = ninja->getAnimationState("Kick");
   else if (keyboard->isKeyDown(OIS::KC_1))
      state = ninja->getAnimationState("Crouch");
   else if (keyboard->isKeyDown(OIS::KC_2))
      state = ninja->getAnimationState("Attack1");
   else if (keyboard->isKeyDown(OIS::KC_3))
      state = ninja->getAnimationState("HighJump");
   else if (keyboard->isKeyDown(OIS::KC_4))
      state = ninja->getAnimationState("SideKick");
   else if (keyboard->isKeyDown(OIS::KC_5))
      state = ninja->getAnimationState("Attack2");
   else if (keyboard->isKeyDown(OIS::KC_6))
      state = ninja->getAnimationState("Spin");
   else if (keyboard->isKeyDown(OIS::KC_7))
      state = ninja->getAnimationState("Backflip");
   else if (keyboard->isKeyDown(OIS::KC_8))
      state = ninja->getAnimationState("Block");
   else if (keyboard->isKeyDown(OIS::KC_9))
      state = ninja->getAnimationState("Attack3");      
      
   state->addTime(evt.timeSinceLastFrame);
   return true;
}
