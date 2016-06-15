/****************************************************
** File: stack.h
** Author: Patrick Trinkle
** Date: 5/7/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the functions involving
** the stack ADT with the exception of IsEmpty
**
****************************************************/

#ifndef _stack_h
#define _stack_h

#include "proj5.h"

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
void DestroyStack(TRACKPTR * trackheadnodePtr);

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
void ChangeTracks(TRACKPTR * queueheadnodePtr, TRACKPTR * transferheadnodePtr, TRACKPTR * track1, TRACKPTR * track2, TRACKPTR * track3, TRACKPTR * track4);

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
void Push(NODEPTR temp, TRACKPTR * track);

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
int Peek(NODEPTR temp, TRACKPTR * queueheadnodePtr);

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
NODEPTR Pop(TRACKPTR * track);




#endif
