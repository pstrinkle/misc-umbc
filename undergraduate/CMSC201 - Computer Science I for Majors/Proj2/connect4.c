/****************************************************
 ** File: connect4.c
 ** Author: Patrick Trinkle
 ** Date: 3/8/2004
 ** Section: 0103
 ** Email : tri1@umbc.edu
 **
 ** This files holds the other functions
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "connect4.h"

#define ROW 6 /* the rows of the array: board */
#define COL 7

/*****************************************
 ** Function: PrintGreeting()
 ** This function displays the greeting.
 **
 ** Inputs: void
 ** Outputs: void
 ****************************************/
void PrintGreeting (void)
{
   printf("Welcome to Connect 4, C Style!\n");
   printf(" by Patrick Trinkle\n\n");
   printf("Follow the instructions below:\n");
}


/*****************************************
 ** Function: PrintInstructions()
 ** This function prints the instructions.
 **
 ** Inputs: void
 ** Outputs: void
 ****************************************/
void PrintInstructions (void)
{
   printf("To play:\n");
   printf("First choose type of game : Test or Play\n");
   printf("Then if you choose play, you will have the opportunity to enter the value of the column\n");
   printf("into which you wish to place your token.\n");
   printf("Then the computer will go, and the game will continue as such until there is a winner or a tie.\n");
   printf("To win you must get three pieces in a row, vertically, horizontally or diagonally.\n");
   printf("\n");
   printf("If you choose test, you will need to feed the random number generator.\n");
   printf("\n");

}


/*****************************************
 ** Function: TestSeed()
 ** This function asks for a seed from the 
 ** user to use when the computer plays.
 **
 ** Inputs: void
 ** Outputs: the user defined seed
 ****************************************/
int TestSeed(void)
{
   int seed;

   printf("Enter in a seed for random number generator : ");
   scanf("%d", &seed);

   return seed;
}



/*****************************************
 ** Function: TurnPrompt()
 ** This function this function finds out
 ** who needs to make a move and calls to
 ** user or to the computer for a column,
 ** in which to place the piece.
 **
 ** Inputs: the array holding which player
 **         is currently playing.
 ** Outputs: the chosen column, either
 **          either from the computer or
 **          or the user
 ****************************************/
int TurnPrompt (char player[1],  char board[ROW][COL])
{
   int columnnum, rowcount, accum;

   
   if (player[0] == 'X')
   {
      columnnum = CompMove();

      /* check to see if column is full: */

      accum = 0;

      for ( rowcount = 0; rowcount < ROW; rowcount++ )
      {
         if (board[rowcount][columnnum] == 'X')
         {
            accum++;
         }
         else if (board[rowcount][columnnum] == 'O')
         {
   	    accum++;
         }
         else
         {
         }
      }

      while (accum == 6)
      {
         columnnum = CompMove();
       
	 for ( rowcount = 0; rowcount < ROW; rowcount++ )
	 {
	    if (board[rowcount][columnnum] == 'X')
	    {
	       accum++;
	    }
	    else if (board[rowcount][columnnum] == 'O')
	    {
	       accum++;
	    }
	 }
  
      }       
   }
   
   else
   {
      columnnum = -1;
      accum = 0;

      while (columnnum < 0 || columnnum > 6 || accum == 6)
      {
         printf("It is your turn.\n");
         printf("Please choose a column : ");
         scanf("%d", &columnnum);
         columnnum = columnnum - 1;
         
         /* check to see if column is full: */    

         for ( rowcount = 0; rowcount < ROW; rowcount++ )
         {
            if (board[rowcount][columnnum] == 'X')
            {
               accum++;
            }
            else if (board[rowcount][columnnum] == 'O')
	    {
	       accum++;
	    }
         }  
      }
    
   }

   return columnnum;
}



/*****************************************
 ** Function: CompMove()
 ** This function calls the seed and then 
 ** generates a random column to place its
 ** piece.
 **
 ** Inputs: void
 ** Outputs: the computer chosen column
 ****************************************/
int CompMove (void)
{
   int columnnum;

   columnnum = rand() % 7; /* 0 through 6 */
   
   return columnnum;
}



/*****************************************
 ** Function: PlacePiece()
 ** This function places your piece in the
 ** column after checking if the column is
 ** full or not.
 **
 ** Inputs: the chosen column number, the 
 **         array of the board and who is
 **         playing(computer or user)
 ** Outputs: the column number
 ****************************************/
int PlacePiece (int columnnum, char board[ROW][COL], char player[1])
{
   char piece;
   int rowcount;

   if (player[0] == 'O')
   {
      piece = 'O';
   }
   else
   {
      piece = 'X';
   }

   for (rowcount = 5; rowcount >= 0; rowcount--)
   {
      if (board[rowcount][columnnum] == ' ')
      {
	 board[rowcount][columnnum] = piece;
	 return columnnum;
      }
   }

   return columnnum;
}
