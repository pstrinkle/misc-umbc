//---------------------------------------------------
// File       : Truck.cpp
// Author     : Patrick Trinkle
// Date       : October 13 2004
// UMBC Email : tri1@umbc.edu
// Project    : 2
// Section    : 0101
// Description: Functions That access the
//              members of Truck Class Used for Proj2
//---------------------------------------------------

#include "Truck.h"
#include "Box.h"
#include "RoundToy.h"

using namespace std;

//---------------------------------------
// Constructor
// PreConditions:
//         none
// PostConditions
//         an object
//---------------------------------------
Truck::Truck()
   :m_totalmileage( 0 ), m_distancetoPlant( 0 )
{
   // values initialized
}

//---------------------------------------
// Truck::LoadTruck
// PreConditions:
//         none
// PostConditions
//         box on truck
//---------------------------------------
void Truck::LoadTruck(const Box& box)
{
   m_boxesintruck.push_back(box);
   // puts the box onto truck
}

//---------------------------------------
// Truck::Deliver
// PreConditions:
//         none
// PostConditions
//         delivered boxes to plant
//---------------------------------------
void Truck::Deliver()
{
   unsigned int i;

   for ( i = 0; i < m_boxesintruck.size(); i++ )
   {
      m_boxesdelivered.push_back(m_boxesintruck.at(i));
   }
   // takes boxes from truck and places them into plant
   
   m_boxesintruck.clear();
   // clears out truck box vector

   m_totalmileage = m_totalmileage + ( m_distancetoPlant * 2 );
   // calculates delivery distance
}

//---------------------------------------
// Truck::SetPlant
// PreConditions:
//         none
// PostConditions
//         set values for plant with 
//         truck
//---------------------------------------
void Truck::SetPlant(int distance, string& plantName)
{
   m_distancetoPlant = distance;
   m_plantName = plantName;
   // values set
}

//---------------------------------------
// Truck::Output
// PreConditions:
//         none
// PostConditions
//         none
//---------------------------------------
void Truck::Output(ostream& out) const
{
   int numCLR1, numCLR2, numCLR3, numCLR4, numCLR5;
   int deliveries;
   deliveries = 0;

   out << "Current Load: "
       << m_boxesintruck.size()
       << endl << endl;
   // set up for table for each box

   if ( m_boxesintruck.size() > 0 )
   {
      for ( unsigned int i = 0; i < m_boxesintruck.size(); i++ )
      {
         out << "Box # " << setw(2) << i + 1 << endl << "--------" << endl;

	 numCLR1 = 0;
	 numCLR2 = 0;
	 numCLR3 = 0;
	 numCLR4 = 0;
	 numCLR5 = 0;

	 // sets up color variables


	 // calculates color totals
         for ( unsigned int j = 0; j < m_boxesintruck[i].NumToys(); j++ )
         {
            if ( m_boxesintruck[i].GetToy(j).Color() == CLR1 )
               numCLR1++;
            else if ( m_boxesintruck[i].GetToy(j).Color() == CLR2 )
               numCLR2++;
            else if ( m_boxesintruck[i].GetToy(j).Color() == CLR3 )
               numCLR3++;
            else if ( m_boxesintruck[i].GetToy(j).Color() == CLR4 )
               numCLR4++;
            else if ( m_boxesintruck[i].GetToy(j).Color() == CLR5 )
               numCLR5++;
         }
	 
	 // builds table

         out << "   " << setw(2) << numCLR1
             << " " << setw(6) << CLR1
             << "       " << setw(2) << numCLR2
             << " " << setw(6) << CLR2
             << "       " << setw(2) << numCLR3
             << " " << setw(6) << CLR3 
             << endl
             << "   " << setw(2) << numCLR5
             << " " << setw(6) << CLR5
             << "       " << setw(2) << numCLR4
             << " " << setw(6) << CLR4 
             << endl
             << endl;
      }
   }
   
   // prints delivery information
   deliveries = ( m_totalmileage / 2 );
   deliveries = ( deliveries / m_distancetoPlant );
      
      // Delivery Log

      out << "Delivery Log" << endl
	  << "            " << endl
	  << deliveries << " deliveries made to " << m_plantName
	  << endl
	  << m_totalmileage << " total miles driven" << endl
	  << m_boxesdelivered.size() << " boxes delivered" << endl
	  << endl;
}
