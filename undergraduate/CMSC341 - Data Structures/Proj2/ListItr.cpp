//---------------------------------------------------                              
// File       : ListItr.cpp                                                             
// Author     : Patrick Trinkle                                                    
// Date       : March 2005                                                         
// UMBC Email : tri1@umbc.edu                                                      
// Project    : 2                                                                  
// Section    : 0101                                                               
// Description: The ListItr Class used for Proj2                                      
//---------------------------------------------------


// implements the methods of the  ListItr class
// used to represent position within a Linked List


#ifndef _LISTITR_CPP
#define _LISTITR_CPP

#include "ListItr.h"

using namespace std;

// --------------------------------
//  constructor
// --------------------------------
template <class Object>
ListItr<Object>::ListItr( ) : current( NULL )
{
   // no code
}

//---------------------------------
// Private Constructor
//--------------------------------
template <class Object>
ListItr<Object>::ListItr (ListNode<Object> *theNode)
   : current (theNode)
{
   // no code
}

//--------------------------------
// isPastEnd()
// returns true if the iterator represents a 
// data node that is past the end of the List
// i.e., whose position is NULL
//-------------------------------------
template <class Object>
bool ListItr<Object>::isPastEnd( ) const
{
   return current == NULL;
}

template <class Object>
bool ListItr<Object>::operator!=(const ListItr<Object>& rhs) const
{
   bool truth = false;
   if ( current == rhs.current )
      truth = true;

   return truth;
}


//-------------------------------
// advance ( )
//  move to the next node in the LL
// --------------------------------
template <class Object>
void ListItr<Object>::advance( )
{
   if( !isPastEnd( ) )
      current = current->next;
}

//--------------------------------
// retrieve ()
// get a constant reference to the Object
// stored at the current position
// ---------------------------------
template <class Object>
const Object & ListItr<Object>::retrieve( ) const
{
   if( isPastEnd( ) )
      throw BadIterator( );

   return current->element;
}

#endif
