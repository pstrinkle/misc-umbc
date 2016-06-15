//------------------------------------------------
// Edit 27 Jan 2003 DLF namespace std for g++ v3.2
//------------------------------------------------

#ifndef _QUADRATIC_PROBING_H_
#define _QUADRATIC_PROBING_H_

#include <vector>
#include <string>
#include <iomanip>
#include "HashingAux.h"

using namespace std;


// QuadraticProbing Hash table class
//
// CONSTRUCTION: an initialization for ITEM_NOT_FOUND
//               and an approximate initial size or default of 101
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// Hashable find( x )     --> Return item that matches x
// void makeEmpty( )      --> Remove all items


template <class HashedObj>
class HashTable
{
   public:
      explicit HashTable( const HashedObj & notFound, int size = 101 );
      HashTable( const HashTable & rhs )
	 : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
	   array( rhs.array ), currentSize( rhs.currentSize ), probeCount( rhs.probeCount ), distinctCount( rhs.distinctCount ), occurCount( rhs.occurCount ), insertCount( rhs.insertCount ) { }
      
      const HashedObj & find( const HashedObj & x );

      void makeEmpty( );
      void insert( const HashedObj & x );
      void remove( const HashedObj & x );

      double avgwordFreq( ) const
	 {
	    return static_cast<double> ( 1 ) / static_cast<double> ( distinctCount );
	 }
      void top20( ostream& out ) const;
      void print( ostream& out ) const;
      void printInfo( int when );
      
      const HashTable & operator=( const HashTable & rhs );
      
      enum EntryType { ACTIVE, EMPTY, DELETED };
      
   private:
      struct HashEntry
      {
	    HashedObj element;
	    EntryType info;
	    int m_occurrence;
	    
	    HashEntry( const HashedObj & e = HashedObj( ), EntryType i =EMPTY, int occur = 0 )
	       : element( e ), info( i ), m_occurrence( occur ) { }
      };
      
      bool operator<( const HashEntry & rhs );
      const HashedObj ITEM_NOT_FOUND;
      vector<HashEntry> array;
      unsigned int currentSize;
      int probeCount;
      int distinctCount;
      int occurCount;
      int insertCount;

      bool isActive( int currentPos ) const;
      int findPos( const HashedObj & x );
      void rehash( );
};

#include "QuadProbing.cpp"
#endif


