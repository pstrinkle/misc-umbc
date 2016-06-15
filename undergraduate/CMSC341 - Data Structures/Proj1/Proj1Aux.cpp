//---------------------------------------------------                   
// File       : Proj1Aux.cpp
// Author     : Patrick Trinkle                                         
// Date       : February 2005                                        
// UMBC Email : tri1@umbc.edu                                           
// Project    : 1
// Section    : 0101
// Description: The Exception Classes used for Proj1                          
//---------------------------------------------------                    


#include "Proj1Aux.h"

using namespace std;

// default constructor
NoneToSell::NoneToSell(string name)
   :m_name(name)
{
   // no code
}

// information function
const string& NoneToSell::Info() const
{
   return m_name;
}

// default constructor
NotEnoughCash::NotEnoughCash()
{
   // no code
}
