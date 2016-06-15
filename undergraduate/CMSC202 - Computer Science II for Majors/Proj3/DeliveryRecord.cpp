//---------------------------------------------------
// File       : DeliveryRecord.cpp
// Author     : Patrick Trinkle
// Date       : November 5 2004
// UMBC Email : tri1@umbc.edu
// Project    : 3
// Section    : 0101
// Description: Functions That access the
//              members of DeliveryRecord for Proj3
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
DeliveryRecord::DeliveryRecord(int numBoxes, int distance, const string& plantName)
{
   m_pNumBoxes = new int(numBoxes);
   m_pDistance = new int(distance * 2);
   m_pPlantName = new string(plantName);
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

   *m_pNumBoxes = 0;
   delete m_pNumBoxes;
   m_pNumBoxes = 0;

   *m_pDistance = 0;
   delete m_pDistance;
   m_pDistance = 0;

   *m_pPlantName = " ";
   delete m_pPlantName;
   m_pPlantName = 0;
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

   m_pNumBoxes = new int;
   *m_pNumBoxes = *(rhs.m_pNumBoxes);
   m_pDistance = new int;
   *m_pDistance = *(rhs.m_pDistance);
   m_pPlantName = new string;
   *m_pPlantName = *(rhs.m_pPlantName);
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
      delete m_pNumBoxes;
      m_pNumBoxes = new int;
      *m_pNumBoxes = *(rhs.m_pNumBoxes);

      delete m_pDistance;
      m_pDistance = new int;
      *m_pDistance = *(rhs.m_pDistance);

      delete m_pPlantName;
      m_pPlantName = new string;
      *m_pPlantName = *(rhs.m_pPlantName);
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
       << *(record.m_pNumBoxes) << " boxes Delivered";
   return out;
}
