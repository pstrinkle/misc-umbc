//---------------------------------------------------                              
// File       : ListItr.h                                                             
// Author     : Patrick Trinkle                                                    
// Date       : March 2005                                                         
// UMBC Email : tri1@umbc.edu                                                      
// Project    : 2                                                                  
// Section    : 0101                                                               
// Description: The ListItr Class used for Proj2                                      
//---------------------------------------------------


#ifndef _ListItr_H
#define _ListItr_H

// ListItr class; maintains "current position" within a List
//
// CONSTRUCTION: Package friendly only, with a ListNode
//
// ******************PUBLIC OPERATIONS*********************
// bool isPastEnd( )      --> True if past end position in list
// void advance( )        --> Advance (if not already null)
// Object retrieve        --> Return item in current position

#include "dsexceptions.h"
#include "ListNode.h"

// partial calss declarations for friends
template <class Object> class List;

template <class Object>
class ListItr
{
   public:
      ListItr( );
      bool isPastEnd( ) const;
      void advance( );
      const Object & retrieve( ) const;
      bool operator!=(const ListItr<Object>& rhs) const;

   private:
      // current position within the list
      ListNode<Object> *current;

      // private constructor for List to use
      ListItr( ListNode<Object> *theNode );

      friend class List<Object>; // Grant access to constructor
};

#include "ListItr.cpp"

#endif

