//---------------------------------------------------
// File       : DeliveryRecord.cpp
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the
//              members of DeliveryRecord for Proj5
//---------------------------------------------------

#include "DeliveryRecord.h"

#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         an object
//---------------------------------------
DeliveryRecord::DeliveryRecord(int numItems, int distance, const string& plantName, const string& info)
{
   m_pNumItems = new int(numItems);
   m_pDistance = new int(distance * 2);
   m_pPlantName = new string(plantName);
   m_pInfo = new string(info);
}

//---------------------------------------
// Destructor
// PreConditions:
//         none
// PostConditions
//         memeory returned to heap
//---------------------------------------
DeliveryRecord::~DeliveryRecord()
{
   // clear variables
   // set return memory
   // nullify pointers

   *m_pNumItems = 0;
   delete m_pNumItems;
   m_pNumItems = 0;

   *m_pDistance = 0;
   delete m_pDistance;
   m_pDistance = 0;

   *m_pPlantName = " ";
   delete m_pPlantName;
   m_pPlantName = 0;

   *m_pInfo = " ";
   delete m_pInfo;
   m_pInfo = 0;
}

//---------------------------------------
// Copy Constructor
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
DeliveryRecord::DeliveryRecord(const DeliveryRecord& rhs)
{
   // copies right hand object into left hand object

   m_pNumItems = new int;
   *m_pNumItems = *(rhs.m_pNumItems);
   m_pDistance = new int;
   *m_pDistance = *(rhs.m_pDistance);
   m_pPlantName = new string;
   *m_pPlantName = *(rhs.m_pPlantName);
   m_pInfo = new string;
   *m_pInfo = *(rhs.m_pInfo);
}

//---------------------------------------
// Assignment Operator
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
DeliveryRecord& DeliveryRecord::operator=(const DeliveryRecord& rhs)
{
   // if they're not the same object
   if ( this != &rhs )
   {
      *m_pNumItems = *(rhs.m_pNumItems);
      *m_pDistance = *(rhs.m_pDistance);
      *m_pPlantName = *(rhs.m_pPlantName);
      *m_pInfo = *(rhs.m_pInfo);
   }
   return *this;
}

//---------------------------------------
// Output Operator (friend)
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
ostream& operator<<(ostream& out, const DeliveryRecord& record)
{
   // prints delivery record
   out << "Delivered to"
       << *(record.m_pPlantName) << setw(10) 
       << *(record.m_pDistance) << "    " << setw(10)
       << *(record.m_pNumItems) << " " << *(record.m_pInfo) << " Delivered";
   return out;
}
