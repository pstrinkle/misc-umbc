/****************************************************
 ** File: winchecks.c
 ** Author: Patrick Trinkle
 ** Date: 3/9/2004
 ** Section: 0103
 ** Email : tri1@umbc.edu
 **
 ** This files holds the functions that check for a win
 ****************************************************/

#include <stdio.h>
#include "connect4.h"

#define ROW 6 /* the rows of the array: board */
#define COL 7

/*****************************************
 ** Function: VertCheck()
 ** This function checks for a win up and
 ** down.
 **
 ** Inputs: the board, and
 **         where the last piece was placed
 ** Outputs: if there was a win
 ****************************************/
int VertCheck (char board[ROW][COL], int columnnum, char piece)
{
   int cn, win;

   cn = columnnum;
   win = 0;  /* 1 means a player won */
   
   if ( piece == board[5][cn] && board[5][cn] == board[4][cn] && board[4][cn] == board[3][cn] && board[3][cn] == board[2][cn] )
   {
      win = 1;
   }
   else if ( piece == board[4][cn] && board[4][cn] == board[3][cn] && board[3][cn] == board[2][cn] && board[2][cn] == board[1][cn] )
   {
      win = 1;
   }
   else if ( piece == board[3][cn] && board[3][cn] == board[2][cn] && board[2][cn] == board[1][cn] && board[1][cn] == board[0][cn] )
   {
      win = 1;
   }
   else
   {
   }
   return win;
}


/*****************************************
 ** Function: HorizCheck()
 ** This function checks for a win to the
 ** left and right of the piece.
 **
 ** NOTE: More efficient than what I previously had
 **
 ** Inputs: the board
 ** Outputs: if there was a win
 ****************************************/
int HorizCheck (char board[ROW][COL], char piece)
{
   int i, win;
   win = 0; /* 1 means a player won */

   for ( i = 0; i < ROW; i++ )
   {
      if ( piece == board[i][0] && board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][2] == board[i][3])
      {
         win = 1;
      }
      
      else if ( piece == board[i][1] && board[i][1] == board[i][2] && board[i][2] == board[i][3] && board[i][3] == board[i][4])
	 {
	    win = 1;
	 }

      else if ( piece == board[i][2] && board[i][2] == board[i][3] && board[i][3] == board[i][4] && board[i][4] == board[i][5])
	 {
	    win = 1;
	 }

      else if ( piece == board[i][3] && board[i][3] == board[i][4] && board[i][4] == board[i][5] && board[i][5] == board[i][6])
	 {
	    win = 1;
	 }

   }
   
   return win;
}

/*****************************************
 ** Function: DiagCheck()
 ** This function checks for a win diagonally.
 **
 ** Inputs: the board, and
 **         the player's piece
 ** Outputs: if there was a win
 ****************************************/
int  DiagCheck (char board[ROW][COL], char piece)
{
   int i, j, win;
   
   win = 0;
   /* first diagonal direction check */   
   for (i = 5; i > 2; i--)
   {
      for (j = 0; j < 4; j++)
      {
         if ( piece == board[i][j] && board[i][j] == board[i-1][j+1] && board[i-1][j+1] == board[i-2][j+2] && board[i-2][j+2] == board[i-3][j+3] )
         {
            win = 1;
            return win;
         }
      }
   }

   /* second diagonal check */
   for (i = 0; i < 3; i++)
   {
      for (j = 0; j < 4; j++)
      {
         if ( piece == board[i][j] && board[i][j] == board[i+1][j+1] && board[i+1][j+1] == board[i+2][j+2] && board[i+2][j+2] == board[i+3][j+3] )
         {
            win = 1;
            return win;
         }
      }
   }

   return win;
}



/*****************************************
 ** Function: FullBoard()
 ** This function checks to see if the board
 ** is full and there is a tie.
 **
 ** Inputs: the board
 ** Outputs: if there was a tie
 ****************************************/
int FullBoard (char board[ROW][COL])
{
   int rowcount, colcount, accum, win;
   win = 0; /* 3 means tie */
   accum = 0;

   for ( rowcount = 0; rowcount < ROW; rowcount++ )
   {
      for ( colcount = 0; colcount < COL; colcount++ )
      {

         if (board[rowcount][colcount] == 'X')
         {
            accum++;
         }
         else if (board[rowcount][colcount] == 'O')
	 {
            accum++;
         }

      }
   }
   
   if (accum == 42)
   {
      win = 3;
   }

   return win;
}


/*****************************************
 ** Function: WinCheck()
 ** This function will check where the last
 ** piece was placed and then check whose 
 ** turn it is and check the board, this
 ** function houses the actual functions
 ** that do the checking. It also changes
 ** whose turn it is after it checks.
 **
 ** Inputs: the playing field, the player
 **         and the last column used
 ** Outputs: whether someone who won, if
 **          anyone or if there was a tie
 ****************************************/
int WinCheck (char board[ROW][COL], char player[1], int columnnum)
{
   int win;
   char piece;
   
   if (player[0] == 'X')
   {
      piece = 'X';
   }
   else
   {
      piece = 'O';
   }
   
   win = VertCheck (board, columnnum, piece);
   
   if (win == 1 && player[0] == 'O')
   {
      printf("You win!\n\n");
      return win;
   }
   else if (win == 1 && player[0] == 'X')
   {
      printf("You lose!\n\n");
      return win;
   }

   win = HorizCheck (board, piece);

   if (win == 1 && player[0] == 'O')
   {
      printf("You win!\n\n");
      return win;
   }
   else if (win == 1 && player[0] == 'X')
   {
      printf("You Lose!\n\n");
      return win;
   }

   win = DiagCheck (board, piece);

   if (win == 1 && player[0] == 'O')
   {
      printf("You win!\n\n");
      return win;
   }
   else if (win == 1 && player[0] == 'X')
   {
      printf("You Lose!\n\n");
      return win;
   }

   win = FullBoard (board);

   if (win == 3)
   {
      printf("Tie!\n");
      return win;
   }

   return win;
}
