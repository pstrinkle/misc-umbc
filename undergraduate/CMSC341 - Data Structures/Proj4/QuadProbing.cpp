//-------------------------------------------------
// Edit: 27 Jan 2003 DLF namespace std for g++ v3.2
//-------------------------------------------------

#ifndef _QUADPROBING_C_
#define _QUADPROBING_C_

#include "QuadProbing.h"
#include <iostream>
#include "HashingAux.h"

using namespace std;

/**
 * Construct the hash table.
 */
template <class HashedObj>
HashTable<HashedObj>::HashTable( const HashedObj & notFound, int size )
   : ITEM_NOT_FOUND( notFound ), array( nextPrime( size ) ), probeCount( 0 ), distinctCount( 0 ), occurCount( 0 ), insertCount( 0 )
{
   makeEmpty( );
}

template <class HashedObj>
void HashTable<HashedObj>::print( ostream& out ) const
{
   for ( unsigned int i = 0; i < array.size(); ++i )
   {
      if ( isActive( i ) )
	 cout << i << " " << array[ i ].element << " : " << array[ i ].m_occurrence << endl;
   }
}

template <class HashedObj>
bool HashTable<HashedObj>::operator<( const HashEntry &rhs )
{
   if ( m_occurrence < rhs.m_occurrence )
      return true;
   return false;
}

template <class HashedObj>
void HashTable<HashedObj>::printInfo( int when )
{
   if ( when == 4 )
   {
      // lambda = .25
      cout << endl << "Average # of probings per attempted insertion." << endl;
      cout << "current table size : " << array.size() << endl;
      cout << "# distinct words   : " << distinctCount << endl;
      cout << "lambda = 0.25      : " << static_cast<double> ( probeCount ) / static_cast<double> ( insertCount ) << endl;
   }

   else if ( when == 2 )
   {
      // lambda = 0.5
      cout << "lambda = 0.5       : " << static_cast<double> ( probeCount ) / static_cast<double> ( insertCount ) << endl;
   }

   else if ( when == 0 )
   {
      // before rehashing
      cout << "before rehashing   : " << static_cast<double> ( probeCount ) / static_cast<double> ( insertCount ) << endl;
   }

   else
   {
      // end of execution
      cout << endl << "After execution :" << endl;
      cout << "current table size : " << array.size() << endl;
      cout << "# distinct words   : " << distinctCount << endl;
      cout << "average            : " << static_cast<double> ( probeCount ) / static_cast<double> ( insertCount ) << endl;
   }

   insertCount = 0;
   probeCount = 0;
}

template <class HashedObj>
void HashTable<HashedObj>::top20( ostream& out ) const
{
   
   // initialize 20 top holdings
   vector<HashEntry> top20( 20, HashEntry( "empty", ACTIVE, 0 ) );

   
   // traverse hashtable
   for ( unsigned int i = 0; i < array.size(); ++i )
   {
      if ( array[ i ].m_occurrence != 0 ) // check to see if array[ i ] has element
      {
	 for ( unsigned int j = 0; j < 20; ++j )
	 {
	    if ( array[ i ].m_occurrence > top20[ j ].m_occurrence && j != 19 && array[ i ].m_occurrence < top20[ j + 1 ].m_occurrence )
	    {
	       for ( unsigned int k = 0; k < j - 1; ++k )
	       {
		  top20[ k ] = top20[ k + 1 ]; // push back
	       }
	       top20[ j ] = array[ i ];
	       j = 100;
	    }

	    else if ( array[ i ].m_occurrence > top20[ j ].m_occurrence && j == 19 )
	    {
	       for ( unsigned int z = 0; z < j; ++z )
	       {
		  top20[ z ] = top20[ z + 1 ];
	       }
	       top20[ j ] = array[ i ];
	       j = 100;
	    }

	    else if ( array[ i ].m_occurrence == top20[ j ].m_occurrence && j > 0 )
	    {
	       // insert behind
	       for ( unsigned int u = 0; u < j; ++u)
	       {
		  top20[ u ] = top20[ u + 1 ];
	       }
	       top20[ j - 1 ] = array[ i ];
	       j = 100;
	    }
	    else
	    {
	       // do nill
	    }
	 }
      }
   }

   // print in descending order
   out << setw(10) << "Word" << setw(10) << "Occurrence " << setw(10) << "Frequency" << endl;
   out << "-----------------------------------------------" << endl;
   for ( int f = 19; f > -1; --f )
      out << setw(10) << top20[ f ].element << setw(10) << top20[ f ].m_occurrence 
	  << setw(10) << static_cast<double> ( top20[ f ].m_occurrence ) / static_cast<double> ( occurCount ) << endl; 



}


