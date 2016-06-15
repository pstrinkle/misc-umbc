/****************************************************
** File: other.c
** Author: Patrick Trinkle
** Date: 5/7/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the odd functions for
** proj5
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "other.h"

/*****************************************
** Function: IsEmpty()
** This function tests to see if the
** stack or queue is empty
**
** Inputs:  pointer to track pointer for
**          the track queue or stack
**
** Outputs: int called flag that if true
**          then the queue or stack is
**          empty
**
****************************************/
int IsEmpty(TRACKPTR * track)
{
   int flag = 0;

   /* checks the head of the track */
   if ((*track) -> head == NULL)
   {
      flag = 1;
      return flag;
   }
   else
   {
      return flag;
   }
}

/*****************************************
** Function: InitiateTrack()
** This function initializes the head
** nodes for the different tracks
**
** Inputs:  pointer to the track pointer
**          to the track to be created.
** Outputs: void
****************************************/
void InitiateTrack(TRACKPTR * track)
{
   /* remove all garbages and set pointers to null */
   (*track) -> head = NULL;
   (*track) -> tail = NULL;
   (*track) -> numCars = 0;
   (*track) -> totalWeight = 0;
   (*track) -> totalCost = 0.00;
   strcpy((*track) -> destination, "");
   (*track) -> trackId = 0;
}
