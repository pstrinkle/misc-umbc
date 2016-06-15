//---------------------------------------------------
// File       : Proj5.cpp
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Main function for Project 5
//---------------------------------------------------

#include "TinkerToy.h"
#include "RoundToy.h"
#include "SquareToy.h"
#include "RodToy.h"

#include "Truck.h"

#include "TruckEmpty.h"
#include "TruckFull.h"

#include "Box.h"
#include "Glue.h"
#include "PaintCan.h"

#include "DeliveryLog.h"
#include "DeliveryRecord.h"

#include<iostream>
#include<fstream>

const string CMD1 = "TOYS";
const string CMD2 = "BOXES";
const string CMD3 = "PRINT";
const string CMD4 = "DELIVER";
const string CMD5 = "PAINT";
const string CMD6 = "GLUE";
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

   int maxBoxes, maxGlue, maxPaint;
   inStream >> maxBoxes >> maxPaint >> maxGlue;

   // declare color variables
   int numColors = 0;
   inStream >> numColors;
   vector<int> colorsCtr(numColors, 0);
   vector<int> colorsPaintCtr(numColors, 0);
   vector<string> colors;

   int totaltoys = 0;
   int totalPaint = 0;
   int totalGlue = 0;
   
   // read in colors
   for ( int i = 0; i < numColors; i++ )
   {
      string temp;
      inStream >> temp;
      colors.push_back(temp);
   }

   // declare trucks
   Truck<Box> boxTruck;
   Truck<Glue> glueTruck;
   Truck<PaintCan> paintTruck;

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
			y = 2;
			   // toy added
		     } // toy added from while statement
		     else if ( boxId == BoxQueue.size() )
		     {
			cout << "No more boxes." << endl;
			y = 2;
			i = i + 10 + count;
		     }
		  }
	       } // the toy didn't fit in top box statement
	    } // there were boxes in the queue if statement
	    else
	    {
	       i = i + count + 2;
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
	       // try block for full truck
	       try
	       {
		  if ( BoxQueue.at(k).NumToys() > 0 )
		  {
		     if ( boxTruck.NumItems() == maxBoxes )
		     {
			// the truck is full
			throw TruckFull<Box>(maxBoxes, "BOX", BoxQueue.at(k));
		     }
		     else
		     {
			// increment with toys then add
			tempClr = color;
			for ( unsigned int clrCounter = 0; clrCounter < colors.size(); clrCounter++ )
			{
			   if ( colors.at(clrCounter) == tempClr )
			   {
			      colorsCtr.at(clrCounter) += BoxQueue.at(k).NumToys();
			      totaltoys += BoxQueue.at(k).NumToys();
			      clrCounter = clrCounter + colors.size() + 2;
			   } // color check if statement
			}
			// then officially add the truck
			boxTruck += BoxQueue.at(k);
		     }
		  }
		  else
		  {
		     // box was empty
		     nrRecycled++;
		  }
	       }
	       catch(TruckFull<Box>& exception)
	       {
		  // print out truckfull exception
		  cout << exception << endl;;
		  k = BoxQueue.size();
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

	 cout << "Box Truck" << endl;
	 cout << boxTruck << endl;

	 cout << "Paint Truck" << endl;
	 cout << paintTruck << endl;

	 cout << "Glue Truck" << endl;
	 cout << glueTruck << endl;
      }

      // paint command
      else if ( command == CMD5 )
      {
	 // capture paint information
	 int gallons;
	 string tempClr;

	 inStream >> count >> gallons >> color;

	 cout << "CMD " << command << " " 
	      << count << " cans of " 
	      << color << " paint at " 
	      << gallons << " gallons." 
	      << endl << endl;

	 for ( int i = 0; i < count; i++ )
	 {
	    // make paint can and try to add it
	    PaintCan can(gallons, color);

	    try
	    {
	       if ( paintTruck.NumItems() == maxPaint )
	       {
		  // truck was full
		  throw TruckFull<PaintCan>(maxPaint, "Paint", can);
	       }
	       else
	       {
		  paintTruck += can;
	       }
	    }
	    catch(TruckFull<PaintCan>& exception)
            {
	       // print out exception information
               cout << exception << endl;
               i += count;
            }
	 }
	 // production incrementing
	 tempClr = color;
	 for ( unsigned int clrCounter = 0; clrCounter < colors.size(); clrCounter++ )
	 {
	    if ( colors.at(clrCounter) == tempClr )
	    {
	       colorsPaintCtr.at(clrCounter) += count;
	       totalPaint += count;
	       clrCounter = clrCounter + colors.size() + 2;
	    } // color check if statement
	 }
      } 

      // glue command
      else if ( command == CMD6 )
      {
	 // get information
      	 string type;

	 inStream >> count;
	 getline(inStream, type);

	 cout << "CMD " << command << " " << count << " " << type << endl << endl;

	 for ( int i = 0; i < count; i++ )
	 {
	    // make glue and try to add it to truck
	    Glue bottle(type);
	    try
	    {
	       if ( glueTruck.NumItems() == maxGlue )
	       {
		  // truck is full
		  throw TruckFull<Glue>(maxGlue, "Glue", bottle);
	       }
	       else
	       {
		  glueTruck += bottle;
		  totalGlue++;
	       }
	    }
	    catch(TruckFull<Glue>& exception)
            {
	       // print out exception information
               cout << exception << endl;
               i += count;
            }
	 }

      }

      // deliver command
      else if ( command == CMD4 )
      {
	 int distance;
	 string plantName;
	 string truckType;
	 inStream >> truckType >> distance;
	 getline(inStream, plantName);

	 cout << "CMD " << command << " " << truckType << " " << distance << " " << plantName << endl << endl;

	 // create and add record
	 try
	 {
	    if ( truckType == "PAINT" )
	    {
	       if ( paintTruck.NumItems() == 0 )
	       {
		  // empty truck
		  throw TruckEmpty(distance, plantName, truckType);
	       }
	       else
	       {
		  // add record and deliver
		  DeliveryRecord newrecord(paintTruck.NumItems(), distance, plantName, truckType);
		  paintTruck.GetLog().AddRecord(newrecord);
		  paintTruck.Deliver();
	       }
	    }
	    else if ( truckType == "GLUE" )
	    {
	       if ( glueTruck.NumItems() == 0 )
	       {
		  // empty truck
		  throw TruckEmpty(distance, plantName, truckType);
	       }
	       else
	       {
		  // add record and deliver
		  DeliveryRecord newrecord(glueTruck.NumItems(), distance, plantName, truckType);
		  glueTruck.GetLog().AddRecord(newrecord);
		  glueTruck.Deliver();
	       }
	    }
	    else if ( truckType == "BOXES" )
	    {
	       if ( boxTruck.NumItems() == 0 )
	       {
		  // emptry truck
		  throw TruckEmpty(distance, plantName, truckType);
	       }
	       else
	       {
		  // add record and deliver
		  DeliveryRecord newrecord(boxTruck.NumItems(), distance, plantName, truckType);
		  boxTruck.GetLog().AddRecord(newrecord);
		  boxTruck.Deliver();
	       }
	    }
	 }
	 catch(const TruckEmpty& exception)
	 {
	    // print information on empty truck exception
	    cout << exception.What() << " ";
	    cout << exception.GetMiles() << " miles." << endl;
	 }
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

   cout << endl << "Toy Production Summary: " << totaltoys << " toys" << endl << endl;

   int counter = 0;

   // print color production summary
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

   counter = 0;
   cout << endl << endl << "Paint Production Summary: " << totalPaint << " cans" << endl << endl;
   for ( unsigned int i = 1; i < colors.size() + 1; i++ )
   {
      if ( i % 5 == 0 )
      {
         cout << setw(5) << colorsPaintCtr.at(counter)
              << setw(9) << colors.at(counter) << endl;
      }
      else
      {
         cout << setw(5) << colorsPaintCtr.at(counter)
              << setw(9) << colors.at(counter);
      }
      counter++;
   }

   cout << endl << endl << "Glue Production Summary: " << totalGlue << " bottles" << endl << endl;

   cout << endl;

   return 0;
}
