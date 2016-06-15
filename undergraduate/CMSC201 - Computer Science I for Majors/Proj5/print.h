/****************************************************
** File: print.h
** Author: Patrick Trinkle
** Date: 5/7/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the printing functions for
** proj5
****************************************************/

#ifndef _print_h
#define _print_h

#include "proj5.h"

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
void BuildInstructions(TRACKPTR * transferheadnodePtr, TRACKPTR * queueheadnodePtr);

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
void BuildFinalInstructions(TRACKPTR * transferheadnodePtr);

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
void PrintAcctFiles(TRACKPTR * track, FILE * ofp);

/*****************************************
** Function: PrintGreeting()
** This function displays the greeting.
**
** Inputs:  void
** Outputs: void
****************************************/
void PrintGreeting(void);

#endif
