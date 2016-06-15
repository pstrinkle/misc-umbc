//---------------------------------------------------
// File       : Box.h
// Author     : Patrick Trinkle
// Date       : November 5 2004
// UMBC Email : tri1@umbc.edu
// Project    : 3
// Section    : 0101
// Description: The Box Class Used for Proj3
//---------------------------------------------------

#ifndef _Box_h
#define _Box_h

#include "RoundToy.h"

#include<iomanip>
#include<vector>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Box
{
  public:
   Box(int length = 1, int width = 1, int height = 1);
   double Unused() const;
   const RoundToy& GetToy(int i) const; 
   unsigned int NumToys() const;

   // the box +=
   const Box operator+=(const RoundToy& toy);

  private:
   int m_length, m_width, m_height;
   vector<RoundToy> m_toysinbox;

   int GetLength() const;
   int GetWidth() const;
   int GetHeight() const;
};

ostream& operator<<(ostream& out, const Box& box);


#endif
