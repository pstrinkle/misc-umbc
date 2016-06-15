//---------------------------------------------------
// File       : TinkerToy.h
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 4
// Section    : 0101
// Description: Functions That access the
//              members of TinkerToy Class Used for Proj4
//---------------------------------------------------


#ifndef _TinkerToy_h
#define _TinkerToy_h

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

const double PI = 3.14159265359;

using namespace std;

class TinkerToy
{
  public:
   TinkerToy(const string& color); // constructor
   TinkerToy& operator=(const TinkerToy& rhs); // asignment operator
   TinkerToy(const TinkerToy& rhs);
   virtual ~TinkerToy();
   virtual TinkerToy* Clone() const = 0; // no code!
   virtual void Print() const = 0; // no code!
   virtual double Volume() const = 0; // no code!
   static int NumConstructed();
   static int NumDestroyed();
   
  protected:
   string GetColor() const;

  private:
   static int m_numcon;
   static int m_numdes;
   string m_color;
};

#endif
