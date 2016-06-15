/****************************************************
** File: stack.c
** Author: Patrick Trinkle
** Date: 5/7/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the functions involving
** the stack ADT with the exception of IsEmpty
**
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "queue.h"
#include "print.h"
#include "other.h"

/*****************************************
** Function: DestroyStack()
** This function fress the memory in the
** stack and sets all pointers to NULL
**
** Inputs:  a pointer to a trackpointer
**          to the track's head node
** Outputs: void
**
****************************************/
void DestroyStack(TRACKPTR * trackheadnodePtr)
{
   /* set up place holder nodes */
   NODEPTR prev, curr, waynext;

   prev = NULL;

   /* make curr the starting point */
   curr = (*trackheadnodePtr) -> head;

   /* set the tail pointer to null */
   (*trackheadnodePtr) -> tail = NULL;

   while (curr != NULL)
   {
      /* set pointers to null and free memory one car at a time */
      prev = curr;
      waynext = curr -> next;
      curr -> next = NULL;
      free(curr);
      curr = waynext;
   }

   /* after freeing all the nodes set the head to null */
   (*trackheadnodePtr) -> head = NULL;
}



/*****************************************
** Function: ChangeTracks()
** This function takes the nodes from the
** queue and pushes all the nodes onto the
** stacks for the outgoing tracks
**
** Inputs:  pointers to the track pointers
**          to the stacks and the track
**          pointer for the queue's head
**          node pointer
** Outputs: void
**
****************************************/
void ChangeTracks(TRACKPTR * queueheadnodePtr, TRACKPTR * transferheadnodePtr, TRACKPTR * track1, TRACKPTR * track2, TRACKPTR * track3, TRACKPTR * track4)
{
   /* declare place holders and flags */
   NODEPTR temp, temp2;
   int flag2 = 0;
   int id = 0;

   /* allocate the memory for the 5 stacks */
   (*transferheadnodePtr) = (TRACKPTR)malloc(sizeof(TRACK));
   (*track1) = (TRACKPTR)malloc(sizeof(TRACK));
   (*track2) = (TRACKPTR)malloc(sizeof(TRACK));
   (*track3) = (TRACKPTR)malloc(sizeof(TRACK));
   (*track4) = (TRACKPTR)malloc(sizeof(TRACK));
   if (*transferheadnodePtr == NULL)
   {
      fprintf(stderr, "Not enough memory available for transfer track.\n");
      exit(-5);
   }
   if (*track1 == NULL)
   {
      fprintf(stderr, "Not enough memory for track 1.\n");
      exit(-6);
   }
   if (*track2 == NULL)
   {
      fprintf(stderr, "Not enough memory for track 2.\n");
      exit(-7);
   }
   if (*track3 == NULL)
   {
      fprintf(stderr, "Not enough memory for track 3.\n");
      exit(-8);
   }
   if (*track4 == NULL)
   {
      fprintf(stderr, "Not enough memory for track 4.\n");
      exit(9);
   }

   /* initialize the tracks */

   InitiateTrack(track1);
   (*track1) -> trackId = 1;
   strcpy((*track1) -> destination, "Trenton");
   InitiateTrack(track2);
   (*track2) -> trackId = 2;
   strcpy((*track2) -> destination, "Charlotte");
   InitiateTrack(track3);
   (*track3) -> trackId = 3;
   strcpy((*track3) -> destination, "Baltimore");
   InitiateTrack(track4);
   (*track4) -> trackId = 4;
   strcpy((*track4) -> destination, "Other");
   InitiateTrack(transferheadnodePtr);

   /* initialize temp so while loop will run */
   temp = (*queueheadnodePtr) -> head;

   while (temp != NULL)
   {
      /* dequeue and push first car */
      Dequeue(temp, queueheadnodePtr);
      Push(temp, transferheadnodePtr);

      /* initialize the peek loop */
      flag2 = 1;

      while (temp != NULL && flag2 == 1)
      {
         flag2 = Peek(temp, queueheadnodePtr);
         if (flag2 == -1)
         {
            flag2 = -1;
         }
         else if (flag2 == 3)
         {
            if ((*queueheadnodePtr) -> head != NULL)
            {
               /* the cars have the same track id so another gets added to the transfer stack */
               temp = (*queueheadnodePtr) -> head;
               Dequeue(temp, queueheadnodePtr);
               Push(temp, transferheadnodePtr);
               flag2 = 1;
            }
            else
            {
               flag2 = -1;
            }
         }
         else
         {
            flag2 = -1;
         }
      }
      
      /* check to see if the queue has any left */
      if ((*queueheadnodePtr) -> head != NULL)
      {
         /* standard car instructions */
         BuildInstructions(transferheadnodePtr, queueheadnodePtr);
      }
      else
      {
         /* back remaining cars instruction */
         BuildFinalInstructions(transferheadnodePtr);
      }

      /* build instructions transfer stack and queue head so see seperation between cars */
      /* pop the transfer stack and push onto the appopriate track based on trackid case switch based off that */

      /* initiate pop  and push sequence of transfer track */
      temp2 = (*transferheadnodePtr) -> head;

      while (temp2 != NULL)
      {
         /* pop cars off transfer stack and push onto appropriate stack */
         temp2 = Pop(transferheadnodePtr);
         id = temp2 -> trackId;
         
         switch (id)
         {
            case 1:
               Push(temp2, track1);
               break;
            case 2:
               Push(temp2, track2);
               break;
            case 3:
               Push(temp2, track3);
               break;
            case 4:
               Push(temp2, track4);
               break;
	    default:
               fprintf(stdout, "No track available.\n");
               break;
         }
         temp2 = (*transferheadnodePtr) -> head;
      }
      temp = (*queueheadnodePtr) -> head;
   }
}

