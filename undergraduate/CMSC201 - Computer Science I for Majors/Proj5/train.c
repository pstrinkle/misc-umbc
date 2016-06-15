/****************************************************
** File: train.c
** Author: Patrick Trinkle
** Date: 4/5/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the functions for proj3.c
** some modified for proj5
****************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "train.h"

#define ROWSPAN 5


/*****************************************
** Function: GetNumCars()
** This function gets the number of cars.
**
** Inputs: a pointer to the number of cars
** Outputs: void
****************************************/
void GetNumCars (int* numCarsPtr)
{
   int numCars;
   
   scanf("%d", &numCars);
   /* reads in the number of cars and stores in temp */

   *numCarsPtr = numCars; /* assigns value to numCars in main */
}

/*****************************************
** Function: PrintNumCars()
** This function prints the number of cars
**
** Inputs: the number of cars
** Outputs: void
****************************************/
void PrintNumCars (int numCars)
{
   printf("There are %d cars in the train\n", numCars);
   printf("There data for each car are : \n");
}

/*****************************************
** Function: GetMemory()
** This dynamically allocates memory
**
** Inputs: the pointer for the cars and
**         the number of cars in the train
** Outputs: void
****************************************/
void GetMemory (CAR** train, int numCars)
{
   /* dynamically allocates the space */
   *train = (CAR *) malloc(numCars * sizeof(CAR));
   
   /* if there wasn't space it exits */
   if (*train == NULL)
   {
      printf("Sorry, Memory could not be allocated.");
      exit(-1);
   }
}

/*****************************************
** Function: GetInfo()
** This gets the info for the train
**
** Inputs: the pointer for the cars and
**         the number of cars in the train
** Outputs: void
****************************************/
void GetInfo (CAR* train, int numCars)
{
   int i;
 
   /* goes through the data file and inputs */ 
   for (i = 0; i < numCars; i++)
   {
      scanf("%d", &train[i].carNum);
      scanf("%s", train[i].cargo);
      scanf("%s", train[i].origin);
      scanf("%s", train[i].destination);
      scanf("%d", &train[i].weight);
      scanf("%d", &train[i].miles);
   }
}

/*****************************************
** Function: CalcCost()
** Calculates the cost per car of the
** train
**
** Inputs: the pointer for the car
** 
** Outputs: void
****************************************/
void CalcCost (CARPTR newcar)
{
   int compared;
   float temp = 0;
   float price;

   /* compares the cargo of the car and calculates the cost of transport */

   compared = strcmp(newcar -> cargo, "autos");
   if (compared == 0)
   {
      price = AUTOS;
   }

   compared = strcmp(newcar -> cargo, "coal");
   if (compared == 0)
   {
      price = COAL;
   }

   compared = strcmp(newcar -> cargo, "cattle");
   if (compared == 0)
   {
      price = CATTLE;
   }

   compared = strcmp(newcar -> cargo, "hogs");
   if (compared == 0)
   {
      price = HOGS;
   }

   compared = strcmp(newcar -> cargo, "eggs");
   if (compared == 0)
   {
      price = EGGS;
   }

   /* here it actually uses the price and weight of the car to calculate */

   temp = ( ( (float) (newcar -> weight) ) / 2000 );
   temp = temp * price * (newcar -> miles);

   newcar -> cost = temp;
}

/*****************************************
** Function: FindTotals()
** Calculates totals for the train
**
** Inputs: the pointer for the cars and
**         the number of cars in the train
**         and the cost pointer, and the
**         weight pointer
** Outputs: void
****************************************/
void FindTotals (CAR* train, int numCars, float* costPtr, int* wtPtr)
{
   int i;

   /* this goes through the train and totals the weight and cost */
   for (i = 0; i < numCars; i++)
   {
      ( *wtPtr ) = train[i].weight + ( *wtPtr );
      ( *costPtr ) = train[i].cost + ( *costPtr );
   }
}


/*****************************************
** Function: PrintData()
** Prints the data for the trains
**
** Inputs:  the pointer to the track
**          pointer for the track and the
**          pointer to the output file
**          pointer
**
** Outputs: void
****************************************/
void PrintData (TRACKPTR * track, FILE * ofp)
{
   NODEPTR curr, prev;

   prev = NULL;
   curr = (*track) -> head;

   while (curr != NULL)
   {
      /* this prints the data for each car */

      fprintf(ofp, "\n");
      fprintf(ofp, " Car number : %d\n", curr -> data.carNum);
      fprintf(ofp, "      Cargo : %s\n", curr -> data.cargo);
      fprintf(ofp, "     Origin : %s\n", curr -> data.origin);
      fprintf(ofp, "Destination : %s\n", curr -> data.destination);
      fprintf(ofp, "     Weight : %d pounds\n", curr -> data.weight);
      fprintf(ofp, "   Distance : %d\n", curr -> data.miles);
      fprintf(ofp, "       Cost : $ %.2lf\n", curr -> data.cost);

      prev = curr;
      curr = curr -> next;
   }
}

