//---------------------------------------------------
// File       : Proj4.cpp
// Author     : Patrick Trinkle
// Date       : April 2005
// UMBC Email : tri1@umbc.edu
// Project    : 4
// Section    : 0101
// Description: The Project Main File  used for Proj4
//---------------------------------------------------


#include <stdlib.h>
#include <fstream>
#include <ctype.h>

#include "QuadProbing.h"
#include "HashingAux.h"

void parsetext( string& input );

int main( int argc, char** argv)
{

   if ( argc != 3)
   {
      cerr << "Not enough arguments." << endl;
      exit(-1);
   }

   ifstream inExclusionStream(argv[1]);
   if ( inExclusionStream == NULL )
   {
      cerr << "Invalid Exclusion Input File." << endl;
      exit(-2);
   }

   ifstream inTextStream(argv[2]);
   if ( inTextStream == NULL )
   {
      cerr << "Invalid Text Input File." << endl;
      exit(-3);
   }

   cout.setf(ios::left);

   string exclude, input;
   HashTable<string> excinput("undefined");
   HashTable<string> storage("0");

   int n_words = 0;
   int n_excl = 0;
   int n_total = 0;

   while ( inExclusionStream >> exclude )
   {
      parsetext(exclude);

      if ( excinput.find(exclude) != exclude )
	 excinput.insert(exclude);
   }
   inExclusionStream.close();

   while ( inTextStream >> input )
   {
      parsetext(input);

      if ( input == " " || input[1] == '\0' || input[1] == '\n')
      {
	 // do nill
      }
      else
      {
	 n_total++;

	 if ( excinput.find(input) != input )
	 {
	    n_words++;
	    storage.insert(input);
	 }
	 else
	    n_excl++;
      }
   }
   inTextStream.close();

   storage.printInfo(1);

   cout << endl << endl << endl;
   cout << "Top 20 Words by Frequency:" << endl;
   storage.top20(cout);

   cout << endl << "Total words read in from input file: " << n_total << endl
	<< "Total words excluded from input file: " << n_excl << endl
	<< "Total words included: " << n_words << endl;
   cout << "Total Average Word Frequency : " << storage.avgwordFreq() << endl << endl;

   excinput.makeEmpty();
   storage.makeEmpty();

   return 0;
}


void parsetext( string& input )
{
   string::iterator the_iterator;
   the_iterator = input.begin();
   unsigned int i = 0;

   while ( i < input.length() )
   {

      if ( input.at(i) < 65 || input.at(i) > 122 )
         input.erase(the_iterator);

      else if ( input.at(i) > 90 && input.at(i) < 97 )
         input.erase(the_iterator);

      else
      {
         input.at(i) = tolower(input.at(i));
         the_iterator++;
         i++;
      }
   }
};
