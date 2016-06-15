/****************************************************
** File: print.c
** Author: Patrick Trinkle
** Date: 5/7/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the printing functions for
** proj5
****************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "train.h"
#include "print.h"

/*****************************************
** Function: PrintGreeting()
** This function displays the greeting.
**
** Inputs:  void
** Outputs: void
****************************************/
void PrintGreeting(void)
{
   /* Print an on-screen greeting */
   fprintf(stdout, "\nWelcome to the Train Switching Station Control System\n");
   fprintf(stdout, "Instructions are printed out below after the incoming train has been analyzed.\n\n");
}

/*****************************************
** Function: BuildInstructions()
** This function prints out the
** instructions for the switch controller
**
** Inputs:  pointer to the track pointer
**          to the transfer track's
**          head node and the queue's
**          head node.
** Outputs: void
****************************************/
void BuildInstructions(TRACKPTR * transferheadnodePtr, TRACKPTR * queueheadnodePtr)
{
   NODEPTR lead, end;
   int id = 0;

   /* set cars to be examined */
   lead = (*transferheadnodePtr) -> head;
   end = (*queueheadnodePtr) -> head;
   id = lead -> trackId;

   if ((*transferheadnodePtr) -> numCars > 1)
   {
      /* instructions for if the stack held multiple cars, all going to the same place */
      fprintf(stdout, "Uncouple between cars %d and %d and back them onto track %d\n", lead -> data.carNum, end -> data.carNum, id);
   }
   else
   {
      /* only one car in the transfer stack */
      fprintf(stdout, "Uncouple between cars %d and %d and back car %d onto track %d\n", lead -> data.carNum, end -> data.carNum, lead -> data.carNum, id);
   }
}

/*****************************************
** Function: BuildFinalInstructions()
** This function prints out the last
** instructions for the switch controller
**
** Inputs:  pointer to the track pointer
**          to the transfer track's
**          head node.
** Outputs: void
****************************************/
void BuildFinalInstructions(TRACKPTR * transferheadnodePtr)
{
   NODEPTR curr;
   int id = 0;

   /* set the car to be viewed */
   curr = (*transferheadnodePtr) -> head;

   id = curr -> trackId;

   if ((*transferheadnodePtr) -> numCars > 1)
   {
      /* if multiple cars in the transfer stack and the queue is empty. */
      fprintf(stdout, "Back remaining cars onto track %d\n", id);
   }
   else
   {
      /* only one car on the transfer stack and the queue is empty */
      fprintf(stdout, "Back remaining car %d onto track %d\n", curr -> data.carNum, id);
   }
}

/*****************************************
** Function: PrintAcctFiles()
** This function prints the accounting
** files for the different tracks.
**
** Inputs:  pointer to the track pointer
**          to the track and a pointer
**          to the file pointer for
**          output
** Outputs: void
****************************************/
void PrintAcctFiles(TRACKPTR * track, FILE * ofp)
{
   /* prints accounting output files based on the track */

   fprintf(ofp, "Track %d: A total of %d cars board for %s\n\n", (*track) -> trackId, (*track) -> numCars, (*track) -> destination);
   
   PrintData(track, ofp);
   PrintTotals(track, ofp);
}
