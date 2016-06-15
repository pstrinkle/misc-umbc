//---------------------------------------------------
// File       : Truck.h
// Author     : Patrick Trinkle
// Date       : October 13 2004
// UMBC Email : tri1@umbc.edu
// Project    : 2
// Section    : 0101
// Description: Truck Class Used for Proj2
//---------------------------------------------------

#ifndef _Truck_h
#define _Truck_h

#include "Box.h"

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

const string CLR1 = "Red";
const string CLR2 = "White";
const string CLR3 = "Blue";
const string CLR4 = "Orange";
const string CLR5 = "Green";

using namespace std;

class Truck
{
  public:
   Truck();
   void LoadTruck(const Box& box);
   void Output(ostream& out) const;
   void Deliver();
   void SetPlant(int distance, string& plantName);

  private:
   int m_totalmileage, m_distancetoPlant;
   string m_plantName;
   vector<Box> m_boxesintruck;
   vector<Box> m_boxesdelivered;
};



#endif
