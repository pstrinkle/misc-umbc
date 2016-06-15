//---------------------------------------------------
// File       : Proj3.cpp
// Author     : Patrick Trinkle
// Date       : April 2005
// UMBC Email : tri1@umbc.edu
// Project    : 3
// Section    : 0101
// Description: The Project Main File  used for Proj3
// :: Please see ReadMe.txt
//---------------------------------------------------


#include <stdlib.h>
#include <fstream>
#include "BinarySearchTree.h"


int main( int argc, char** argv)
{
   if ( argc != 3)
   {
      cerr << "Not enough arguments." << endl;
      exit(-1);
   }
   ifstream inStream(argv[2]);
   if ( inStream == NULL )
   {
      cerr << "Invalid Input File." << endl;
      exit(-2);
   }
   
   int levelprint = 0;
   levelprint = atoi(argv[1]);

   BinarySearchTree<int> bst(-1);
   BinarySearchTree<int> rbst(-1);

   // set randomize
   srand(1);

   int input = 0;
   int inputfound = 0;

   while ( inStream >> input )
   {
      
      inputfound = bst.find(input);
      
      if ( inputfound != input )
      {
	 bst.insert(input);
	 // doesn't work because split() core dumps
	 // rbst.randomizeinsert(input);
      }
   }
   
   cout << "bst: " << endl << "Sorted Order Print" << endl;
   bst.printTree();

   cout << endl << "Height: " << bst.height() << endl;

   // doesn't work, just prints an infinite loop of the first element
   /*
   cout << "Level Order Print " << endl << endl;
   bst.LevelOrderPrint(levelprint);
   */
   cout << endl;

   bst.makeEmpty();
   /*
   cout << "rbst: " << endl << "Sorted Order Print" << endl;
   rbst.printTree();
   cout << endl << "Height: " << rbst.height() << endl;

   rbst.makeEmpty();
   */
   return 0;

}
