#ifndef _JOB_H_
#define _JOB_H_

#include <iostream>
#include "BinaryHeap.h"

using namespace std;

class Job
{
  public:
   Job(int ID = 0, int unitPrice = 0, int size = 0, int submitTime = 0)
      :m_ID( ID ), m_unitPrice( unitPrice ), m_size( size ), m_submitTime( submitTime )
      {}

   bool operator==( const Job & rhs ) const;
   bool operator<( Job & rhs ) const;
   const Job & operator+=( int amount );

   int GetPrice( ) const
      {
	 return m_unitPrice;
      }
   int GetTime( ) const
      {
	 return m_submitTime;
      }
   int GetSize( ) const
      {
	 return m_size;
      }
   int GetID( ) const
      {
	 return m_ID;
      }
   int GetPayment( ) const
      {
	 return m_size * m_unitPrice;
      }

   ostream& printInfo( ostream& out, int T );
   ostream& printID( ostream& out );

  private:
   int m_ID;
   int m_unitPrice;
   int m_size;
   int m_submitTime;
};

#endif
