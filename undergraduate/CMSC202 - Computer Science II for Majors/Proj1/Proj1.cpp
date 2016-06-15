//---------------------------------------------------
// File       : Proj1.cpp
// Author     : Patrick Trinkle
// Date       : September 26 2004
// UMBC Email : tri1@umbc.edu
// Project    : 1
// Section    : 0101
// Description: Main function for Project 1
//---------------------------------------------------


#include "RoundToy.h"
#include "Box.h"

using namespace std;

int main (int argc, char** argv) // check the argv dereference 
{

   // check command line arguments
   if ( argc != 2 )
   {
      cerr << "Not enough arguments." << endl;
      exit(-1);
   }

   // check input file
   ifstream inStream(argv[1]);
   if (inStream == NULL)
   {
      cerr << "Invalid Input File." << endl;
      exit(-1);
   }  

   // set formatting options
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   // declare important variables
   string command;
   int count;
   double diameter;
   string color;
   int holes;
   bool success;
   RoundToy toy;
   BOX box;
   int length, width, height;

   inStream >> length >> width >> height;
   // retrieve the dimensions for the box

   BoxInit(box, length, width, height);
   // sets the box to the retrieved dimensions

   // while loop runs through file
   while ( inStream >> command )
   {
      if ( command == "MAKE" )
      {
         // echo the make command
         inStream >> count >> diameter >> color >> holes;
         cout << "CMD " 
              << command 
              << " " 
              << count 
              << " " 
              << diameter 
              << " " 
              << color 
              << " " 
              << holes 
              << endl << endl;

         int i;

         // for loop to place toys in box
         for ( i = count; i > 0; i-- )
         {
            RoundToyInit(toy, diameter, color, holes);
            success = BoxStore(box, toy);
            if ( success == false )
            {
               cout << i 
                    << " " 
                    << color 
                    << " Round Toys with diameter "
                    << diameter 
                    << " and "
                    << holes 
                    << " holes "
                    << "did not fit in the box" 
                    << endl << endl;
               i = -1;
               // if toy doesn't fit it breaks loop and reports
            }
         }
      }
      else if ( command == "PRINT" )
      {
         cout << "CMD " << command << endl;
         BoxPrint(cout, box);
         // echos print command and prints contents of box
      }
      else
      {
         cerr << "CMD " << command << " is an invalid command" << endl << endl;
         // prints an error because the command entered was neither MAKE nor PRINT
      }

   }

   inStream.close();
   // close the input file

   return 0;
}
