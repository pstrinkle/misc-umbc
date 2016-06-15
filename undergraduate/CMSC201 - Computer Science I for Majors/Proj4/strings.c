/****************************************************
** File: proj4.c
** Author: Patrick Trinkle
** Date: 4/23/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the functions used by 
** proj4.c Proj4.c reads in strings from a file
** and lists the strings and with
** that allows the user to obtain information about
** the different strings, if they're palindromes or
** not.
****************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "palindromes.h"

/*****************************************
** Function: PrintGreeting()
** This function displays the greeting.
**
** Inputs:  void
** Outputs: void
*****************************************/
void PrintGreeting(void)
{
   /* prints the greeting */
   printf("\n\nThis program will read in the strings from your data file.\n");
   printf("and will determine different things about the strings.\n");
   printf("to include if it's a palindrome or not.\n");
   printf("\n");
   printf("A palindrome is defined as a word or sentence that\n");
   printf("is the same whether read forward or backward.\n");
}

/*****************************************
** Function: FindNumStrings()
** This function finds the number of
** strings in the file.
**
** Inputs:  the file pointer
** Outputs: int numStrings == the number
**          of strings in the file.
*****************************************/
int FindNumStrings(FILE * ifp)
{
   int numStrings = 0;

   char tempString[100];

   /* this adds up the number of strings in the file */
   while(fgets(tempString, 100, ifp) != NULL)
   {
      numStrings++;
   }

   return numStrings;
}

/*****************************************
** Function: GetArrayMem()
** This gets the memory for the array.
**
** Inputs:  the number of strings
** Outputs: the address or whatever
**          char * * arrayofstrings
*****************************************/
char * GetArrayMem(int numStrings)
{

   char * memSpace;

   /* allocates memory for the array of pointers */
   memSpace = (char *)malloc(numStrings * sizeof(char));

   /* if no space found, exit! */
   if (memSpace == NULL)
   {
      fprintf(stderr, "Could not find the memory.\n");
      exit(-3);
   }

   return memSpace;
}

/*****************************************
** Function: ReadStrings()
** This reads the strings from the file
**
** Inputs:  the number of strings, the
**          file pointer, and the address
**          of the array of strings
** Outputs: void
*****************************************/
void ReadStrings(FILE * ifp, int numStrings, char * * arrayofstrings)
{
   int i, strLen;

   char tempString[100];

   char * tempPtr;

   /* read in the strings */
   for (i = 0; i < numStrings; i++)
   {
      fgets(tempString, 100, ifp);

      strLen = strlen(tempString);

      tempString[strLen - 1] = '\0';

      /* allocates the space for the string */
      tempPtr = (char *)malloc(strLen * sizeof(char));

      (char *)arrayofstrings[i] = tempPtr;

      /* if not enough space, exit */
      if (tempPtr == NULL)
      {
         fprintf(stderr, "Not enough memory.\n");
         exit(-4);
      }

      /* copies the string from the temp to the array location */
      strcpy(arrayofstrings[i], tempString);
   }
}

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
int VowelCount(char * * arrayofstrings, int stringId)
{
   int i, vowelCount, strLen;

   vowelCount = 0;

   strLen = 0;

   char tempString[100];

   char letter;

   /* copies the string into a temporary string */
   strcpy(tempString, arrayofstrings[stringId]);

   strLen = strlen(tempString);

   /* checks the letters of the string for vowels */
   for (i = 0; i < strLen; i++)
   {
      tempString[i] = tolower(tempString[i]);

      letter = tempString[i];

      /* checks to see if the letter is a vowel */
      if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u')
      {
         vowelCount++;
      }
   }

   return vowelCount;
}

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
int WordCount(char * * arrayofstrings, int stringId)
{
   int i, iswhiteSpace, strLen, numWords = 1;

   char tempString[100];

   /* copies the array into a temporary string */
   strcpy(tempString, arrayofstrings[stringId]);

   strLen = strlen(tempString);

   /* counts the words in the string */
   for (i = 0; i < strLen; i++)
   {
      iswhiteSpace = isspace(tempString[i]);

      if (iswhiteSpace != 0)
      {
         numWords++;
      }
   }

   return numWords;
}

/*****************************************
** Function: StringLength()
** Calculates the length of the string.
**
** Inputs:  the location of the array of
**          strings and the string Id
** Outputs: int stringLen--the length of
**          the string.
*****************************************/
int StringLength(char * * arrayofstrings, int stringId)
{
   int stringLen;

   /* calculates the length of the string */
   stringLen = strlen(arrayofstrings[stringId]);

   return stringLen;
}

