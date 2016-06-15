//---------------------------------------------------
// File       : RoundToy.h
// Author     : Patrick Trinkle
// Date       : October 13 2004
// UMBC Email : tri1@umbc.edu
// Project    : 2
// Section    : 0101
// Description: RoundToy Class Used for 
//              Proj2
//---------------------------------------------------


#ifndef _RoundToy_h
#define _RoundToy_h

#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

const double PI = 3.14159265359;

class RoundToy
{
  public:
   RoundToy(double diameter, string& color, int nrHoles);
   double Diameter() const;
   string Color() const;
   int Holes() const;   
   double Volume() const;

  private:
   double m_diameter;
   string m_color;
   int m_holes;

};




#endif
