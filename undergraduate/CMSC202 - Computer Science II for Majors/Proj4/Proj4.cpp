//---------------------------------------------------
// File       : Proj4.cpp
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 4
// Section    : 0101
// Description: Main function for Project 4
//---------------------------------------------------

#include "TinkerToy.h"
#include "RoundToy.h"
#include "SquareToy.h"
#include "RodToy.h"
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
   int count, holes, side, length;
   float diameter;
   string color;

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
   // declare base class pointer
   TinkerToy * p_toy;

   // while loop runs through file
   while ( inStream >> command )
   {
      
      // toys command
      if ( command == CMD1 )
      {
	 string type, tempClr;
	 unsigned int nrRecycled = 0;
	 int nrPacked = 0;

	 // read in information
	 inStream >> type >> count >> color;
	 
	 // build specific toy
	 if ( type == "Round" )
	 {
	    inStream >> holes >> diameter;
	    p_toy = new RoundToy(diameter, color, holes);
	    cout << "CMD " << command << ": " << type << ", " << count 
		 << ", " << diameter << ", " << color << ", " << holes << endl;
	 }

	 else if ( type == "Square" )
	 {
	    inStream >> holes >> side;
	    p_toy = new SquareToy(color, side, holes);
	    cout << "CMD " << command << ": " << type << ", " << count << ", " << side << ", "
		 << color << ", " << holes << endl;
	 }

	 else if ( type == "Rod" )
	 {
	    inStream >> length;
	    p_toy = new RodToy(color, length);
	    cout << "CMD " << command << ": " << type << ", " << count << ", "
		 << length << ", " << color << endl;
	 }
 
	 // begin for loop
	 for ( int i = 0; i < count; i++ )
	 {  
	    // there are boxes in the queue
	    if ( BoxQueue.size() > 0 )
	    {
	       unsigned int boxId = 0;

	       if ( p_toy -> Volume() <= BoxQueue.at(boxId).Unused() )
	       {
		  // the toy fits to add it
		  BoxQueue.at(boxId) += p_toy;
		  nrPacked++;
		  // toy added to the box

		  // increment the production summary
		  tempClr = color;
		  for ( unsigned int clrCounter = 0; clrCounter < colors.size(); clrCounter++ )
		  {
		     if ( colors.at(clrCounter) == tempClr )
		     {
			colorsCtr.at(clrCounter)++;
			totaltoys++;
			clrCounter = clrCounter + colors.size() * 2;
		     } // color check if statement
		  }
	       }
	       else
	       {
		  int y = 0;
		  while ( boxId < BoxQueue.size() && 
			  BoxQueue.at(boxId).Unused() < p_toy -> Volume()
			  && y == 0 )
		  { 
		     // toy didn't fit on first box in queue
		     boxId++;
		     
		     if ( boxId < BoxQueue.size() && p_toy -> Volume() <= BoxQueue.at(boxId).Unused() )
		     {
			// toy fits so add it
			BoxQueue.at(boxId) += p_toy;
			nrPacked++;
			tempClr = color;

			// update production summary
			for ( unsigned int clrCounter = 0; clrCounter < colors.size(); clrCounter++ )
			{
			   if ( colors.at(clrCounter) == tempClr )
			   {
			      colorsCtr.at(clrCounter)++;
			      totaltoys++;
			      clrCounter = clrCounter + colors.size() * 2;
			   } // color check if statement
			}
			y = 2;
			   // toy added
		     } // toy added from while statement
		     else if ( boxId == BoxQueue.size() )
		     {
			cout << "No more boxes." << endl;
			y = 2;
			i = i * 10 * count;
		     }
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
	
	 // free allocated memory
	 delete p_toy;
 
	 // add boxes onto truck
	 if ( BoxQueue.size() > 0 )
         {
            for ( unsigned int k = 0; k < BoxQueue.size(); k++ )
	    {
	       if ( BoxQueue.at(k).NumToys() > 0 )
	       {
		  truck += BoxQueue.at(k);
	       }
	       else
	       {
		  nrRecycled++;
	       }
	    }
         }
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
            cout << nrPacked << " " << color << " " << type
                 << " Toy(s) packed"
                 << endl;

            int nrNotPacked;
            nrNotPacked = count - nrPacked;

            cout << nrNotPacked << " " << color << " " << type
                 << " Toy(s) not packed " << endl;
         }
         else if ( nrPacked == count )
         {
            cout << "All Toy(s) made and shipped" << endl;
            cout << nrRecycled << " boxes destroyed" << endl;
         }
      } // end of command if ( command == cmd1 ) 
      
      // box command
      else if ( command == CMD2 )
      {
	 int length, width, height;
	 // gather info
	 inStream >> count >> length >> width >> height;
	 cout << "CMD " << command 
	      << ": " << count << ", " 
	      << length << ", " << width 
	      << ", " << height << endl;

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

	 // create and add record
	 DeliveryRecord newrecord(truck.NumBoxes(), distance, plantName);
	 truck.GetLog().AddRecord(newrecord);
	 
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
   cout << endl;
   // print information on toy construction and destruction
   cout << "TinkerToy Constructor called " << p_toy -> NumConstructed() << " times" << endl
	<< "TinkerToy Destructor called " << p_toy -> NumDestroyed() << " times" << endl;

   cout << endl;

   return 0;
}
