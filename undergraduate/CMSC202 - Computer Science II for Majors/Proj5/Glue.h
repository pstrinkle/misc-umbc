//---------------------------------------------------
// File       : Glue.h
// Author     : Patrick Trinkle
// Date       : December 08 2004
// UMBC Email : tri1@umbc.edu
// Project    : 5
// Section    : 0101
// Description: The Glue Class Used for Proj5
//---------------------------------------------------


#ifndef _Glue_h
#define _Glue_h

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Glue
{
   friend ostream& operator<<(ostream& out, const Glue& glue);

  public:
   Glue(const string& type);

  private:
   string m_type;
};

#endif
