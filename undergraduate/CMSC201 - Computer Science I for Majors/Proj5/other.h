/****************************************************
** File: other.h
** Author: Patrick Trinkle
** Date: 5/7/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the odd functions for
** proj5
****************************************************/

#ifndef _other_h
#define _other_h

#include "proj5.h"

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
int IsEmpty(TRACKPTR * track);

/*****************************************
** Function: InitiateTrack()
** This function initializes the head
** nodes for the different tracks
**
** Inputs:  pointer to the track pointer
**          to the track to be created.
** Outputs: void
****************************************/
void InitiateTrack(TRACKPTR * track);

#endif
