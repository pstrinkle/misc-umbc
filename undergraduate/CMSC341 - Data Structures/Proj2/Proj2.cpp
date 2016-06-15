//---------------------------------------------------                              
// File       : Proj2.cpp                                                             
// Author     : Patrick Trinkle                                                    
// Date       : March 2005                                                         
// UMBC Email : tri1@umbc.edu                                                      
// Project    : 2                                                                  
// Section    : 0101                                                               
// Description: The Project Main File  used for Proj2                                      
//---------------------------------------------------


#include "List.h"
#include "mraf.h"
#include "iae.h"
#include "P2DataGen.h"

#include<stdlib.h>
#include<vector>

using namespace std;

void UniqueFind(vector<int>& data, int datum)
{
   bool truth = false;
   for (unsigned int i = 0; i < data.size(); ++i)
   {
      if (data.at(i) == datum)
      {
         truth = true;
	 i += data.size();
      }
   }
   if (truth == false)
      data.push_back(datum);
}

int main( int argc, char** argv)
{
   if ( argc != 3 )
   {
      cerr << "Not enough arguments." << endl;
      exit(-1);
   }

   int expN = atoi(argv[1]);
   int expK = atoi(argv[2]);
   // perhaps use atoi ?


   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(3);

   // 5 runs for experiment
   // run 1: n recency, 0
   // run 2: low recency, .25
   // run 3: medium recency, .50
   // run 4: high recency, .75
   // run 5: very high recency, 1
 
   Mraf<int> l_mraf;
   Iae<int> l_iae;

   InitializeExperiment(expN);

   int RandomTotal = 0;
   int RecencyTotal = 0;
   vector<int> recencyunique;
   vector<int> randomunique;
   double recency;
   double random = 0;
   int kCounter = 0;
   int input = 0;
   ListItr<int> mraf_find;
   ListItr<int> iae_find;
   string type;

   // big for statement to proceed with experiment
   for (recency = 0; recency <= 1; recency += .25)
   {
      if (recency == 0) // special case 1
      {
	 type = "NO";
	 
	 for (int i = 0; i < expN; ++i)
	 {
	    // for loop to add items to lists
	    input = GetRandomDatum();
	    UniqueFind(randomunique, input);
	    RandomTotal++;

	    // insertion tests
	    mraf_find = l_mraf.find(input);
	    if(!mraf_find.isPastEnd() && mraf_find != l_mraf.first())
	    {
	       l_mraf.remove(input);
	       l_mraf.insertAtFront(input); // it will insert after making it first
	    }
	    else if (mraf_find.isPastEnd())
	       l_mraf.insertAtFront(input);
	    
	    iae_find = l_iae.find(input);
	    if (iae_find.isPastEnd())
	       l_iae.insertAtBack(input);

	    kCounter++;

	    if (kCounter == expK)
	    {
	       // Print Data
	       cout << "After " << ( i + 1 ) << " input items: " << type << " recency:" << endl
		    << "        " << "number of items drawn from recency: " << RecencyTotal << endl
		    << "        " << "number of items drawn from random:  " << RandomTotal << endl
		    << "        " << "number of unique items drawn from recency: " << recencyunique.size() << endl
		    << "        " << "number of unique items drawn from random:  " << randomunique.size() << endl
		    << "                             " << " MRAF " << "               " << " IAE " << endl
		    << "        " << "Total Accesses        " << l_mraf.GetTotal() << "                   " << l_iae.GetTotal() << endl
		    << "        " << "Average Number        " << ( l_mraf.GetTotal() / static_cast<double>(i + 1) ) << "                "
		    << ( l_iae.GetTotal() / static_cast<double>(i + 1) ) << endl
		    << "        " << " of access" << endl;

	       kCounter = 0;
	    }
	 }
	 // print end data
	 cout << endl << "Final Data" << endl;
	 cout << "After " << expN << " input items: " << type << " recency:" << endl
	      << "        " << "number of items drawn from recency: " << RecencyTotal << endl
	      << "        " << "number of items drawn from random:  " << RandomTotal << endl
	      << "        " << "number of unique items drawn from recency: " << recencyunique.size() << endl
	      << "        " << "number of unique items drawn from random:  " << randomunique.size() << endl
	      << "                             " << " MRAF " << "               " << " IAE " << endl
	      << "        " << "Total Accesses        " << l_mraf.GetTotal() << "                   " << l_iae.GetTotal() << endl
	      << "        " << "Average Number        " << ( l_mraf.GetTotal() / static_cast<double>(expN) ) << "                "
	      << ( l_iae.GetTotal() / static_cast<double>(expN) ) << endl
	      << "        " << " of access" << endl << endl;	 

	 // clear lists
	 l_iae.makeEmpty();
	 l_mraf.makeEmpty();
	 
	 // reset data
	 ResetData();
	 RecencyTotal = 0;
	 RandomTotal = 0;
	 randomunique.clear();
	 recencyunique.clear();
	 kCounter = 0;
	 input = 0;
	 l_mraf.ResetTotal();
	 l_iae.ResetTotal();

      } // end special 1

      else if (recency == 1) // special case 2
      {
	 type = "VERY HIGH";

	 for (int j = 0; j < expN; ++j)
	 {
	    input = GetRecencyDatum();
	    UniqueFind(recencyunique, input);
	    RecencyTotal++;

	    mraf_find = l_mraf.find(input);
	    if (!mraf_find.isPastEnd() && mraf_find != l_mraf.first())
	    {
	       l_mraf.remove(input);
	       l_mraf.insertAtFront(input);
	    }
	    else if (mraf_find.isPastEnd())
	       l_mraf.insertAtFront(input);

	    iae_find = l_iae.find(input);
	    if (iae_find.isPastEnd())
	       l_iae.insertAtBack(input);

	    kCounter++;

	    if (kCounter == expK)
	    {
	       // print k data
               cout << "After " << ( j + 1 ) << " input items: " << type << " recency:" << endl
                    << "        " << "number of items drawn from recency: " << RecencyTotal << endl
                    << "        " << "number of items drawn from random:  " << RandomTotal << endl
                    << "        " << "number of unique items drawn from recency: " << recencyunique.size() << endl
                    << "        " << "number of unique items drawn from random:  " << randomunique.size() << endl
                    << "                             " << " MRAF " << "               " << " IAE " << endl
                    << "        " << "Total Accesses        " << l_mraf.GetTotal() << "                   " << l_iae.GetTotal() << endl
                    << "        " << "Average Number        " << ( l_mraf.GetTotal() / static_cast<double>(j + 1) ) << "                "
                    << ( l_iae.GetTotal() / static_cast<double>(j + 1) ) << endl
                    << "        " << " of access" << endl;

	       kCounter = 0;
	    }
	 }
	 // print end data
	 cout << endl << "Final Data" << endl;
	 cout << "After " << expN << " input items: " << type << " recency:" << endl
	      << "        " << "number of items drawn from recency: " << RecencyTotal << endl
	      << "        " << "number of items drawn from random:  " << RandomTotal << endl
	      << "        " << "number of unique items drawn from recency: " << recencyunique.size() << endl
	      << "        " << "number of unique items drawn from random:  " << randomunique.size() << endl
	      << "                             " << " MRAF " << "               " << " IAE " << endl
	      << "        " << "Total Accesses        " << l_mraf.GetTotal() << "                   " << l_iae.GetTotal() << endl
	      << "        " << "Average Number        " << ( l_mraf.GetTotal() / static_cast<double>(expN) ) << "                "
	      << ( l_iae.GetTotal() / static_cast<double>(expN) ) << endl
	      << "        " << " of access" << endl << endl;

	 //clear lists
	 l_iae.makeEmpty();
	 l_mraf.makeEmpty();

	 //reset data
	 ResetData();
	 RecencyTotal = 0;
	 RandomTotal = 0;
	 randomunique.clear();
	 recencyunique.clear();
	 kCounter = 0;
	 l_mraf.ResetTotal();
	 l_iae.ResetTotal();
      }

      else
      {
	 if (recency == .25)
	    type = "LOW";
	 else if (recency == .50)
	    type = "MEDIUM";
	 else
	    type = "HIGH";

	 for (int k = 0; k < expN; ++k)
	 {
	    random = drand48();
	    if (random > recency)
	    {
	       input = GetRandomDatum();
	       UniqueFind(randomunique, input);
	       RandomTotal++;
	    }
	    else
	    {
	       input = GetRecencyDatum();
	       UniqueFind(recencyunique, input);
	       RecencyTotal++;
	    }
	    
	    mraf_find = l_mraf.find(input);
	    if (!mraf_find.isPastEnd() && mraf_find != l_mraf.first())
	    {
	       l_mraf.remove(input);
	       l_mraf.insertAtFront(input);
	    }
	    else if (mraf_find.isPastEnd())
	       l_mraf.insertAtFront(input);

	    iae_find = l_iae.find(input);
	    if (iae_find.isPastEnd())
	       l_iae.insertAtBack(input);
	    
	    kCounter++;

	    if (kCounter == expK)
	    {
	       // print k
               cout << "After " << ( k + 1 ) << " input items: " << type << " recency:" << endl
                    << "        " << "number of items drawn from recency: " << RecencyTotal << endl
                    << "        " << "number of items drawn from random:  " << RandomTotal << endl
                    << "        " << "number of unique items drawn from recency: " << recencyunique.size() << endl
                    << "        " << "number of unique items drawn from random:  " << randomunique.size() << endl
                    << "                             " << " MRAF " << "               " << " IAE " << endl
                    << "        " << "Total Accesses        " << l_mraf.GetTotal() << "                   " << l_iae.GetTotal() << endl
                    << "        " << "Average Number        " << ( l_mraf.GetTotal() / static_cast<double>(k + 1) ) << "                "
                    << ( l_iae.GetTotal() / static_cast<double>(k + 1) ) << endl
                    << "        " << " of access" << endl;	       

	       kCounter = 0;
	    }
	 }
	 // print end data
	 cout << endl << "Final Data" << endl;
	 cout << "After " << expN << " input items: " << type << " recency:" << endl
	      << "        " << "number of items drawn from recency: " << RecencyTotal << endl
	      << "        " << "number of items drawn from random:  " << RandomTotal << endl
	      << "        " << "number of unique items drawn from recency: " << recencyunique.size() << endl
	      << "        " << "number of unique items drawn from random:  " << randomunique.size() << endl
	      << "                             " << " MRAF " << "               " << " IAE " << endl
	      << "        " << "Total Accesses        " << l_mraf.GetTotal() << "                   " << l_iae.GetTotal() << endl
	      << "        " << "Average Number        " << ( l_mraf.GetTotal() / static_cast<double>(expN) ) << "                "
	      << ( l_iae.GetTotal() / static_cast<double>(expN) ) << endl
	      << "        " << " of access" << endl << endl;
	 
	 // clear lists
	 l_iae.makeEmpty();
	 l_mraf.makeEmpty();
	 l_iae.ResetTotal();
	 l_mraf.ResetTotal();
	 ResetData();
	 RecencyTotal = 0;
	 RandomTotal = 0;
	 randomunique.clear();
	 recencyunique.clear();
	 kCounter = 0;
      } // end else case
      
   } // end of major experiment for loop
   
   return 0;
}
