//---------------------------------------------------
// File       : Proj2.cpp
// Author     : Patrick Trinkle
// Date       : October 13 2004
// UMBC Email : tri1@umbc.edu
// Project    : 2
// Section    : 0101
// Description: Main function for Project 2
//---------------------------------------------------


//---------------------------------------------------
//
// The program is miscalculating how many toys should
// go into a box. I cannot find why or where this is
// occuring. I went through the code many times and
// traced it. If you find where it is a problem, 
// please note in grade. I tried all over, to include
// all obvious locations. It wants to put 35 toys
// where only 26 should fit. Or at least it says
// there are 35 toys. Perhaps that is the problem
// regardless I have run out of time and I am
// reporting my bug here. Everything else appears to
// run error free. Have a nice day. -Patrick Trinkle
//
//--------------------------------------------------

#include "Truck.h"
#include "RoundToy.h"
#include "Box.h"

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

   bool success;

   // strings for truck
   string plantName;
   int distancetoPlant;   

   // get truck info
   getline( inStream, plantName );
   inStream >> distancetoPlant;

   // construct truck and set info
   Truck truck;
   truck.SetPlant( distancetoPlant, plantName );

   // while loop runs through file
   while ( inStream >> command )
   {
      
      // toys command
      if ( command == CMD1 )
      {
	 int nrRecycled = 0;
	 int nrPacked = 0;

	 // gather info
	 inStream >> count >> diameter >> color >> holes;
	 cout << "CMD " << command << ": " 
	      << count << ", " << diameter << ", " 
	      << color << ", " << holes << endl << endl;
         	 
	 // runs for loop, somehow add more toys into box than should be allowed
	 for ( int i = 0; i < count; i++ )
	 {
	    // make toy individually

	    RoundToy toy(diameter, color, holes);

	    // see if there are any boxes
	    if ( BoxQueue.size() > 0 )
	    {

	       unsigned int j = BoxQueue.size() - 1;

	       // try to place toy in box
	       success = BoxQueue.at(j).Store(toy);
	       
	       // if it doesn't fit in box, ship box and recycle it?
	       while ( BoxQueue.size() > 0 && success == false )
	       {
		  // loads box onto truck and removes from box list
		  truck.LoadTruck(BoxQueue.at(j));
		  BoxQueue.pop_back();
		  nrRecycled++;
		  j = BoxQueue.size() - 1;
		  if ( j >= 0 )
		  {
		     success = BoxQueue.at(j).Store(toy);
		  }
	       }
	       if ( success == true )
	       {
		  nrPacked++;
	       }
	    }
	    else
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
		    << endl;
	       // count breaker was here
               i = i + count + 100;
	    }
	    if ( nrPacked == count )
	    {
	       cout << "All toys made and shipped" << endl;
	       cout << nrRecycled << " boxes recycled" << endl;
	    }
	    
	 }
	 if ( nrPacked != count )
	 {
	    cout << nrPacked << " " << color
		 << " toys with diameter " << diameter << " and "
		 << holes << " hole(s) packed"
		 << endl;

	    int nrNotPacked;
	    nrNotPacked = count - nrPacked;

	    cout << nrNotPacked << " " << color
		 << " toys with diameter " << diameter << " and "
		 << holes << " hole(s) not packed"
		 << endl;  
	 }
      }
      
      // box command
      else if ( command == CMD2 )
      {
	 // gather info
	 inStream >> count >> length >> width >> height;
	 cout << "CMD " << command 
	      << " " << count << " " 
	      << length << " " << width 
	      << " " << height << endl << endl;

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
	 truck.Output(cout);
      }

      // deliver command
      else if ( command == CMD4 )
      {
	 // echos and delivers
	 cout << "CMD " << command << endl << endl;
	 truck.Deliver();
      } 
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

   return 0;
}
