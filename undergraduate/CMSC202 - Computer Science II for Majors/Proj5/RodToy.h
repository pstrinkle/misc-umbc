//---------------------------------------------------
// File       : RodToy.h
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: Functions That access the
//              members of RodToy Class Used for Proj5
//---------------------------------------------------

#ifndef _RodToy_h
#define _RodToy_h

#include "TinkerToy.h"

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class RodToy: public TinkerToy
{
  public:
   RodToy(const string& color = "undefined_color", int length = 0);
   RodToy& operator=(const RodToy& rhs);
   virtual ~RodToy();
   virtual RodToy* Clone() const;
   virtual void Print() const;
   virtual double Volume() const;
  private:
   int m_length;
};

#endif
