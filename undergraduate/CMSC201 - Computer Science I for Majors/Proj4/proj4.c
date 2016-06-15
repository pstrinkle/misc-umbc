/****************************************************
** File: proj4.c
** Author: Patrick Trinkle
** Date: 4/23/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This program reads a file indicated by the user
** and reads in the file, a list of strings and with
** that allows the user to obtain information about
** the different strings, if they're palindromes or
** not.
****************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "palindromes.h"

int main(int argc, char * argv[])
{
   /* declare pointer to pointer to char, or array of strings */
   char * * arrayofstrings;

   /* declare menu read-ins */
   char subChoice, trash;

   /* declare return calculation variables */
   int numStrings, stringId, vowelCount, numCons, numWords, stringLen;
   
   /* declare file pointer */
   FILE * ifp;

   /* not enough command arguments */
   if (argc != 2)
   {
      fprintf(stderr, "You need to enter in the input data file.\n");
      exit(-1);
   }

   /* open the file */
   ifp = fopen(argv[1], "r");
   
   /* couldn't open the file then */
   if (ifp == NULL)
   {
      fprintf(stderr, "File could not be opened.\n");
      exit(-2);
   }
   
   /* prints the greeting */
   PrintGreeting();   

   /* get the number of strings in the file */
   numStrings = FindNumStrings(ifp);

   /* rewind the file pointer */
   rewind(ifp);

   /* allocate the memory required to hold the pointers in the array */
   *arrayofstrings = GetArrayMem(numStrings);

   /* put the strings into the place and allocate the memory for them */
   ReadStrings(ifp, numStrings, arrayofstrings);

   /* close the file */
   fclose(ifp);

   /* activate the menu variable */
   stringId = 0;

   /* main string list menu */
   while (stringId != -1)
   {
      /* print the list of strings in menu form */
      PrintMenu(arrayofstrings, numStrings);

      /* read in user entry and remove new line character */
      scanf("%d%c", &stringId, &trash);

      /* test user entry for validity */
      while (stringId > numStrings || stringId < 0)
      {
         printf("Invalid entry, try again : 1 - %d\n", numStrings);
         printf("Enter Choice : ");
         scanf("%d%c", &stringId, &trash);
      }

      /* take the user input to match the appropriate string */
      stringId--;

      /* if they chose then bring up sub menu */
      if (stringId != -1)
      {
         /* activate the sub menu variable */
         subChoice = '\n';
         
         /* sub menu */
         while (subChoice != 'q')
         {
            /* print the string chosen */
            PrintString(arrayofstrings, stringId);         

            /* print the options */
            PrintSubMenu();

            printf("Enter Choice : ");

            /* read in choice and new line character */
            scanf("%c%c", &subChoice, &trash);
 
            /* convert their choice to a lower case letter */
            subChoice = tolower(subChoice);

            /* if they chose */
            if (subChoice != 'q')
            {
               /* menu switch options */
               switch (subChoice)
               {
                  case 'v': /* choice v to tell user how many vowels */
                     vowelCount = VowelCount(arrayofstrings, stringId);
                     printf("\nThere are %d vowels in \"%s\"\n", vowelCount, arrayofstrings[stringId]);
                     break;
                  case 'c': /* choice c to tell user how many consonants */
                     numCons = ConsonantCount(arrayofstrings, stringId);
                     printf("\nThere are %d consonants in \"%s\"\n", numCons, arrayofstrings[stringId]);
                     break;
                  case 'w': /* choice w to tell user how many words */
                     numWords = WordCount(arrayofstrings, stringId);
                     printf("\n\"%s\" consists of %d word(s).\n", arrayofstrings[stringId], numWords);
                     break;
                  case 'l': /* choice l to tell user the length of the string */
                     stringLen = StringLength(arrayofstrings, stringId);
                     printf("\nThe length of \"%s\" is %d\n", arrayofstrings[stringId], stringLen);
                     break;
                  case 'p': /* choice p purges the strings and checks and returns if palindrome */
                     StringPurge(arrayofstrings, stringId);
                     break;
                  default: /* invalid selection */
                     printf("\nInvalid Selection, try again.\n");
                     break;
               }
            }  
         }
      }  

   }

   /* function to free all allocated memory */
   FreeMemory(arrayofstrings, numStrings);

   return 0;
}
