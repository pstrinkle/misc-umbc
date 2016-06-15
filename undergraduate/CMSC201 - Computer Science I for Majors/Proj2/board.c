/****************************************************
 ** File: board.c
 ** Author: Patrick Trinkle
 ** Date: 3/8/2004
 ** Section: 0103
 ** Email : tri1@umbc.edu
 **
 ** This files holds the functions related only to the
 ** board.
 ****************************************************/

#include <stdio.h>
#include "connect4.h"


#define ROW 6 /* the rows of the array: board */
#define COL 7

/**********************************************
 ** Function: InitializeBoard()
 ** This function initializes the playing
 ** field with blank spaces in the array.
 **
 ** Inputs: the array holding the playing field
 ** Outputs: void
 ***********************************************/
void InitializeBoard (char board[ROW][COL])
{
   int rowcount, colcount; /* initialize counters */

   for ( rowcount = 0; rowcount < ROW; rowcount++ ) /* count rows */
   {
      for ( colcount = 0; colcount < COL; colcount++ ) /* count columns */
      {
         board[rowcount][colcount] = ' '; /* set value to blank space */
      }
   }

}


/*****************************************
 ** Function: PrintBoard()
 ** This function prints the playing field
 ** on the screen.
 **
 ** Inputs: the array holding the field
 ** Outputs: void
 ****************************************/
void PrintBoard (char board[ ][ ]);
void PrintBoard (char board[ROW][COL])
{
   int rowcount, colcount; /* initialize counters */

   printf("\n"); /* sets the board to be drawn apart */
   
   for ( rowcount = 0; rowcount < ROW; rowcount++ ) /* generate row */
   {
   
      printf("|---|---|---|---|---|---|---|\n"); /* print bar */

      for ( colcount = 0; colcount < COL; colcount++ ) /* count column and print */
      {
         printf("| %c ", board[rowcount][colcount]);
      }
      printf("|\n");
   }

   printf("|---|---|---|---|---|---|---|\n"); /* print the end of the board */
   printf("  1   2   3   4   5   6   7\n"); /* prints column numbers */
   printf("\n");

}
