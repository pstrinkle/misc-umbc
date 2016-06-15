//---------------------------------------------------
// File       : Proj5.cpp
// Author     : Patrick Trinkle
// Date       : May 2005
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: The Project Main File  used for Proj5
//---------------------------------------------------

#include <string>
#include <iostream>
#include <fstream>

#include "BinaryHeap.h"
#include "Job.h"
#include "JRecord.h"

const string CMD1 = "SubmitJob";
const string CMD2 = "WithdrawJob";
const string CMD3 = "IncreasePrice";

using namespace std;

int averagejobtime( vector<JRecord> & jrecords )
{
   int total = 0;
   for ( unsigned int i = 0; i < jrecords.size(); ++i )
      total += jrecords.at(i).GetTime();

   return total / static_cast<int>( jrecords.size() );
}

int main( int argc, char** argv)
{
   if ( argc != 2)
   {
      cerr << "Not enough arguments." << endl;
      exit(-1);
   }
   ifstream inStream(argv[1]);
   if ( inStream == NULL )
   {
      cerr << "Invalid Input File." << endl;
      exit(-2);
   }

   BinaryHeap<Job> printserver;
   Job deleted(0, 0, 0, 0);
   JRecord least(0, 10);
   JRecord greatest(0, 0);
   vector<JRecord> jobrecords;

   int income, id, size, unitPrice, time, amount, T;
   income = 0;
   id = 0;
   size = 0;
   unitPrice = 0;
   time = 0;
   amount = 0;
   T = 0;
   string command;

// this code isn't needed if the first item's time is always zero
/*
   // Get first item and set system time
   inStream >> command;
   if ( command == CMD1 ) 
   {
      inStream >> id >> size >> unitPrice >> time;
      printserver.insert( Job(id, unitPrice, size, time) );
      T = time;
   }
*/
   cout << "ID\t\t" << "SIZE\t\t" << "TOTAL\t\t" << "TIME IN\t\t" << "LEFT\t\t" << "RIGHT" << endl
   << "\t\t\t\tPAYMENT\t\t" << "SYSTEM\t\t" << "CHILD\t\t" << "CHILD" << endl;

   while ( inStream.good() )
   {
      inStream >> command;

      if ( command == CMD1 )
	 inStream >> id >> size >> unitPrice >> time;
      else if ( command == CMD2 )
	 inStream >> id >> time;
      else // CMD3 due to clean input
	 inStream >> id >> amount >> time;

      if ( time <= T && T != 0 ) // T = time ( process ) maybe?
      {
	 if ( command == CMD1 )
	    printserver.insert( Job(id, unitPrice, size, time) );
	 else if ( command == CMD2 )
	    printserver.deleteItem( Job(id) );
	 else
	    printserver.update(id, amount);
      }
      else // item time > T
      {
	 while ( time > T && T != 0 )
	 {
	    if ( !printserver.isEmpty() )
	    {
	       deleted = printserver.findMin();
	       printserver.printfirstItem( cout, T );
	       printserver.printChildren( cout );
	       cout << endl;
	       printserver.deleteMin();
	       //check time in system
	       JRecord temp( deleted.GetID(), (T - deleted.GetTime()) );
	       if ( T - deleted.GetTime() > greatest.GetTime() )
		  greatest = temp;
	       else if ( T - deleted.GetTime() < least.GetTime() )
		  if ( least.GetTime() > greatest.GetTime() )
		       greatest = least;
		  else
		     least = temp;

	       // add to total jobrecords vector
	       jobrecords.push_back(temp);

	       income += deleted.GetPayment();
	       T += deleted.GetSize();
	    }
	    else
	       T = 0;
	 }
	 
	 // either the above ran or T == 0
	 if ( command == CMD1 )
	 {
	    T = time;
	    printserver.insert( Job(id, unitPrice, size, time) );
	 }
	 else if ( command == CMD2 )
	    printserver.deleteItem( Job(id) );
	 else
	    printserver.update(id, amount);
      }
   }

   inStream.close();
   printserver.makeEmpty();

   cout << endl << endl;
   cout << "JOB " << least.GetID() << " HAS THE SHORTEST TIME STAYING IN THE SYSTEM OF " << least.GetTime() << endl
	<< "JOB " << greatest.GetID() << " HAS THE LONGEST TIME STAYING IN THE SYSTEM OF " << greatest.GetTime() << endl;

   cout << endl;
   cout << "THE AVERAGE TIME A JOB STAYED IN THE SYSTEM IS " << averagejobtime(jobrecords) << endl << endl;

   return 0;
}

