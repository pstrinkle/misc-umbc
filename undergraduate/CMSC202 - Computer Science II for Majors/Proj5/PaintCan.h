//---------------------------------------------------
// File       : PaintCan.h
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: The PaintCan Class Used for Proj5
//---------------------------------------------------


#ifndef _PaintCan_h
#define _PaintCan_h

#include <iomanip>
#include <string>
#include <iostream>

using namespace std;

class PaintCan
{
   friend ostream& operator<<(ostream& out, const PaintCan& can);

  public:
   PaintCan(int gallons, const string& color);

  private:
   int m_gallons;
   string m_color;
};

#endif
