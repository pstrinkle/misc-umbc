/****************************************************
 ** File: proj3.c
 ** Author: Patrick Trinkle
 ** Date: 4/5/2004
 ** Section: 0103
 ** Email : tri1@umbc.edu
 **
 ** This program reads in data from a unix redirect
 ** about the cars on a train and inputs them into an
 ** array through dynamic memory allocation. 
 ** 
 ** The program then prints the data with transport
 ** totals and then prints a mock up of the train.
 ****************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"

/* prices of moving materials
** per ton per mile */
#define AUTOS   .165
#define COAL    .291
#define CATTLE  .525
#define HOGS    .631
#define EGGS    .759

/* number of cars per row */
#define ROWSPAN 5

/* length of the origin & destination strings */
#define LENGTH  12

int main()
{
   CAR * train; /* declare point to CAR */

   int numCars, wt; /* delcare vars for number of cars and weight */
   
   wt = 0; /* placing it at 0 so it clears out the garbage */
   
   float cost; /* declare var cost as float for total cost */

   cost = 0; /* placing it at 0 so it clears out the garbage */

   /* prints the greeting */
   PrintGreeting();

   /* gets the number of cars in the train */
   GetNumCars(&numCars);

   /* dynamically allocates the memory */
   GetMemory(&train, numCars);

   /* gets the information for the cars on the train */
   GetInfo(train, numCars);

   /* calculates the cost of moving each car on the train */
   CalcCost(train, numCars);

   /* goes through the train and calculates the total weight and cost */
   FindTotals(train, numCars, &cost, &wt);

   /* prints the number of cars */
   PrintNumCars(numCars);

   /* prints the data per car of the entire train */
   PrintData(train, numCars);

   /* prints the break */
   PrintBreak();

   /* prints the total cost, weight and number of cars */
   PrintTotals(numCars, cost, wt);

   /* prints the ascii art of the train with rows 5 cars long */
   PrintCars(train, numCars);

   /* frees the memory allocated for the train */
   free(train);

   /* end of the function */
   return 0;
}
