//---------------------------------------------------
// File       : Box.cpp
// Author     : Patrick Trinkle
// Date       : September 26 2004
// UMBC Email : tri1@umbc.edu
// Project    : 1
// Section    : 0101
// Description: Functions That access the
//              members of Box Struct Used for Proj1
//---------------------------------------------------

#include "Box.h"
#include "RoundToy.h"

using namespace std;

//---------------------------------------
// BoxInit
// PreConditions:
//         a box declared with dimensions
// PostConditions
//         a box with initialized
//         dimensions
//---------------------------------------
void BoxInit(BOX& box, int length, int width, int height)
{
   box.length = length;
   box.width = width;
   box.height = height;
   // inititalizes all the members of the new box structure

}

//---------------------------------------
// BoxUnused
// PreConditions:
//         a box structure defined
// PostConditions
//         returns the unused volume of
//         the box structure
//---------------------------------------
double BoxUnused(const BOX& box)
{
   double boxVolume, volume, tempVolume, unusedVolume;
   unusedVolume = box.length * box.width * box.height;
   unsigned int numToys;
   volume = 0;
   numToys = box.toysinbox.size();
   // set up the for loop

   if ( numToys != 0 )
   {
      unsigned int i;

      for ( i = 0; i < numToys; i++ )
      {
         tempVolume = RoundToyVolume(box.toysinbox.at(i));
         volume = volume + tempVolume;
         // takes the volume of each toy and totals them all up
      }

      boxVolume = box.length * box.width * box.height;
      // calculates the volume of the box

      unusedVolume =  boxVolume - volume;
      // calculates the leftover volume and then returns it in the next line

      return unusedVolume;

   }

   return unusedVolume;
}

//---------------------------------------
// BoxStore
// PreConditions:
//         a box structure defined, and
//         a toy
// PostConditions
//         None
//---------------------------------------
bool BoxStore(BOX& box, const RoundToy& toy)
{
   double unusedVolume, toyVolume, toyDiameter, toyRadius;
   unusedVolume = BoxUnused(box);
   toyDiameter = RoundToyDiameter(toy);
   toyRadius = toyDiameter / 2;
   toyVolume = ( 4 / 3 ) * PI * ( toyRadius * toyRadius * toyRadius );

   // gets the unused volume of the box and the volume of the toy in queue


   if ( toyVolume <= unusedVolume )
   {
      box.toysinbox.push_back(toy);
      // the toy is put in the box if it will fit volume wise
   }
   else
   {
      return false;
      // if this action is not completed a boolean false is returned otherwise it is true
   }

   return true;
}

//---------------------------------------
// BoxPrint
// PreConditions:
//         a box structure defined
// PostConditions
//         None
//---------------------------------------
void BoxPrint(ostream& out, const BOX& box)
{
   int numRed, numBlue, numWhite, toyTotal;
   numRed = 0;
   numBlue = 0;
   numWhite = 0;
   toyTotal = 0;

   // prints out the box dimensions

   out << "Box Dimensions : "
       << box.length
       << " x "
       << box.width
       << " x "
       << box.height
       << endl;
   
   // prints out the box volume
   out << "Box Volume     : "
       << ( box.length * box.width * box.height )
       << endl;

   // prints out the unused box volume

   out << "Unused Volume  : "
       << BoxUnused(box)
       << endl
       << endl;

   // tests if there are contents and prints according for the box

   out << "Box Contents"
       << endl;

   if ( box.toysinbox.size() == 0 )
   {
      out << "Box is empty"
          << endl
          << endl;
   }
   else
   {      
      out << endl
          << "Color   Diameter         Volume   Holes"
          << endl
          << "-----   --------         ------   -----"
          << endl;

      // prints each toy in the box and talleys up the colors totals

      unsigned int i;

      for ( i = 0; i < box.toysinbox.size(); i++ )
      {
         string toyColor;
         toyColor = RoundToyColor(box.toysinbox.at(i));
         if ( toyColor == "Blue" )
         {
            numBlue++;
         }
         else if ( toyColor == "Red" )
         {
            numRed++;
         }
         else
         {
            numWhite++;
         }
         out << setw(5) << setiosflags(ios::left) << toyColor
             << "   "
             << setw(8) << RoundToyDiameter(box.toysinbox.at(i))
             << "         "
             << setw(6) << RoundToyVolume(box.toysinbox.at(i))
             << "   "
             << setw(5) << RoundToyHoles(box.toysinbox.at(i))
             << endl;
      }
   }
   
   toyTotal = numRed + numBlue + numWhite;

   // prints out box summary with talley of total toys and the totals for each color toy

   out << endl
       << "Box Summary: "
       << toyTotal
       << " total toys"
       << endl
       << "        "
       << numRed
       << " Red"
       << endl
       << "        "
       << numWhite
       << " White"
       << endl
       << "        "
       << numBlue
       << " Blue"
       << endl
       << endl;
}
