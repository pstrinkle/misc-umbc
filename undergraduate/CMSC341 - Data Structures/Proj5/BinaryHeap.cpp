#ifndef BINARYHEAP_C
#define BINARYHEAP_C

#include "BinaryHeap.h"
using namespace std;

/**
 * Construct the binary heap.
 * capacity is the capacity of the binary heap.
 */
template <class Comparable>
BinaryHeap<Comparable>::BinaryHeap( int capacity )
   : currentSize( 0 ), array( capacity + 1 )
{
}

/**
 * Find item x in the priority queue, returns -1 if not found
 */
template <class Comparable>
int BinaryHeap<Comparable>::find( const Comparable & x ) const
{
   for ( unsigned int i = 0; i < array.size(); ++i )
   {
      if ( x == array[ i ] )
	 return i;
   }
   return -1;
}

template <class Comparable>
void BinaryHeap<Comparable>::printfirstItem( ostream& out, int T )
{
   array[ 1 ].printInfo(out, T);
   return;
}

template <class Comparable>
void BinaryHeap<Comparable>::printChildren( ostream& out )
{
   if ( 2 > currentSize ) // left child 2i
      out << "NULL\t\t";
   else
      array[ 2 ].printID( out ) << "\t\t";

   if ( 3 > currentSize ) // right child 2i + 1
      out << "NULL\t\t";
   else
      array[ 3 ].printID( out ) << "\t\t";

   return;
}


template <class Comparable>
void BinaryHeap<Comparable>::update( int id, int amount )
{
   int found = 0;
   found = find( Job(id) );
   if ( found == -1 )
      return;

   array[ found ] += amount;
   buildHeap();

   return;
}

template <class Comparable>
void BinaryHeap<Comparable>::deleteItem( const Comparable & x )
{
   int found = 0;
   found = find( x );
   if ( found == -1 )
      return;

   //place hole at item
   int hole = found;

   //set last item into hole
   array[ hole ] = array[ currentSize-- ];
   percolateDown( hole );

   return;
}

template <class Comparable>
Comparable & BinaryHeap<Comparable>::LeftChild( int i )
{
   return array[ 2i ];
}

template <class Comparable>
Comparable & BinaryHeap<Comparable>::RightChild( int i )
{
   return array[ 2i + 1 ];
}

/**
 * Insert item x into the priority queue, maintaining heap order.
 * Duplicates are allowed.
 * Throw Overflow if container is full.
 */
template <class Comparable>
void BinaryHeap<Comparable>::insert( const Comparable & x )
{
   if( isFull( ) )
      throw Overflow( );
   
   // Percolate up
   int hole = ++currentSize;
   for( ; hole > 1 && x < array[ hole / 2 ]; hole /= 2 )
      array[ hole ] = array[ hole / 2 ];
   array[ hole ] = x;
}

/**
 * Find the smallest item in the priority queue.
 * Return the smallest item, or throw Underflow if empty.
 */
template <class Comparable>
const Comparable & BinaryHeap<Comparable>::findMin( ) const
{
   if( isEmpty( ) )
      throw Underflow( );
   return array[ 1 ];
}

/**
 * Remove the smallest item from the priority queue.
 * Throw Underflow if empty.
 */
template <class Comparable>
void BinaryHeap<Comparable>::deleteMin( )
{
   if( isEmpty( ) )
      throw Underflow( );
   
   array[ 1 ] = array[ currentSize-- ];
   percolateDown( 1 );
}

/**
 * Remove the smallest item from the priority queue
 * and place it in minItem. Throw Underflow if empty.
 */
template <class Comparable>
void BinaryHeap<Comparable>::deleteMin( Comparable & minItem )
{
   if( isEmpty( ) )
      throw Underflow( );
   
   minItem = array[ 1 ];
   array[ 1 ] = array[ currentSize-- ];
   percolateDown( 1 );
}

/**
 * Establish heap order property from an arbitrary
 * arrangement of items. Runs in linear time.
 */
template <class Comparable>
void BinaryHeap<Comparable>::buildHeap( )
{
   for( int i = currentSize / 2; i > 0; i-- )
      percolateDown( i );
}

/**
 * Test if the priority queue is logically empty.
 * Return true if empty, false otherwise.
 */
template <class Comparable>
bool BinaryHeap<Comparable>::isEmpty( ) const
{
   return currentSize == 0;
}

/**
 * Test if the priority queue is logically full.
 * Return true if full, false otherwise.
 */
template <class Comparable>
bool BinaryHeap<Comparable>::isFull( ) const
{
   return (unsigned)currentSize == array.size( ) - 1;
}

/**
 * Make the priority queue logically empty.
 */
template <class Comparable>
void BinaryHeap<Comparable>::makeEmpty( )
{
   currentSize = 0;
}

/**
 * Internal method to percolate down in the heap.
 * hole is the index at which the percolate begins.
 */
template <class Comparable>
void BinaryHeap<Comparable>::percolateDown( int hole )
{
   /* 1*/      int child;
   /* 2*/      Comparable tmp = array[ hole ];
   
   /* 3*/      for( ; hole * 2 <= currentSize; hole = child )
   {
    /* 4*/          child = hole * 2;
    /* 5*/          if( child != currentSize && array[ child + 1 ] < array[ child ] )
    /* 6*/              child++;
    /* 7*/          if( array[ child ] < tmp )
    /* 8*/              array[ hole ] = array[ child ];
      else
    /* 9*/              break;
   }
   /*10*/      array[ hole ] = tmp;
}


#endif
