/****************************************************
** File: palindromes.h
** Author: Patrick Trinkle
** Date: 4/23/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains the prototypes for the
** functions in the Proj4.c and strings.c files.
****************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


/*****************************************
** Function: PrintGreeting()
** This function displays the greeting.
**
** Inputs:  void
** Outputs: void
*****************************************/
void PrintGreeting (void);

/*****************************************
** Function: FindNumStrings()
** This function finds the number of
** strings in the file. 
**
** Inputs:  the file pointer
** Outputs: int numStrings == the number
**          of strings in the file.
*****************************************/
int FindNumStrings(FILE * ifp);

/*****************************************
** Function: GetArrayMem()
** This gets the memory for the array.
**
** Inputs:  the number of strings
** Outputs: the address or whatever
**          char * * arrayofstrings
*****************************************/
char * GetArrayMem(int numStrings);

/*****************************************
** Function: ReadStrings()
** This reads the strings from the file
** 
** Inputs:  the number of strings, the
**          file pointer, and the address
**          of the array of strings
** Outputs: void
*****************************************/
void ReadStrings(FILE * ifp, int numStrings, char * * arrayofstrings);

/*****************************************
** Function: VowelCount()
** Calculates the number of vowels in the
** string.
**
** Inputs:  the location of the array of
**          strings and the string Id
** Outputs: int numVowels--the number of
**          vowels in the string.
*****************************************/
int VowelCount(char * * arrayofstrings, int stringId);

/*****************************************
** Function: ConsonantCount()
** Calculates the number of consonants in
** the string.
**
** Inputs:  the location of the array of
**          strings and the string Id
** Outputs: int numCons--the number of
**          consonants in the string.
*****************************************/
int ConsonantCount(char * * arrayofstrings, int stringId);

/*****************************************
** Function: WordCount()
** Calculates the number of words in the
** string. 
**
** Inputs:  the location of the array of
**          strings and the string Id
** Outputs: int numWords--the number of
**          words in the string.
*****************************************/
int WordCount(char * * arrayofstrings, int stringId);

/*****************************************
** Function: StringLength()
** Calculates the length of the string.
**
** Inputs:  the location of the array of
**          strings and the string Id
** Outputs: int stringLen--the length of
**          the string.
*****************************************/
int StringLength(char * * arrayofstrings, int stringId);

/*****************************************
** Function: FreeMemory()
** Frees all your allocated memory.
**
** Inputs:  the location of the array of
**          strings and the number of
**          strings.
** Outputs: void
*****************************************/
void FreeMemory(char * * arrayofstrings, int numStrings);

/*****************************************
** Function: PrintMenu()
** Prints the list of strings in menu form
**
** Inputs:  the number of strings and the
**          address of the array of strings
** Outputs: void
*****************************************/
void PrintMenu(char * * arrayofstrings, int numStrings);

/*****************************************
** Function: PrintSubMenu()
** Prints the sub menu
**
** Inputs:  void
** Outputs: void
*****************************************/
void PrintSubMenu(void);

/*****************************************
** Function: PrintString()
** Prints the string chosen
**
** Inputs:  the string id and the
**          address of the array of strings
** Outputs: void
*****************************************/
void PrintString(char * * arrayofstrings, int stringId);

/*****************************************
** Function: IsPalindrome()
** Is recursive and checks if it's a 
** palindrome.
**
** Inputs:  the address of a purged string
**          the starting integer, and the
**          ending integer.
** Outputs: an integer saying if it's 
**          a palindrome or not.
*****************************************/
int IsPalindrome(char * temp, int numStart, int numEnd);

/*****************************************
** Function: StringPurge()
** Purges the string of all non-alpha
** and also runs the recursion function
** to check for palindromes.
**
** Inputs:  the string id and the address
**          of the array of strings.
** Outputs: void
*****************************************/ 
void StringPurge(char * * arrayofstrings, int stringId);

