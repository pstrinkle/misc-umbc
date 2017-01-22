#include <iostream>
#include <dae.h>

using namespace std;

int main(int, char **) {
   unsigned int docnum;
   
   /* Create a DAE object */
   DAE* dae = new DAE;
   
   /* Load file content and access the database */
   dae->load("example.dae");
   dae->setDatabase(0);   
   
   /* Insert document into database */
   daeDocument *daeDoc = NULL;
   dae->getDatabase()->insertDocument("example.dae", 
      &daeDoc);
   
   /* Obtain and display number of documents */
   docnum = dae->getDatabase()->getDocumentCount();
   cout << "Document count: " << docnum << endl;
   
   /* Unload document and deallocate DAE */
   dae->unload("example.dae");
   delete dae;
   return 0;
} 
