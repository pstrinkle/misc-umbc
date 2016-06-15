#ifndef _BINARY_HEAP_H_
#define _BINARY_HEAP_H_

#include "Job.h"
#include <vector>
using namespace std;

// BinaryHeap class
//
// CONSTRUCTION: with an optional capacity (that defaults to 100)
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// deleteMin( minItem )   --> Remove (and optionally return) smallest item
// Comparable findMin( )  --> Return smallest item
// bool isEmpty( )        --> Return true if empty; else false
// bool isFull( )         --> Return true if full; else false
// void makeEmpty( )      --> Remove all items
// ******************ERRORS********************************
// Throws Underflow and Overflow as warranted

class Underflow{};
class Overflow {};

template <class Comparable>
class BinaryHeap
{
   public:
      explicit BinaryHeap( int capacity = 100 );
      
      bool isEmpty( ) const;
      bool isFull( ) const;
      const Comparable & findMin( ) const;
      
      void insert( const Comparable & x );
      void deleteMin( );
      void deleteMin( Comparable & minItem );
      void makeEmpty( );
      void deleteItem( const Comparable & x );
      int find( const Comparable & x ) const;
      void update( int id, int amount );
      Comparable & LeftChild( int i );
      Comparable & RightChild( int i );
      void printfirstItem( ostream& out, int T );
      void printChildren( ostream& out );
     
   private:
      int                currentSize;  // Number of elements in heap
      vector<Comparable> array;        // The heap array
      
      void buildHeap( );
      void percolateDown( int hole );
};

#include "BinaryHeap.cpp"
#endif
