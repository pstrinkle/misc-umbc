//---------------------------------------------------                              
// File       : ListNode.h                                                             
// Author     : Patrick Trinkle                                                    
// Date       : March 2005                                                         
// UMBC Email : tri1@umbc.edu                                                      
// Project    : 2                                                                  
// Section    : 0101                                                               
// Description: The ListNode Class used for Proj2                                      
//---------------------------------------------------


#ifndef _ListNode_H
#define _ListNode_H

#include <iostream>    // For NULL

using namespace std;

// friend class partial declarations
template <class Object> class List;
template <class Object> class ListItr;

// the Singly-Linked ListNode class
template <class Object>
class ListNode
{
   private:
      // constructor
      ListNode( const Object & theElement = Object( ), ListNode * n = NULL)
	 :element(theElement), next(n) {};

      // the data
      Object   element;

      // Link to next node
      ListNode *next;

      friend class List<Object>;
      friend class ListItr<Object>;
};

#endif

