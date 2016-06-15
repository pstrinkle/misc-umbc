//---------------------------------------------------                   
// File       : Proj1.cpp
// Author     : Patrick Trinkle                                         
// Date       : February 2005                                        
// UMBC Email : tri1@umbc.edu                                           
// Project    : 1
// Section    :   
// Description: The Main File used for Proj1                          
//---------------------------------------------------                    

#include "Electronics.h"
#include "Stocks.h"

#include "Inventory.h"

#include "Proj1Aux.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

const string CMD1 = "CASHINIT";
const string CMD2 = "BUY";
const string CMD3 = "SELL";
const string CMD4 = "COUNTLIST";
const string CMD5 = "PRINTLIST";
const string CMD6 = "CASHBALANCE";
const string TYPE1 = "Electronics";
const string TYPE2 = "Stocks";


using namespace std;

int main( int argc, char** argv)
{
   if ( argc != 3 )
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
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   string type;

   Inventory<Electronics> Invent_e;
   Inventory<Stocks> Invent_s;
   
   if ( strcmp(argv[1], "Electronics") == 0 )
      type = "Electronics";
   else if ( strcmp(argv[1], "Stocks") == 0 )
      type = "Stocks";
   else
   {
      cerr << "Invalid Inventory Type" << endl;
      exit(-3);
   }

   string command, name;
   double buyPrice = 0;
   double cash = 0;
   int numUnits = 0;

   while ( inStream >> command )
   {
      if ( command == CMD1 ) // CASHINIT
      {
	 inStream >> cash;

	 if ( type == TYPE1 )
	    Invent_e.SetCash(cash);
	 else
	    Invent_s.SetCash(cash);

	 cout << "Cmd: " << command << " " << cash << endl;
      }

      else if ( command == CMD2 ) // BUY
      {
	 inStream >> name >> numUnits >> buyPrice;
	 Electronics buy_e(name, numUnits, buyPrice);
	 Stocks buy_s(name, numUnits, buyPrice);

	 try 
	 {
	    if ( type == TYPE1 )
	       Invent_e += buy_e;
	    else
	       Invent_s += buy_s;
	 }
	 catch( const NotEnoughCash& exception )
	 {
	    cout << "Error message: there isn't enough cash to complete this order." << endl;
	 }
      }
      
      else if ( command == CMD3 ) // SELL
      {
	 inStream >> name >> numUnits;
	 Electronics sell_e(name, numUnits);
	 Stocks sell_s(name, numUnits);

	 try
	 {
	    if ( type == TYPE1 )
	       Invent_e -= sell_e;
	    else
	       Invent_s -= sell_s;
	 }
	 catch( const NoneToSell& exception )
	 {
	    cout << "Error message: there isn't enough units of " << exception.Info() << " to complete this order" << endl;
	 }
      }

      else if ( command == CMD4 ) // COUNTLIST
      {
	 cout << "Cmd: " << command << endl
	      << "     " << "The number of distinct products in the inventory is ";
	    if ( type == TYPE1 )
	      cout << Invent_e.NumItems() << endl;
	    else
	       cout << Invent_s.NumItems() << endl;
      }
      
      else if ( command == CMD5 ) // PRINTLIST
      {
	 cout << "Cmd: " << command << endl;
	 if ( type == TYPE1 )
	    cout << Invent_e;
	 else
	    cout << Invent_s;     
      }
      
      else if ( command == CMD6 ) // CASHBALANCE
      {
	 cout << "Cmd: " << command << endl
	      << "     " << "The current cash balance is ";
	 if ( type == TYPE1 )
	      cout << Invent_e.GetCash() << endl;
	 else
	    cout << Invent_s.GetCash() << endl;
      }

   }
   inStream.close();

   return 0;
}
