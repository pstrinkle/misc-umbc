//---------------------------------------------------
// File       : DeliveryLog.cpp
// Author     : Patrick Trinkle
// Date       : November 5 2004
// UMBC Email : tri1@umbc.edu
// Project    : 4
// Section    : 0101
// Description: Functions That access the
//              members of DeliveryLog Class, Proj3
//---------------------------------------------------

#include "DeliveryLog.h"
#include "DeliveryRecord.h"

#include<vector>
#include<string>
#include<fstream>
#include<iostream>

using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         an object
//---------------------------------------
DeliveryLog::DeliveryLog()
{
   // no code
}

//---------------------------------------
// DeliveryLog::AddRecord
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
void DeliveryLog::AddRecord(const DeliveryRecord& record)
{
   m_records.push_back(record);
}

//---------------------------------------
// Output Operator
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
ostream& operator<<(ostream& out, DeliveryLog& log)
{
   out << endl << "Delivery Log" << endl
       << "------------" << endl;
   if ( log.m_records.size() == 0 )
   {
      out << "No Deliveries" << endl;
   }
   else
   {
      // prints records
      for ( unsigned int i = 0; i < log.m_records.size(); i++ )
      {
	 out << log.m_records.at(i) << endl;
      }
   }
   return out;
}