/*****************************************
** Function: Pop()
** This function pops a node from the
** specified track
**
** Inputs:  pointer to the track pointer
**          to the track from which a
**          node will be popped.
** Outputs: the pointer to the node that
**          was just popped from the
**          stack
****************************************/
NODEPTR Pop(TRACKPTR * track)
{
   /* pops the top node off the stack */
   /* would not get to this point if the stack was empty */
   NODEPTR temp;

   temp = (*track) -> head;
   (*track) -> head = temp -> next;
   temp -> next = NULL;   
   (*track) -> numCars--;

   return temp;
}

/*****************************************
** Function: Push()
** This function pushes a node onto the
** specified stack
**
** Inputs:  pointer to the track pointer
**          to the stack and the node
**          pointer for the node to be
**          pushed
** Outputs: void
**
****************************************/
void Push(NODEPTR temp, TRACKPTR * track)
{
   int oldWeight;
   float oldCost;

   /* checks if destintation stack is empty */
   if (IsEmpty(track))
   {
      /* it is empty so the values are set appropriately */
      (*track) -> head = temp;
      (*track) -> numCars++;
      (*track) -> totalWeight = temp -> data.weight;
      (*track) -> totalCost = temp -> data.cost;
   }
   else
   {
      /* it wasn't empty so it adds the new node to the top based on LIFO model */
      temp -> next = (*track) -> head;
      (*track) -> head = temp;
      (*track) -> numCars++;
      oldWeight = (*track) -> totalWeight;
      (*track) -> totalWeight = (temp -> data.weight) + oldWeight;
      oldCost = (*track) -> totalCost;
      (*track) -> totalCost = (temp -> data.cost) + oldCost;      
   }
}

/*****************************************
** Function: Peek()
** This function compares the track ids
** for the temp node and the node under it
** still in the queue
**
** Inputs:  pointer to the track pointer
**          to the queue and the node
**          pointer for the head of the
**          queue
** Outputs: an int flagging if the cars
**          have the same destination
****************************************/
int Peek(NODEPTR temp, TRACKPTR * queueheadnodePtr)
{
   int id = 0;
   int nextid = 0;
   int flag2 = 0;
   NODEPTR curr;

   /* checks the queue is empty */
   if (IsEmpty(queueheadnodePtr))
   {
      flag2 = -1;
      return flag2;
   }
   else
   {
      /* the queue isn't empty so it compares the track ids of the nodes in question */
      curr = (*queueheadnodePtr) -> head;
      nextid = curr -> trackId;
      id = temp -> trackId;

      if (id == nextid)
      {
         flag2 = 3;
         return flag2;
      }
      else
      {
         flag2 = 4;
         return flag2;
      }
   }
}
