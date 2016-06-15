//---------------------------------------------------
// File       : DeliveryRecord.h
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: The DeliveryRecord Class for Proj5
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
   DeliveryRecord(int numItems = 0, int distance = 0, const string& plantName = "undefined_name", const string& info = "undefined_info");

   //copy constructor
   DeliveryRecord(const DeliveryRecord& rhs);
   //destructor
   ~DeliveryRecord();
   //assignment
   DeliveryRecord& operator=(const DeliveryRecord& rhs);

  private:
   int * m_pNumItems;
   string * m_pPlantName;
   string * m_pInfo;
   int * m_pDistance;
};

#endif
