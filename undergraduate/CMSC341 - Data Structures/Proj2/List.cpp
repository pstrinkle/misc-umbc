//---------------------------------------------------                              
// File       : List.cpp                                                             
// Author     : Patrick Trinkle                                                    
// Date       : March 2005                                                         
// UMBC Email : tri1@umbc.edu                                                      
// Project    : 2                                                                  
// Section    : 0101                                                               
// Description: The List Class used for Proj2                                      
//---------------------------------------------------


//
// Implements the methods of the Linked List implementation
// of the List ADT


#ifndef _LIST_CPP
#define _LIST_CPP

#include "List.h"

using namespace std;


//-------------------------
// Construct an empty list.
//------------------------
template <class Object>
List<Object>::List( )
   :m_access(0)
{
   header = new ListNode<Object>;
}

//-------------------------
// Copy constructor
//  note use of operator=
//-------------------------
template <class Object>
List<Object>::List( const List<Object> & rhs )
{
   header = new ListNode<Object>;
   *this = rhs;
}

//-------------
// Destructor
//------------------
template <class Object>
List<Object>::~List( )
{
   makeEmpty( );
   delete header;
}

//----------------------------------
// isEmpty ( )
// Test if the list is logically empty.
// Return true if empty, false, otherwise.
//--------------------------------------
template <class Object>
bool List<Object>::isEmpty( ) const
{
   return header->next == NULL;
}


//-------------------------------
// makeEmpty ( )
// Make the list logically empty.
//-------------------------------
template <class Object>
void List<Object>::makeEmpty( )
{
   while( !isEmpty( ) )
      remove( first( ).retrieve( ) );
}

//---------------------------------------------
// zeroth()
// Return an iterator representing the header node.
//-----------------------------------------------
template <class Object>
ListItr<Object> List<Object>::zeroth( ) const
{
   return ListItr<Object>( header );
}

//---------------------------------------------------------
// first()
// Return an iterator representing the first node in the list.
// This operation is valid for empty lists.
//------------------------------------------------------------
template <class Object>
ListItr<Object> List<Object>::first( ) const
{
   return ListItr<Object>( header->next );
}

//------------------------
// insert (x, p)
// Insert item x after p.
//--------------------------        
template <class Object>
void List<Object>::insert( const Object & x, const ListItr<Object> & p )
{
   if( p.current != NULL )
      p.current->next = new ListNode<Object>( x, p.current->next );
}

//---
// replace
//-----------
template <class Object>
void List<Object>::replace( const Object & x, const ListItr<Object> & p )
{
   if( p.current != NULL )
     p.current->element = x;
}

template <class Object>
ListItr<Object> List<Object>::last( ) const
{
   ListNode<Object> *itr = header;

   while ( itr->next != NULL )
      itr = itr->next;

   return ListItr<Object>( itr );
}

//-------------------------------------------------
// find (Object x)
// Return iterator corresponding to the first node containing an item x.
// Iterator isPastEnd if item is not found.
//-------------------------------------------------------
template <class Object>
ListItr<Object> List<Object>::find( const Object & x )
{
   ListNode<Object> *itr = header->next;

   // assumes 'short circut' of &&
   while( itr != NULL && itr->element != x )
   {
      itr = itr->next;
      m_access++;
   }

   return ListItr<Object>( itr );
}

//---------------------------
// findPrevious (Object x)
// Return iterator prior to the first node containing an item x.
// Needed by remove ()
//----------------------------
template <class Object>
ListItr<Object> List<Object>::findPrevious( const Object & x ) const
{
   ListNode<Object> *itr = header;

   while( itr->next != NULL && itr->next->element != x )
      itr = itr->next;

   return ListItr<Object>( itr );
}

//----------------------------------------
// remove (Object x)
// Remove the first occurrence of an item x.
//---------------------------------------
template <class Object>
void List<Object>::remove( const Object & x )
{
   ListItr<Object> p = findPrevious( x );

   if( p.current->next != NULL )
   {
      ListNode<Object> *oldNode = p.current->next;
      p.current->next = p.current->next->next;  // Bypass deleted node
      delete oldNode;
   }
}

//----------------------------------------------
// Assignment Operator
//    Deep copy of linked lists.
// ----------------------------------------------
template <class Object>
const List<Object> & List<Object>::operator=( const List<Object> & rhs )
{
  if( this != &rhs )
   {
      makeEmpty( );

      ListItr<Object> ritr = rhs.first( );
      ListItr<Object> itr = zeroth( );
      for( ; !ritr.isPastEnd( ); ritr.advance( ), itr.advance( ))
	      insert( ritr.retrieve( ), itr );

      return *this;
   }
}

template <class Object>
int List<Object>::GetTotal() const
{
   return m_access;
}

template <class Object>
void List<Object>::ResetTotal()
{
   m_access = 0;
}



#endif
