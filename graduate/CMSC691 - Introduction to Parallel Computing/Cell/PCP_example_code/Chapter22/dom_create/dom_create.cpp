#include <iostream>
#include <dae.h>
#include <dom/domCOLLADA.h>
#include <dom/domAsset.h>

using namespace std;

int main(int, char **) {

   /* Create document and insert into database */
   DAE* dae = new DAE;
   dae->setDatabase(0);
   daeDocument* daeDoc = NULL;
   dae->getDatabase()->insertDocument("new.dae", &daeDoc);

   /* Get root element of document and create asset */
   domCOLLADA* dom = (domCOLLADA*)daeDoc->getDomRoot();
   domAsset* asset = (domAsset*)dom->createAndPlace("asset");
   
   /* Set values for the created and modified elements */
   domAsset::domCreated* created = 
      (domAsset::domCreated*)asset->
         createAndPlace("created");
   created->setValue("2008-03-25T14:21:29U");
   domAsset::domModified* modified = 
      (domAsset::domModified*)asset->
         createAndPlace("modified");
   modified->setValue("2008-03-25T21:51:29U");   

   /* Unload document and deallocate DAE */
   dae->save("new.dae");
   delete dae;
   return 0;
}
