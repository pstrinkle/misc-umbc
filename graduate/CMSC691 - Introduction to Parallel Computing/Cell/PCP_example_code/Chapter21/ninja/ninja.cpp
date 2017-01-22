#include <Ogre.h>
#include "NinjaListener.h"

using namespace Ogre;
using namespace std;

void initResources() {
   // Load resource paths from config file
   ConfigFile cf;
   cf.load("ninja_res.cfg");    
    
   // Go through all sections & settings in the file
   ConfigFile::SectionIterator iter 
      = cf.getSectionIterator();    
   while (iter.hasMoreElements()) {
      String secName = iter.peekNextKey();
      ConfigFile::SettingsMultiMap* settings = 
         iter.getNext();
      for (ConfigFile::SettingsMultiMap::iterator i = 
         settings->begin(); i != settings->end(); ++i) {
        
         String typeName = i->first;
         String archName = i->second;
         ResourceGroupManager::getSingleton()
            .addResourceLocation(
               archName, typeName, secName);
      }
   }
   ResourceGroupManager::getSingleton()
      .initialiseAllResourceGroups();
}

int main(int, char **) {
   
   // Initialize of Root and RenderWindow
   Root* root = new Root("plugins.cfg");
   if (!root->restoreConfig()) {
      if (!root->showConfigDialog()) {
         return 1;
      }
   }
   RenderWindow* window = root->initialise(true, "Ninja!");
   initResources();

   // Initialize SceneManager and Camera
   SceneManager* sceneManager = root->createSceneManager(ST_GENERIC, "sceneManager");
   Camera* camera = sceneManager->createCamera("Camera");
   camera->setPosition(Vector3(0.0f, 300.0f, -600.0f));
   camera->lookAt(Vector3(0.0f, 0.0f, 300.0f));
   camera->setNearClipDistance(5.0f);
   camera->setFarClipDistance(1000.0f);
   sceneManager->setAmbientLight(ColourValue(0.5f, 0.5f, 0.5f));

   // Access ninja mesh
   Entity *ninjaEntity = sceneManager->createEntity("ninja", "ninja.mesh");
   ninjaEntity->getSubEntity(0)->setMaterialName("ninja-material");
   ninjaEntity->getSubEntity(1)->setMaterialName("ninja-material");   
   SceneNode* ninjaNode =
      sceneManager->getRootSceneNode()->createChildSceneNode("NinjaNode");
   ninjaNode->attachObject(ninjaEntity);

   // Create a spotlight
   Light* light = sceneManager->createLight("Light");
   light->setType(Light::LT_POINT);
   SceneNode* lightNode = ninjaNode->createChildSceneNode("LightNode");
   lightNode->attachObject(light);
   lightNode->setPosition(100.0f, 75.0f, 0.0f);

   // Create keyboard and mouse
/*   size_t handle = 0;
   window->getCustomAttribute("WINDOW", &handle);
   OIS::InputManager* inputManager = OIS::InputManager::createInputSystem(handle);
   OIS::Keyboard* keyboard = static_cast<OIS::Keyboard*>
      (inputManager->createInputObject(OIS::OISKeyboard, false));

   // Create and configure listener
   NinjaListener* listener = new NinjaListener(keyboard, ninjaEntity);
   root->addFrameListener(listener); */

   // Binding of Scene and RenderWindow
   Viewport* viewport = window->addViewport(camera);
   viewport->setBackgroundColour(ColourValue(0.3f, 0.3f, 0.3f));
   camera->setAspectRatio(Real(viewport->getActualWidth()) /
                            Real(viewport->getActualHeight()));

   // Running the main loop
   root->startRendering();
   
//   delete keyboard;
//   delete listener;
   delete root;
   return 0;
}

