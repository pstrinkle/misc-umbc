//---------------------------------------------------
// File       : RoundToy.h
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 4
// Section    : 0101
// Description: Functions That access the
//              members of RoundToy Class Used for Proj4
//---------------------------------------------------

#ifndef _RoundToy_h
#define _RoundToy_h

#include "TinkerToy.h"

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class RoundToy: public TinkerToy
{
  public:
   RoundToy(float diameter = 0, const string& color = "undefined_color", int nrHoles = 0);

   RoundToy& operator=(const RoundToy& rhs); // assign
   virtual ~RoundToy();
   virtual RoundToy* Clone() const;
   virtual void Print() const;
   virtual double Volume() const;

  private:
   float m_diameter;
   int m_nrHoles;
};

#endif
