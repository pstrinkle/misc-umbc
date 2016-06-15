//---------------------------------------------------                            
// File       : List.h                                                         
// Author     : Patrick Trinkle                                                  
// Date       : March 2005                                                    
// UMBC Email : tri1@umbc.edu                                                    
// Project    : 2                                                         
// Section    : 0101                                                         
// Description: The List Class used for Proj2
//---------------------------------------------------


#ifndef _LinkedList_H
#define _LinkedList_H

#include <iostream>    // For NULL
#include "ListItr.h"
#include "ListNode.h"


using namespace std;

template <class Object>
class List
{
  public:
   List( );
   List( const List & rhs );
   ~List( );
   
   bool isEmpty( ) const;
   void makeEmpty( );
   ListItr<Object> zeroth( ) const;
   ListItr<Object> first( ) const;
   ListItr<Object> last ( ) const;
   void insert( const Object & x, const ListItr<Object> & p );
   void replace(const Object & x, const ListItr<Object> & p );
   ListItr<Object> find( const Object & x );
   ListItr<Object> findPrevious( const Object & x ) const;
   void remove( const Object & x );
   const List & operator=( const List & rhs );
   int GetTotal() const;
   void ResetTotal();
   
  private:
   ListNode<Object> *header;
   int m_access;
};

#include "List.cpp"

#endif

