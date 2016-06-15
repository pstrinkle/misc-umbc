//---------------------------------------------------
// File       : Box.h
// Author     : Patrick Trinkle
// Date       : November 27 2004
// UMBC Email : tri1@umbc.edu
// Project    : 4
// Section    : 0101
// Description: The Box Class Used for Proj3
//---------------------------------------------------

#ifndef _Box_h
#define _Box_h

#include "TinkerToy.h"

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
   const TinkerToy* GetToy(int i) const; 
   unsigned int NumToys() const;

   // the box +=
   const Box& operator+=(TinkerToy* toy);
   // the copy constructor
   Box(const Box& rhs);
   // assignment operator
   Box& operator=(const Box& rhs);
   ~Box();

  private:
   int m_length, m_width, m_height;
   vector<TinkerToy*> m_toysinbox;

   int GetLength() const;
   int GetWidth() const;
   int GetHeight() const;
};

ostream& operator<<(ostream& out, const Box& box);


#endif
