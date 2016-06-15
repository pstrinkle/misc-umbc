/********************************************
 * File: polygons.c
 * Author: Patrick Trinkle
 * Date: 2/24/2004
 * Section 103
 * EMail: tri1@umbc.edu
 *
 * This file contains some simple geometrical
 * functions. They are grouped together in this 
 * file because they are all related to the main
 * program. And we were told to put them here.
 * 
 * This file is meant to be compiled separately from 
 * the main program.
 *
 * Functions in this file:
 *
 * PrintGreeting (void)
 * GenerateTable (int min, int max)
 * PrintInstructions (void)
 * GetValidNumSides (int sentinel, int min, int max)
 * GetPositiveValue (void)
 * PrintName (int numSides)
 * FindExteriorAngles (int numSides)
 * FindAngleSum (int numSides)
 * FindInteriorAngles (double angleSum, int numSides)
 * FindNumDiagonals(int numSides)
 * FindPerimeter (int numSides, double side)
 * FindArea (int numSides, double side)
 * ConvertDegreesToRadians (double degrees)
 * 
 *
 *********************************************/




#include "polygons.h"

#define HALF_ROTATION   180
#define FULL_ROTATION   360
#define PI          3.14159

#define TRIANGLE          3
#define SQUARE            4
#define PENTAGON          5
#define HEXAGON           6
#define HEPTAGON          7
#define OCTAGON           8
#define NONAGON           9
#define DECAGON          10


/*****************************************
 ** Function: PrintGreeting()
 ** This function prints the greeting
 **
 ** Inputs: none
 ** Outputs: none
 ****************************************/

void PrintGreeting (void)
{
   
   printf("Welcome to The Polygon Tool\n\n");
   printf("This program takes the number of sides of a polygon\n");
   printf("and the length of one of the sides of your polygon\n");
   printf("and with this information calculates the perimeter and area.\n\n");

}

/*****************************************
 ** Function: GenerateTable()
 ** This function generates the table
 **
 ** Inputs: the minimum and maximum number of sides
 ** Outputs: the table
 ****************************************/

void GenerateTable (int min, int max)
{
   
   int i;
   /* table header */
   printf("                        Table of Regular Polygon Facts\n\n");
   printf("        Name          # Sides  Ext Ang  Int Ang Sum   Int Ang    Diags\n");
   
   /* for loop to generate table */
   for (i = min ; i <= max ; i++)
   {
      /* Print the Table, each time throught the for loop */
      PrintName (i);
      printf(" %7d %9.3f %8d %13.3f %7d\n", i, FindExteriorAngles(i), FindAngleSum(i), FindInteriorAngles (FindAngleSum(i), (i)), FindNumDiagonals(i));
   }

}

/*****************************************
 ** Function: PrintInstructions()
 ** This function prints the instructions
 **
 ** Inputs: none
 ** Outputs: none
 ****************************************/

void PrintInstructions ()
{
   printf("\n\n");
   printf("Enter the number of sides, between 3 and 10 and\n");
   printf("the length of one of the sides to calculate the\n");
   printf("perimeter and area of the polygon.\n\n");

}

/*****************************************
 ** Function: PrintName()
 ** This function prints the name of the polygon based on the number of sides.
 **
 ** Inputs: number of sides
 ** Outputs: the name of the polygon
 ****************************************/

void PrintName (int numSides)
{

   /* takes the number of sides and finds the name of the appropriate polygon */
   switch (numSides)
   {
      case TRIANGLE:
         printf("Equilateral triangle");
	 break;
      case SQUARE:
	 printf("              Square");
	 break;
      case PENTAGON:
         printf("    Regular pentagon");
	 break;
      case HEXAGON:
         printf("     Regular hexagon");
	 break;
      case HEPTAGON:
	 printf("    Regular heptagon");
	 break;
      case OCTAGON:
	 printf("     Regular octagon");
	 break;
      case NONAGON:
	 printf("     Regular nonagon");
	 break;
      case DECAGON:
	 printf("     Regular decagon");
	 break;
      default:
         printf("     Oops, error.   ");
         break;
   }

}

/*****************************************
 ** Function: FindExteriorAngles()
 ** This function returns the external angle with the input of the number of sides.
 **
 ** Inputs: number of sides
 ** Outputs: the external angle
 ****************************************/

