//---------------------------------------------------
// File       : DeliveryLog.h
// Author     : Patrick Trinkle
// Date       : November 5 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: The DeliveryLog Class Used for Proj5
//---------------------------------------------------

#ifndef _DeliveryLog_h
#define _DeliveryLog_h

#include "DeliveryRecord.h"

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class DeliveryLog
{
   friend ostream& operator<<(ostream& out, DeliveryLog& log);

  public:
   DeliveryLog();
   void AddRecord(const DeliveryRecord& record);

  private:
   vector<DeliveryRecord> m_records;
};




#endif
