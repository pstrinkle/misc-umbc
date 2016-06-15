//---------------------------------------------------
// File       : DeliveryRecord.h
// Author     : Patrick Trinkle
// Date       : November 5 2004
// UMBC Email : tri1@umbc.edu
// Project    : 3
// Section    : 0101
// Description: The DeliveryRecord Class for Proj3
//---------------------------------------------------

#ifndef _DeliveryRecord_h
#define _DeliveryRecord_h

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class DeliveryRecord
{
   friend ostream& operator<<(ostream& out, const DeliveryRecord& record);

  public:
   DeliveryRecord(int numBoxes = 0, int distance = 0, const string& plantName= "undefined_name");

   //copy constructor
   DeliveryRecord(const DeliveryRecord& rhs);
   //destructor
   ~DeliveryRecord();
   //assignment
   DeliveryRecord& operator=(const DeliveryRecord& rhs);

  private:
   int * m_pNumBoxes;
   string * m_pPlantName;
   int * m_pDistance;
};

#endif
