#include <Ogre.h>

using namespace Ogre;
using namespace std;

int main(int, char **) {
   // Create Root and RenderWindow
   Root* root = new Root("./plugins.cfg");
   if (!root->restoreConfig()) {
      if (!root->showConfigDialog()) {
         return 1;
      }
   }
   RenderWindow* window = 
      root->initialise(true, "Ogre Basic");
    
   // Create Scene Manager and Camera
   SceneManager* sceneManager = 
      root->createSceneManager(ST_GENERIC, "SceneManager");
   Camera* camera = sceneManager->createCamera("Camera");
   camera->setPosition(Vector3(0.0f, 0.0f, 500.0f));
   camera->lookAt(Vector3(0.0f, 0.0f, 0.0f));
   camera->setNearClipDistance(5.0f);
   camera->setFarClipDistance(1000.0f);
      
   // Bind scene and RenderWindow
   Viewport* viewport = window->addViewport(camera);
   viewport->setBackgroundColour(ColourValue(0.0f, 1.0f, 0.0f));
   camera->setAspectRatio(Real(viewport->getActualWidth()) /
                            Real(viewport->getActualHeight()));

   // Run the main loop and dispose of the root at finish
   root->startRendering();
   delete root;
   return 0;
}
