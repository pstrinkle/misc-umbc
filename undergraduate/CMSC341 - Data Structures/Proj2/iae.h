//---------------------------------------------------                              
// File       : IAE.h                                                             
// Author     : Patrick Trinkle                                                    
// Date       : March 2005                                                         
// UMBC Email : tri1@umbc.edu                                                      
// Project    : 2                                                                  
// Section    : 0101                                                               
// Description: The IAE Class used for Proj2                                      
//---------------------------------------------------


#ifndef IAE_H_
#define IAE_H_

#include "List.h"

using namespace std;

template<class Object>
class Iae
{
  public:
   Iae();
   Iae(const Iae<Object>& iae);
   ~Iae();
   bool isEmpty() const;

   void makeEmpty();

   ListItr<Object> find(const Object& x);

   void insertAtBack(const Object& x);

   const Iae& operator=(const Iae<Object>& iae);

   int GetTotal() const;

   void ResetTotal();
   
  private:
   List<Object> m_theList;
};

#include "iae.cpp"

#endif
