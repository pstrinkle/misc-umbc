//---------------------------------------------------
// File       : Box.h
// Author     : Patrick Trinkle
// Date       : October 13 2004
// UMBC Email : tri1@umbc.edu
// Project    : 2
// Section    : 0101
// Description: The Box Class Used for Proj2
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
   Box(int length, int width, int height);
   double Unused() const;
   bool Store(const RoundToy& toy);
   const RoundToy& GetToy(int i) const; 
   unsigned int NumToys() const;

  private:
   int m_length, m_width, m_height;
   vector<RoundToy> m_toysinbox;
};




#endif
