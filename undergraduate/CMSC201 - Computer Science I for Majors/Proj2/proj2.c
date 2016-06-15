/****************************************************
 ** File: proj2.c
 ** Author: Patrick Trinkle
 ** Date: 3/8/2004
 ** Section: 0103
 ** Email : tri1@umbc.edu
 **
 ** This program allows you to play connect4 against
 ** the computer in two modes, test and play.
 ****************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "connect4.h" /* the header file with the function prototypes */

#define ROW 6 /* the rows of the array: board */
#define COL 7

int main()
{
   int seed, type, columnnum, win;  /* initialize the variables */ 
   char board[ROW][COL], player[1]; /* initialize my two arrays */
   
   win = -1; /* allows the game to play from the start using the loop at the bottom */

   PrintGreeting(); /* prints greeting */
   PrintInstructions(); /* prints instructions */

   printf("Please hit either, 1 or 2 to choose which type of game:\n 1 for Test, 2 for Play : ");
   scanf("%d", &type); /* reads user input for mode of play */

   InitializeBoard(board); /* initializes the board with blank spaces */
   PrintBoard(board); /* prints the board for the user to see */
   
   if (type == 1)
   {
      seed = TestSeed(); /* this function gets the seed from the user */
   }
   else
   {
      seed = time ( 0 );
   }
   srand ( seed );

   player[0] = 'O'; /* makes your move first */

   while (win != 3 && win != 1) /* This statement controls the game to keep it going or stop it  */
   {
      columnnum = TurnPrompt(player, board); /* prompts the user or the computer */
      columnnum = PlacePiece(columnnum, board, player); /* places the piece */
      PrintBoard(board); /* prints the board with the newly placed piece */
      win = WinCheck(board, player, columnnum); /* tests for a win or a tie, if neither it moves on */
      if (player[0] == 'X')
      {
	 player[0] = 'O';
      }
      else
      {
         player[0] = 'X';
      }
   }

   printf("Closing...");

   return 0;
}