/*****************************************
** Function: FreeMemory()
** Frees all your allocated memory.
**
** Inputs:  the location of the array of
**          strings and the number of
**          strings.
** Outputs: void
*****************************************/
void FreeMemory(char * * arrayofstrings, int numStrings)
{
   int i;
 
   /* run through the pointers to free space! */
   for (i = 0; i < numStrings; i++)
   {
      free(arrayofstrings[i]);
   }
 
   /* frees the main space! */
   free(arrayofstrings);
}

/*****************************************
** Function: PrintMenu()
** Prints the list of strings in menu form
**
** Inputs:  the number of strings and the
**          address of the array of strings
** Outputs: void
*****************************************/
void PrintMenu(char * * arrayofstrings, int numStrings)
{
   int i;

   printf("\n");

   printf("The strings are : \n");

   printf("\n");

   /* prints the menu */
   for (i = 0; i < numStrings; i++)
   {
      printf("%2d - \"%s\"", i+1, arrayofstrings[i]);

      printf("\n");
   }

   printf("\n");

   printf(" 0 - Enter 0 to end the program\n\n");

   printf("Enter choice : ");
}

/*****************************************
** Function: PrintSubMenu()
** Prints the sub menu
**
** Inputs:  void
** Outputs: void
*****************************************/
void PrintSubMenu(void)
{
   /* prints the sub menu */
   printf("\n");
   printf("        P - Is this string a palindrome ?\n");
   printf("        V - How many vowels ?\n");
   printf("        C - How many consonants ?\n");
   printf("        L - What's its length ?\n");
   printf("        W - How many words ?\n");
   printf("\n");
   printf("        Q - Quit\n\n");
}

/*****************************************
** Function: PrintString()
** Prints the string chosen
**
** Inputs:  the string id and the
**          address of the array of strings
** Outputs: void
*****************************************/
void PrintString(char * * arrayofstrings, int stringId)
{
   /* prints the string! */
   printf("\n        Analysis of the string :\n");

   printf("        \"%s\"", arrayofstrings[stringId]);

   printf("\n\n");
}

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
int ConsonantCount(char * * arrayofstrings, int stringId)
{
   int i, numCons, strLen, alphaCount;

   numCons = 0;

   strLen = 0;

   alphaCount = 0;

   char tempString[100];

   char letter;

   /* copies the string into a temporary string */
   strcpy(tempString, arrayofstrings[stringId]);

   strLen = strlen(tempString);

   /* counts all letters */
   for (i = 0; i < strLen; i++)
   {
      alphaCount = isalpha(tempString[i]);

      if (alphaCount != 0)
      {
         numCons++;
      }
   }
 
   /* subtracts for all vowels */
   for (i = 0; i < strLen; i++)
   {
      tempString[i] = tolower(tempString[i]);

      letter = tempString[i];

      if (letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u')
      {
         numCons--;
      }
   }

   return numCons;
}

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
void StringPurge(char * * arrayofstrings, int stringId)
{
   int i, j, strLen, isAlpha, numStart, numEnd, isPalindrome;

   char * temp;

   strLen = strlen(arrayofstrings[stringId]);

   /* allocates the memory required for the strings */
   temp = (char *)malloc((strLen + 1) * sizeof(char));

   /* checks the memory availability */
   if (temp == NULL)
   {
      fprintf(stderr, "Not enough memory.\n");
      exit(-5);
   }

   /* copies the string into the temporary string */
   strcpy(temp, arrayofstrings[stringId]);

   /* checks to see if it's a letter, if not then it removes and adjusts the string */
   for (i = 0; i < strLen; i++)
   {
      isAlpha = isalpha(temp[i]);

      if (isAlpha == 0)
      {
         for (j = i; j < strLen; j++)
         {
            temp[j] = temp[j+1];
         }
        
         strLen--;
         i--;
      }
   }

   numStart = 0;
 
   numEnd = strlen(temp) - 1;

   isPalindrome = 0;

   strLen = strlen(temp);

   /* converts all letters in string to be lower case */
   for (i = 0; i < strLen; i++)
   {
      temp[i] = tolower(temp[i]);
   }

   /* recursive palindrome function */
   isPalindrome = IsPalindrome(temp, numStart, numEnd);

   /* prints the results of the palindrome recursion! */
   if (isPalindrome == -1)
   {
      printf("\n\"%s\" is not a palindrome\n", arrayofstrings[stringId]);
   }
   else
   {
      printf("\n\"%s\" is a palindrome.\n", arrayofstrings[stringId]);
   }
 
   /* free memory allocated for purged string */
   free(temp);
}

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
int IsPalindrome(char * temp, int numStart, int num\
End)
{
   int strLen, isPalindrome;

   strLen = strlen(temp);

   /* checks to see if the letters match */
   if (numStart + 1 != numEnd && numStart != numEnd)
   {
      if (temp[numStart] == temp[numEnd])
      {
         IsPalindrome(temp, numStart+1, numEnd-1);
      }
      else
      {
         isPalindrome = -1;
      }
   }

   return isPalindrome;
}
