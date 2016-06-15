/****************************************************
** File: queue.h
** Author: Patrick Trinkle
** Date: 5/7/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the functions involving
** the queue ADT with the exception of IsEmpty
**
****************************************************/

#ifndef _queue_h
#define _queue_h

#include "proj5.h"

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
void BuildQueue (TRACKPTR * queueheadnodePtr, FILE * ifp);

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
void InitializeCar (CARPTR newcar);

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
NODEPTR CreateNode(void);

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
void SetData(NODEPTR * temp, CAR newcar);

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
void InsertNode(NODEPTR * temp, TRACKPTR * queueheadnodePtr);

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
void DestroyQueue(TRACKPTR * queueheadnodePtr);

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
int GetTrackId(char destination[ ]);

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
void Dequeue(NODEPTR temp, TRACKPTR * queueheadnodePtr);


#endif
