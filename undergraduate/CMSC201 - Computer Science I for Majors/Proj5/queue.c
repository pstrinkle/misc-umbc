/****************************************************
** File: queue.c
** Author: Patrick Trinkle
** Date: 5/7/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the functions involving 
** the queue ADT with the exception of IsEmpty
**
****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "train.h"
#include "other.h"

/*****************************************
** Function: BuildQueue()
** This function initializes the temp
** car to be used for the information
**
** Inputs:  a pointer to the file pointer
**          for the input file and the
**          pointer to track pointer for
**          the incoming track queue
**
** Outputs: void
**
****************************************/
void BuildQueue(TRACKPTR * queueheadnodePtr, FILE * ifp)
{
   /* declare variables to be used repeatedly within function */
   CAR newcar;
   NODEPTR temp;

   /* allocate memory for the incoming track queue */
   (*queueheadnodePtr) = (TRACKPTR)malloc(sizeof(TRACK));
   if (*queueheadnodePtr == NULL)
   {
      fprintf(stderr, "Not enough memory free.\n");
      exit(-3);
   }

   /* initialize the head node for the incoming track queue */
   InitiateTrack(queueheadnodePtr);

   /* initilize the car struct to be used within the while loop for building the queue */
   InitializeCar(&newcar);

   /* read through the data file and build the queue */
   while(fscanf(ifp, "%d %s %s %s %d %d", &newcar.carNum, newcar.cargo, newcar.origin, newcar.destination, &newcar.weight, &newcar.miles) != -1)
   {
      /* calculates the cost of moving the specific car */
      CalcCost(&newcar);

      /* finds memory for the new node and stores in temp */
      temp = CreateNode();

      /* sets data from newcar struct into the new node */
      SetData(&temp, newcar);

      /* get the track id for the specific node */
      temp -> trackId = GetTrackId(temp -> data.destination); 

      /* insert the node into the queue */
      InsertNode(&temp, queueheadnodePtr);
   }
}

/*****************************************
** Function: InitializeCar()
** This function initializes the temp
** car to be used for the information
**
** Inputs:  a car pointer to the new car
**
** Outputs: void
**
****************************************/
void InitializeCar(CARPTR newcar)
{
   /* initialize all the values of car to be blank--remove garbage */
   (*newcar).carNum = 0;
   strcpy((*newcar).cargo, "");
   strcpy((*newcar).origin, "");
   strcpy((*newcar).destination, "");
   (*newcar).weight = 0;
   (*newcar).miles = 0;
   (*newcar).cost = 0.00;
}

/*****************************************
** Function: CreateNode()
** This function creates the space for a
** node and returns the pointer to the
** location for the node
**
** Inputs:  void
**
** Outputs: a node pointer with the
**          location of a new node
**
****************************************/
NODEPTR CreateNode(void)
{
   /* declare temp node pointer */
   NODEPTR temp;

   /* get memory and store in temp */
   temp = (NODEPTR)malloc(sizeof(NODE));
   if (temp == NULL)
   {
      fprintf(stderr, "Not enough memory.\n");
      exit(-4);
   }

   /* remove the garbage from that node's memory */
   temp -> data.carNum = 0;
   strcpy(temp -> data.cargo, "");
   strcpy(temp -> data.origin, "");
   strcpy(temp -> data.destination, "");
   temp -> data.weight = 0;
   temp -> data.miles = 0;
   temp -> data.cost = 0;
   temp -> next = NULL;
   temp -> trackId = 0;

   /* return the location in the memory so the node can be used */
   return temp;
}

/*****************************************
** Function: SetData()
** This function sets the data from the
** car into the specific node
**
** Inputs:  the pointer to the node and
**          the structure with the car
**          data
** Outputs: void
**
****************************************/
void SetData(NODEPTR * temp, CAR newcar)
{
   /* set the data from the struct car into the new node */
   (*temp) -> data = newcar;
   (*temp) -> next = NULL;
}

/*****************************************
** Function: InsertNode()
** This function gets the location of
** target node and dequeues it from the
** incoming track
**
** Inputs:  the pointer to the node and
**          the pointer to the track
**          pointer for the queue head
**          node
** Outputs: void
**
****************************************/
void InsertNode(NODEPTR * temp, TRACKPTR * queueheadnodePtr)
{
   /* declare a variable to hold a location in the queue */
   NODEPTR end;

   /* check if the head is empty */
   if (IsEmpty(queueheadnodePtr))
   {     
      /* it was empty so the values are set appropriately */
      (*queueheadnodePtr) -> head = (*temp);
      (*queueheadnodePtr) -> tail = (*temp);
      (*queueheadnodePtr) -> numCars = 1;
   }
   else
   {
      /* wasn't empty, find the last node and set to place holder */
      end = (*queueheadnodePtr) -> tail;
      
      /* add queue to end */
      end -> next = (*temp);
    
      /* change where the tail of the queue points */
      (*queueheadnodePtr) -> tail = (*temp);
      
      /* add to the car counter */
      (*queueheadnodePtr) -> numCars++;

      /* make sure temp's next is still set to null */
      (*temp) -> next = NULL;
   }  
}

/*****************************************
** Function: DestroyQueue()
** This function fress the memory in the
** queue and sets all pointers to NULL
**
** Inputs:  a pointer to a trackpointer
**          to the queue's head node
** Outputs: void
**
****************************************/
void DestroyQueue(TRACKPTR * queueheadnodePtr)
{
   /* set up place holder nodes */
   NODEPTR prev, curr, waynext;

   prev = NULL;

   /* make curr the starting point */
   curr = (*queueheadnodePtr) -> head;
   
   /* set the tail pointer to null */
   (*queueheadnodePtr) -> tail = NULL;
   
   while (curr != NULL)
   {
      /* set pointers to null and free memory one car at a time */
      prev = curr;
      waynext = curr -> next;
      curr -> next = NULL;
      free(curr);
      curr = waynext;
   }
   
   /* after going through the queue set the queue's head to null */
   (*queueheadnodePtr) -> head = NULL;
}

/*****************************************
** Function: GetTrackId()
** This function gets the track id based
** on the destination of the car
**
** Inputs:  the string with the node's
**          destination
** Outputs: an int with a track id
**
****************************************/
int GetTrackId(char destination[LENGTH])
{
   int trackId, compared;

   /* compare the destinations and determine and return the track id */

   compared = strcmp(destination, "Trenton");
   if (compared == 0)
   {
      trackId = 1;
      return trackId;
   }
   
   compared = strcmp(destination, "Charlotte");
   if (compared == 0)
   {
      trackId = 2;
      return trackId;
   }
   
   compared = strcmp(destination, "Baltimore");
   if (compared == 0)
   {
      trackId = 3;
      return trackId;
   }

   trackId = 4;
   return trackId;
}

/*****************************************
** Function: Dequeue()
** This function gets the location of
** target node and dequeues it from the
** incoming track
**
** Inputs:  the pointer to the node and
**          the pointer to the track
**          pointer for the queue head
**          node
** Outputs: void
**
****************************************/
void Dequeue(NODEPTR temp, TRACKPTR * queueheadnodePtr)
{ 
   /* wouldn't get to this point if the queue was emtpy */
   /* so it just removes the top node */

   (*queueheadnodePtr) -> head = temp -> next;
   (*queueheadnodePtr) -> numCars--;
   temp -> next = NULL;
}

