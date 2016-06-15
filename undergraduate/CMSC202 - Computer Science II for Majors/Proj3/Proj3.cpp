//---------------------------------------------------
// File       : Proj3.cpp
// Author     : Patrick Trinkle
// Date       : November 5 2004
// UMBC Email : tri1@umbc.edu
// Project    : 3
// Section    : 0101
// Description: Main function for Project 3
//---------------------------------------------------

#include "Truck.h"
#include "RoundToy.h"
#include "Box.h"
#include "DeliveryLog.h"
#include "DeliveryRecord.h"


#include<iostream>
#include<fstream>

const string CMD1 = "TOYS";
const string CMD2 = "BOXES";
const string CMD3 = "PRINT";
const string CMD4 = "DELIVER";
// commands

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
      exit(-2);
   }  

   // set formatting options
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   // declare important variables
   string command;
   int count, holes;
   double diameter;
   string color;
   int length, width, height;

   // vector to hold boxes
   vector<Box> BoxQueue;

   // declare color variables
   int numColors = 0;
   inStream >> numColors;
   vector<int> colorsCtr(numColors, 0);
   vector<string> colors;
   int totaltoys = 0;
   
   // read in colors
   for ( int i = 0; i < numColors; i++ )
   {
      string temp;
      inStream >> temp;
      colors.push_back(temp);
   }

   // declare truck
   Truck truck;

   // while loop runs through file
   while ( inStream >> command )
   {
      
      // toys command
      if ( command == CMD1 )
      {
	 unsigned int nrRecycled = 0;
	 int nrPacked = 0;

	 // gather info
	 inStream >> count >> diameter >> color >> holes;
	 cout << "CMD " << command << ": " 
	      << count << ", " << diameter << ", " 
	      << color << ", " << holes << endl << endl;
	 
	 // begin for loop
	 for ( int i = 0; i < count; i++ )
	 {
	    // make toy
	    RoundToy toy(diameter, color, holes);
	    
	    // there are boxes in the queue
	    if ( BoxQueue.size() > 0 )
	    {
	       unsigned int j = BoxQueue.size() - 1;

	       if ( toy.Volume() <= BoxQueue.at(j).Unused() )
	       {
		  BoxQueue.at(j) += toy;
		  nrPacked++;
		  // toy added to the box
	       }
	       else
	       {
		  int y = 0;
		  while ( BoxQueue.size() > 0 && BoxQueue.at(j).Unused() < toy.Volume() && y == 0)
		  { 
                     // so while there are boxes and that the top box doesn't have enough room
		     truck += BoxQueue.at(j);
		     BoxQueue.pop_back();
		     // if there are still boxes
		     if ( BoxQueue.size() > 0 )
		     {
			j = BoxQueue.size() - 1;
			if ( toy.Volume() <= BoxQueue.at(j).Unused() )
			{
			   BoxQueue.at(j) += toy;
			   nrPacked++;
			   y = 2;
			   // toy added
			} // toy added from while statement
		     } // end if statement in while loop
		  }
	       } // the toy didn't fit in top box statement
	    } // there were boxes in the queue if statement
	    else
	    {
	       i = i * count * 2;
	       cout << "No more boxes" << endl;
	       // print out no boxes statement
	    }
	 } // end for loop
	 
	 if ( BoxQueue.size() > 0 )
         {
            unsigned int k = BoxQueue.size() - 1;
            if ( BoxQueue.at(k).NumToys() > 0 )
            {
               truck += BoxQueue.at(k);
               BoxQueue.pop_back();
            }
	    // seal box if toys, load onto truck
         }
	 nrRecycled = BoxQueue.size();
         //empty the leftover boxes
         if ( BoxQueue.empty() )
         {
         }
         else
         {
            BoxQueue.clear();
         }

	 // print statements for end of for loop
         if ( nrPacked != count )
         {
            // print info on unpacked toys
            cout << nrPacked << " " << color
                 << " toys with diameter " << diameter << " and "
                 << holes << " hole(s) packed"
                 << endl;

            int nrNotPacked;
            nrNotPacked = count - nrPacked;

            cout << nrNotPacked << " " << color
                 << " toys with diameter " << diameter << " and "
                 << holes << " hole(s) not packed"
                 << endl << endl;
         }
         else if ( nrPacked == count )
         {
            cout << "All toys made and shipped" << endl;
            cout << nrRecycled << " boxes destroyed" << endl << endl;
         }
      } // end of command if ( command == cmd1 ) 
      
      // box command
      else if ( command == CMD2 )
      {
	 // gather info
	 inStream >> count >> length >> width >> height;
	 cout << "CMD " << command 
	      << ": " << count << ", " 
	      << length << ", " << width 
	      << ", " << height << endl << endl;

	 // makes boxes and put in list of available boxes
	 for ( int i = 0; i < count; i++ )
	 {
	    Box box(length, width, height);
	    BoxQueue.push_back(box);
	 }
      }
      
      // print command
      else if ( command == CMD3 )
      {
	 // echos command and runs print function
	 cout << "CMD " << command << endl << endl;
	 cout << truck << endl;
      }

      // deliver command
      else if ( command == CMD4 )
      {
	 int distance;
	 string plantName;
	 inStream >> distance;
	 getline(inStream, plantName);

	 cout << "CMD " << command << " " << distance << " " << plantName << endl << endl;

	 DeliveryRecord newrecord(truck.NumBoxes(), distance, plantName); // creates record
	 truck.GetLog().AddRecord(newrecord); // adds record to the delivery log object
	 // run testing in for loop
	 string temp;

	 for ( int i = 0; i < truck.NumBoxes(); i++ )
	 {
	    for ( unsigned int j = 0; j < truck.GetBox(i).NumToys(); j++ )
	    {
	       temp = truck.GetBox(i).GetToy(j).Color();
	       for ( unsigned int k = 0; k < colors.size(); k++ )
	       {
		  if ( colors.at(k) == temp )
		  {
		     colorsCtr.at(k)++;
		     totaltoys++;
		     k = k + colors.size() * 2;
		  } // color check if statement
	       } // color check for loop
	    } // toys in box for loop
	 } // boxes on truck for loop
	 truck.Deliver(); // clears out the boxes from the truck

      } // end of command if ( command == cmd4 )
      
      // error check
      else
      {
	 // error check!
	 cerr << "CMD " << command 
	      << " is invalid." << endl 
	      << endl;
      }
   }
   
   inStream.close();
   // close the input file

   cout << endl << "Toy production summary: " << totaltoys << endl << endl;

   int counter = 0;

   // print toy summary
   for ( unsigned int i = 1; i < colors.size() + 1; i++ )
   {
      if ( i % 5 == 0 )
      {
	 cout << setw(5) << colorsCtr.at(counter)
	      << setw(9) << colors.at(counter) << endl;
      }
      else
      {
	 cout << setw(5) << colorsCtr.at(counter)
	      << setw(9) << colors.at(counter);
      }
      counter++;
   }
   cout << endl;

   return 0;
}