/**
 * Insert item x into the hash table. If the item is
 * already present, then increment the occurance
 */
template <class HashedObj>
void HashTable<HashedObj>::insert( const HashedObj & x )
{
   // Insert x as active
   int currentPos = findPos( x );

   if( isActive( currentPos ) )
   {
      array[ currentPos ].m_occurrence++;
      occurCount++;
      insertCount++;
      return;
   }
   array[ currentPos ] = HashEntry( x, ACTIVE, 1 );
   distinctCount++;
   insertCount++;


   if ( ( currentSize + 1 ) == ( array.size() / 4 ) )
      printInfo( 4 );
   if ( ( currentSize + 1 ) == ( array.size() / 2 ) )
      printInfo( 2 );

   // Rehash; see Section 5.5
   if( ++currentSize > static_cast<double> ( array.size( ) ) * 0.8 )
      rehash( );
}

/**
 * Expand the hash table.
 */
template <class HashedObj>
void HashTable<HashedObj>::rehash( )
{
   printInfo( 0 );

   vector<HashEntry> oldArray = array;

   // Create new double-sized, empty table
   array.resize( nextPrime( 2 * oldArray.size( ) ) );
   for( unsigned int j = 0; j < array.size( ); j++ )
      array[ j ].info = EMPTY;
   
   // Copy table over
   currentSize = 0;
   for( unsigned int i = 0; i < oldArray.size( ); i++ )
   {
      if( oldArray[ i ].info == ACTIVE )
      {
	 int currentPos = findPos( oldArray[ i ].element );
	 array[ currentPos ] = HashEntry( oldArray[ i ].element, ACTIVE, oldArray[ i ].m_occurrence );
	 currentSize++;
	 insertCount++;

	 if ( ( currentSize + 1 ) == ( array.size() / 4 ) )
	    printInfo( 4 );
	 if ( ( currentSize + 1 ) == ( array.size() / 2 ) )
	    printInfo( 2 );

      }
   }
}

/**
 * Method that performs quadratic probing resolution.
 * Return the position where the search for x terminates.
 */
template <class HashedObj>
int HashTable<HashedObj>::findPos( const HashedObj & x )
{
   int collisionNum = 0;
   vector<unsigned int> visited;
   bool visit = false;

   unsigned int currentPos = hash( x, array.size( ) );
   visited.push_back( currentPos );

   while( array[ currentPos ].info != EMPTY && array[ currentPos ].element != x )
   {
      probeCount++;
      currentPos += 2 * ++collisionNum - 1;  // Compute ith probe
      if( currentPos >= array.size( ) )
	 currentPos -= array.size( );

      // check to see if visited already
      for ( unsigned int i = 0; i < visited.size(); ++i )
	 if ( currentPos == visited.at(i) )
	    visit = true;

      if ( visit == false )
	 visited.push_back(currentPos);
      else
      {
	 cout << "Rehashed before 0.8" << endl;
	 rehash();
	 return findPos( x );
      }

   }
   
   return currentPos;
}


/**
 * Remove item x from the hash table.
 */
template <class HashedObj>
void HashTable<HashedObj>::remove( const HashedObj & x )
{
   int currentPos = findPos( x );
   if( isActive( currentPos ) )
      array[ currentPos ].info = DELETED;
}

/**
 * Find item x in the hash table.
 * Return the matching item or ITEM_NOT_FOUND if not found
 */
template <class HashedObj>
const HashedObj & HashTable<HashedObj>::find( const HashedObj & x )
{
   int currentPos = findPos( x );
   if( isActive( currentPos ) )
      return array[ currentPos ].element;
   else
      return ITEM_NOT_FOUND;
}

/**
 * Make the hash table logically empty.
 */
template <class HashedObj>
void HashTable<HashedObj>::makeEmpty( )
{
   currentSize = 0;
   for( unsigned int i = 0; i < array.size( ); i++ )
      array[ i ].info = EMPTY;
}

/**
 * Deep copy.
 */
template <class HashedObj>
const HashTable<HashedObj> & HashTable<HashedObj>::
operator=( const HashTable<HashedObj> & rhs )
{
   if( this != &rhs )
   {
      array = rhs.array;
      currentSize = rhs.currentSize;
      probeCount = rhs.probeCount;
      distinctCount = rhs.distinctCount;
      occurCount = rhs.occurCount;
      insertCount = rhs.insertCount;
   }
   return *this;
}


/**
 * Return true if currentPos exists and is active.
 */
template <class HashedObj>
bool HashTable<HashedObj>::isActive( int currentPos ) const
{
   return array[ currentPos ].info == ACTIVE;
}

#endif