/*****************************************
** Function: PrintBreak()
** Prints the break
**
** Inputs: void
**
** Outputs: void
****************************************/
void PrintBreak (void)
{
   printf("\n");
   printf("-------------------------------\n");
   printf("-------------------------------\n");
   printf("\n");
}

/*****************************************
** Function: PrintTotals()
** Prints the totals
**
** Inputs:  the pointer to the track
**          pointer for the track and the
**          pointer to the output file
**          pointer
**
** Outputs: void
****************************************/
void PrintTotals (TRACKPTR * track, FILE * ofp)
{
   float tempwt;


   /* this uses the temporary weight and calcs the weight in tons */
   tempwt = ( (float) ((*track)-> totalWeight) ) / 2000;

   fprintf(ofp, "\nTotal weight : %9.2lf tons\n", tempwt);
   fprintf(ofp, "Total bill : $%10.2lf\n", (*track) -> totalCost);
   fprintf(ofp, "\n\n");

}

/*****************************************
** Function: PrintCars()
** Prints the cars
**
** Inputs: the pointer for the cars and
**         the number of cars
**
** Outputs: void
****************************************/
void PrintCars (CAR* train, int numCars)
{
   int numRows, numExtra, rownum, car, i;

   numRows = ( numCars / ROWSPAN ); /* how many full rows there are */
   numExtra = ( numCars % ROWSPAN ); /* how many extra cars there are */

   if (numRows > 0) /* if there's at least one full row */
   {
      for (rownum = 0; rownum < numRows; rownum++)
      {
         for (car = 0; car < ROWSPAN; car++) /* prints line */
         {
            printf("  -------------");
         }
         printf("\n");
         i = ( ROWSPAN * rownum );    

         for (car = 0; car < ROWSPAN; car++) /* prints car number */
         {
            printf("  | %d     |", train[i].carNum);
            i++;
         }
         printf("\n");
         i = ( ROWSPAN * rownum );

         for (car = 0; car < ROWSPAN; car++) /* prints cargo */
         {
            printf("<-| %-6s    |", train[i].cargo);
            i++;
         }
         printf("\n");
         i = ( ROWSPAN * rownum );
  
         for (car = 0; car < ROWSPAN; car++) /* prints destination */
         {
            printf("  | %-9s |", train[i].destination);
            i++;
         }
         printf("\n");
  
         for (car = 0; car < ROWSPAN; car++) /* print wheels */
         {
            printf("  --O-------O--");
         }
         printf("\n");
        

      }
      if (numExtra > 0) /* if there are extra cars, same sub loop definitions */
      {
         i = numRows * ROWSPAN;   

         for (car = 0; car < numExtra; car++)
         {
            printf("  -------------");
            i++;
         }
         printf("\n");
         i = numRows * ROWSPAN;

         for (car = 0; car < numExtra; car++)
         {
            printf("  | %d     |", train[i].carNum);
            i++;
         }
         printf("\n");
         i = numRows * ROWSPAN;

         for (car = 0; car < numExtra; car++)
         {
            printf("<-| %-6s    |", train[i].cargo);
            i++;
         }
         printf("\n");
         i = numRows * ROWSPAN;

         for (car = 0; car < numExtra; car++)
         {
            printf("  | %-9s |", train[i].destination);
            i++;
         }
         printf("\n");
         
         for (car = 0; car < numExtra; car++)
         {
            printf("  --O-------O--");
         }
         printf("\n");         
      }
   }
   else /* if there are no full rows, same sub loop definitions */
   {

      i = 0;
      for (car = 0; car < numCars; car++)
      {
         printf("  -------------");
         i++;
      }
      printf("\n");
      i = 0;

      for (car = 0; car < numCars; car++)
      {
         printf("  | %d     |", train[i].carNum);
         i++;
      }
      printf("\n");
      i = 0;
 
      for (car = 0; car < numCars; car++)
      {
         printf("<-| %-6s    |", train[i].cargo);
         i++;
      }
      printf("\n");
      i = 0;

      for (car = 0; car < numCars; car++)
      {
         printf("  | %-9s |", train[i].destination);
         i++;
      }
      printf("\n");

      for (car = 0; car < numCars; car++)
      {
         printf("  --O-------O--");
      }
      printf("\n");

   }

}