double FindExteriorAngles (int numSides)
{

   double ExtAng;
   ExtAng = 0;

   /* this finds and returns the external angle of the polygon for the table */
   ExtAng = FULL_ROTATION / numSides;
   
   return ExtAng;

}

/*****************************************
 ** Function: FindAngleSum()
 ** This function returns the sum of the angles with the input of the number of sides.
 **
 ** Inputs: number of sides
 ** Outputs: the angle sum
 ****************************************/

int FindAngleSum (int numSides)
{
   
   int angleSum;
   angleSum = 0;
   /* this finds and returns the angle sum of the polygon for the table */
   angleSum = HALF_ROTATION * ( numSides - 2 );

   return angleSum;

}

/*****************************************
 ** Function: FindInteriorAngles()
 ** This function returns the interior angles with the input of the number of sides.
 **
 ** Inputs: number of sides
 ** Outputs: the interior angles
 ****************************************/

double FindInteriorAngles (double angleSum, int numSides)
{

   double interAngles;
   interAngles = 0;
   /* this finds and returns the interior angle of the polygon for the table */
   interAngles = angleSum / numSides;

   return interAngles;

}

/*****************************************
 ** Function: FindNumDiagonals()
 ** This function returns the number of
 ** diagonals with the input of the
 ** number of sides.
 **
 ** Inputs: number of sides
 ** Outputs: the number of diagonals
 ****************************************/

int    FindNumDiagonals (int numSides)
{

   int NumDiagonals;
   NumDiagonals = 0;
   /* this finds and returns the number of diagonals of the polygon for the table */
   NumDiagonals =  numSides * ( numSides - 3 ) /2;
   
   return NumDiagonals;

}

/*****************************************
 ** Function: FindPerimeter()
 ** This function returns the perimeter
 ** with the input of the number of sides.
 **
 ** Inputs: number of sides
 ** Outputs: the perimeter of the polygon
 ****************************************/

double FindPerimeter (int numSides, double side)
{

   double Perimeter;
   Perimeter = 0;
   /* this finds and returns the perimeter */
   Perimeter = numSides * side;

   return Perimeter;
}

/*****************************************
 ** Function: ConvertDegreesToRadians()
 ** This function converts degrees to
 ** radians so that the math functions
 ** work properly
 **
 ** Inputs: degrees
 ** Outputs: the equivalent angle in radians
 ****************************************/

double ConvertDegreesToRadians (double degrees)
{

   double radians;
   radians = 0;
   /* this converts degrees to radians because the math function in c uses radians */
   radians = degrees * ( PI / HALF_ROTATION );

   return radians;

}


/*****************************************
 ** Function: GetValidNumSides()
 ** This function takes in what the user
 ** inputs and checks it for validity and
 ** then prints out the information
 **
 ** Inputs: the minimum and maximum
 ** number of sides, the number of sides
 ** the user picks, and the killswitch
 **
 ** Outputs: the information for the
 ** user-defined polygon or an error
 ** message if information is bad
 ****************************************/


int GetValidNumSides (int sentinel, int min, int max)
{

   int numSides;
   
   printf("Enter number of sides, 0 to quit : ");
   scanf("%d", &numSides); 

   if ( numSides == sentinel )
   {
   }
   
   else
   {

      while ( numSides < 3 || numSides > 10 )
      {
         printf("Sorry 3 - 10 or 0 only\n");
         printf("Try again.\n");
         printf("Enter number of sides, 0 to quit : ");
         scanf("%d", &numSides); 
      }
   }
   return numSides;
}

/*****************************************
 ** Function: GetPositiveValue()
 ** This function checks to see if the 
 ** user's input is not negative
 **
 ** Inputs: the length of one side
 ** Outputs: the length of the side is
 ** positive
 ****************************************/


double GetPositiveValue ()
{
   
   double side;

   printf("    Enter the length of one side : ");
   scanf("%lf", &side);

   while ( side <= 0 )
   {
      printf("Positive values only! Try again : ");
      scanf("%lf", &side);
   }
   return side;
}
/*************
 ** Function: FindArea (ints)
 ** inputs: numSides, side
 ** outputs: Area
 *************/
double FindArea (int numSides, double side)
{
   
   double area;

   area = .25 * numSides * (side * side) * (1 / tan (ConvertDegreesToRadians (HALF_ROTATION) / numSides));

   return area;

}
