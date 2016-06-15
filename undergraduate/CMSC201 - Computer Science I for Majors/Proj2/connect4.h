/****************************************************
 ** File: connect.h
 ** Author: Patrick Trinkle
 ** Date: 3/9/2004
 ** Section: 0103
 ** Email : tri1@umbc.edu
 **
 ** This files holds the function prototypes
 ****************************************************/


/*****************************************
 ** Function: PrintGreeting()
 ** This function displays the greeting.
 **
 ** Inputs: void
 ** Outputs: void
 ****************************************/
void PrintGreeting (void);


/*****************************************
 ** Function: PrintInstructions()
 ** This function prints the instructions.
 **
 ** Inputs: void
 ** Outputs: void
 ****************************************/ 
void PrintInstructions (void);


/**********************************************
 ** Function: InitializeBoard()
 ** This function initializes the playing
 ** field with blank spaces in the array.
 **
 ** Inputs: the array holding the playing field
 ** Outputs: void
 ***********************************************/
void InitializeBoard (char board[ ][ ]);


/*****************************************
 ** Function: TestSeed()
 ** This function asks for a seed from the 
 ** user to use when the computer plays.
 **
 ** Inputs: void
 ** Outputs: the user defined seed
 ****************************************/
int  TestSeed (void);


/*****************************************
 ** Function: PrintBoard()
 ** This function prints the playing field
 ** on the screen.
 **
 ** Inputs: the array holding the field
 ** Outputs: void
 ****************************************/
void PrintBoard (char board[ ][ ]);


/*****************************************
 ** Function: TurnPrompt()
 ** This function this function finds out
 ** who needs to make a move and calls to
 ** user or to the computer for a column,
 ** in which to place the piece.
 **
 ** Inputs: the array holding which player
 **         is currently playing
 ** Outputs: the chosen column, either
 **          either from the computer or
 **          or the user
 ****************************************/
int  TurnPrompt (char player[ ],  char board[ ][ ]);


/*****************************************
 ** Function: CompMove()
 ** This function calls the seed and then 
 ** generates a random column to place its
 ** piece.
 **
 ** Inputs: void
 ** Outputs: the computer chosen column
 ****************************************/
int  CompMove (void);


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
int  PlacePiece (int columnnum, char board[ ][ ], char player[ ]);


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
int  WinCheck (char board[ ][ ], char player[ ], int columnnum);


/*****************************************
 ** Function: HorizCheck()
 ** This function checks for a win to the
 ** left and right of the piece.
 **
 ** NOTE: More efficient than what I previously had
 **
 ** Inputs: the board and the piece of current player
 ** Outputs: if there was a win
 ****************************************/
int  HorizCheck (char board[ ][ ], char piece);


/*****************************************
 ** Function: VertCheck()
 ** This function checks for a win up and
 ** down.
 **
 ** Inputs: the board, and
 **         where the last piece was placed
 **         , and the current piece type
 ** Outputs: if there was a win
 ****************************************/
int  VertCheck (char board[ ][ ], int columnnum, char piece);


/*****************************************
 ** Function: DiagCheck()
 ** This function checks for a win diagonally.
 **
 ** Inputs: the board, and
 **         the player's piece
 ** Outputs: if there was a win
 ****************************************/
int  DiagCheck (char board[ ][ ], char piece); 


/*****************************************
 ** Function: FullBoard()
 ** This function checks to see if the board
 ** is full and there is a tie.
 **
 ** Inputs: the board
 ** Outputs: if there was a tie
 ****************************************/
int  FullBoard (char board[ ][ ]);
