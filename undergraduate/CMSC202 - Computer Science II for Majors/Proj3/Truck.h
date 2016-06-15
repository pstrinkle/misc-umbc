//---------------------------------------------------
// File       : Truck.h
// Author     : Patrick Trinkle
// Date       : November 5 2004
// UMBC Email : tri1@umbc.edu
// Project    : 3
// Section    : 0101
// Description: Truck Class Used for Proj3
//---------------------------------------------------

#ifndef _Truck_h
#define _Truck_h

#include "Box.h"
#include "DeliveryLog.h"
#include "DeliveryRecord.h"

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Truck
{
  public:
   Truck();
   void Deliver();
   const Box& GetBox(int i) const;
   int NumBoxes() const;
   
   // retrieve the log
   DeliveryLog& GetLog();
   // operator +=
   const Truck operator+=(Box& box);

  private:
   vector<Box> m_boxesintruck;
   DeliveryLog m_Deliveries;
};

ostream& operator<<(ostream& out, Truck& truck);

#endif
