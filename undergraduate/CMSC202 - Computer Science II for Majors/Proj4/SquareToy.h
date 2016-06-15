//---------------------------------------------------
// File       : SquareToy.h
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 4
// Section    : 0101
// Description: Functions That access the
//              members of SquareToy Class Used for Proj4
//---------------------------------------------------

#ifndef _SquareToy_h
#define _SquareToy_h

#include "TinkerToy.h"

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class SquareToy: public TinkerToy
{
  public:
   SquareToy(const string& color = "undefined_color", int side = 0, int nrHoles = 0);
   SquareToy& operator=(const SquareToy& rhs);
   virtual ~SquareToy();
   virtual SquareToy* Clone() const;
   virtual void Print() const;
   virtual double Volume() const;
  private:
   int m_side, m_nrHoles;
};

#endif
