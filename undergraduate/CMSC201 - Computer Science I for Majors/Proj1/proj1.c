/*****************************************
 ** File: proj1.c
 ** Author: Patrick Trinkle
 ** Date: Late February : 2/23/2003
 ** Section: 103
 ** E-Mail: tri1@umbc.edu
 **
 ** This program prints common polygon information
 ** on the screen. This program then asks the user
 ** to input information on a polygon and then uses
 ** that information to output the perimeter and area
 ** of the selected polygon.
 *****************************************/



#include <stdio.h>
#include "polygons.h"

#define SENTINEL    0
#define MIN         3
#define MAX        10

int main()
{
   /* declare two input variables */
   double  numSides;
   double side;

   /* print the greeting */
   PrintGreeting ();

   /* Build the common value table */
   GenerateTable (MIN, MAX);

   /* Print the instructions for the user */
   PrintInstructions ();

   /* Request the number of sides of the polygon */
   numSides = GetValidNumSides (SENTINEL, MIN, MAX);
   
   while ( numSides != SENTINEL)
   {
      /* Request the length of one side */
      side = GetPositiveValue ();

      /* Print the name of polygon from # sides and print the output of the polygon */
      PrintName(numSides);
      printf(" with sides of %.3f\n", numSides);
      printf("                      Perimeter : %.3f\n", FindPerimeter(numSides, side));
      printf("                           Area : %.3f\n\n", FindArea(numSides, side)); 

      /* Repeat! */
      numSides = GetValidNumSides (SENTINEL, MIN, MAX);
   }
   
   /* They hit 0, and the program ends here! */
   printf("Ending Program\n");
   
   return 0;
}
