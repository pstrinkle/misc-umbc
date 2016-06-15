#include "Job.h"


using namespace std;

bool Job::operator==( const Job & rhs ) const
{
   if ( m_ID == rhs.m_ID )
      return true;
   return false;
}

bool Job::operator<( Job & rhs ) const
{
   if ( m_unitPrice > rhs.m_unitPrice )
      return true;
   else if ( m_unitPrice == rhs.m_unitPrice && m_size < rhs.m_size )
      return true;
   return false;
}

const Job & Job::operator+=( int amount )
{
   m_unitPrice += amount;
   return *this;
}

ostream& Job::printInfo( ostream& out, int T )
{
   out << GetID() << "\t\t" << GetSize() << "\t\t" << GetPayment() << "\t\t"
       << ( T - m_submitTime ) << "\t\t";
   return out;
}

ostream& Job::printID( ostream& out )
{
   out << GetID();
   return out;
}
