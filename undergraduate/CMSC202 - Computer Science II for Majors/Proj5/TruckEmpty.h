//---------------------------------------------------
// File       : TruckEmpty.h
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: The TruckEmpty Exception  Class Used 
//              for Proj5
//---------------------------------------------------

#ifndef _TruckEmpty_h
#define _TruckEmpty_h

#include <string>
#include <iomanip>
#include <iostream>

using namespace std;

class TruckEmpty
{

  public:
   TruckEmpty(int miles, const string& dest, const string& type);
   string What() const;
   int GetMiles() const;

  private:
   int m_mileage;
   string m_destination;
   string m_type;

};

#endif
