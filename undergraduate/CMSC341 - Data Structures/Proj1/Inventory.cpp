//---------------------------------------------------                   
// File       : Inventory.cpp
// Author     : Patrick Trinkle                                         
// Date       : February 2005                                        
// UMBC Email : tri1@umbc.edu                                           
// Project    : 1
// Section    :   
// Description: The Inventory Class used for Proj1                          
//---------------------------------------------------                    


#include "Inventory.h"

#ifndef _Inventory_cpp
#define _Inventory_cpp

using namespace std;

template<class T>
int Inventory<T>::NumItems() const
{
   int i = 0;
   unsigned int j = 0;
   j = m_items.size();
   i = j;
   return i;
}

template<class T>
const Inventory<T>& Inventory<T>::operator+=(const T& item)
{
   bool buyproduct = false;

   if ( GetCash() < ( item.GetBuyPrice() * item.GetNumUnits() ) )
      throw NotEnoughCash();
   else
   {
      SetCash( GetCash() - ( item.GetBuyPrice() * item.GetNumUnits() ) );
      int q = 0;

      while ( q < NumItems() )
      {
	 if ( item.GetName() == m_items.at(q).GetName() )
	 {
	    m_items.at(q).SetNumUnits( m_items.at(q).GetNumUnits() + item.GetNumUnits() );
	    q *= ( NumItems() + 1 );
	    buyproduct = true;
	 }
	 q++;
      }
      if ( buyproduct == false )
	 m_items.push_back(item);
   }
   return *this;
}

template<class T>
const Inventory<T>& Inventory<T>::operator-=(const T& item)
{
   int q = 0;
   bool sellproduct = false;

   while ( q < NumItems() )
   {
      if ( item.GetName() == m_items.at(q).GetName() )
      {
	 if ( m_items.at(q).GetNumUnits() < item.GetNumUnits() )
	    throw NoneToSell(item.GetName());
	 else
	 {
	    m_cash += ( item.GetSellPrice() * item.GetNumUnits() );
	    m_items.at(q).SetNumUnits( m_items.at(q).GetNumUnits() - item.GetNumUnits() );
	    sellproduct = true;
	    q = 100 + NumItems();
	 }
      }
      else
	 q++;
   }
   if ( sellproduct == false )
      throw NoneToSell(item.GetName());

   return *this;
}

template<class T>
ostream& Inventory<T>::Print(ostream& out) const
{
   if ( NumItems() == 0 )
      out << "     " << "The inventory list is empty.";
   else
   {
      out << "     " << "The current inventory list is" << endl;
      for ( int j = 0; j < NumItems(); ++j )
      {
	 out << "     " << m_items.at(j) << endl;
      }
   }
   return out;
}

template<class T>
ostream& operator<<(ostream& out, Inventory<T>& i)
{
   i.Print(out);
   return out;
}

#endif
	    
