/****************************************************
** File: train.h
** Author: Patrick Trinkle
** Date: 4/5/2004
** Section: 0103
** Email : tri1@umbc.edu
**
** This file contains all the functions for proj3.c
** some modified for proj5
****************************************************/


#ifndef _train_h
#define _train_h


#include "proj5.h"


/*****************************************
** Function: GetNumCars()
** This function gets the number of cars.
**
** Inputs: a pointer to the number of cars
** Outputs: void
****************************************/
void GetNumCars (int* numCarsPtr);

/*****************************************
** Function: PrintNumCars()
** This function prints the number of cars
**
** Inputs: the number of cars
** Outputs: void
****************************************/
void PrintNumCars (int numCars);

/*******************************************
** Function: GetMemory()
** This dynamically allocates memory
**
** Inputs: the pointer for the cars and
**         the number of cars in the train
** Outputs: void
*******************************************/
void GetMemory (CAR ** train, int numCars);

/*****************************************
** Function: GetInfo()
** This gets the info for the train
**
** Inputs: the pointer for the cars and
**         the number of cars in the train
** Outputs: void
****************************************/
void GetInfo (CAR* train, int numCars);

/*****************************************
** Function: CalcCost()
** Calculates the cost per car of the
** train
**
** Inputs: the pointer for the car
** 
** Outputs: void
****************************************/
void CalcCost (CARPTR newcar);

/*****************************************
** Function: FindTotals()
** Calculates totals for the train
**
** Inputs: the pointer for the cars and
**         the number of cars in the train
**         and the cost pointer, and the
**         weight pointer
** Outputs: void
****************************************/
void FindTotals (CAR* train, int numCars, float* costPtr, int* wtPtr);

/*****************************************
** Function: PrintData()
** Prints the data for the trains
**
** Inputs:  the pointer to the track
**          pointer for the track and the
**          pointer to the output file
**          pointer
**
** Outputs: void
****************************************/
void PrintData (TRACKPTR * track, FILE * ofp);

/*****************************************
** Function: PrintBreak()
** Prints the break
**
** Inputs: void
**         
** Outputs: void
****************************************/
void PrintBreak (void);

/*****************************************
** Function: PrintTotals()
** Prints the totals
**
** Inputs:  the pointer to the track
**          pointer for the track and the
**          pointer to the output file
**          pointer
**
** Outputs: void
****************************************/
void PrintTotals (TRACKPTR * track, FILE * ofp);

/*****************************************
** Function: PrintCars()
** Prints the cars
**
** Inputs: the pointer for the cars and
**         the number of cars
**                  
** Outputs: void
****************************************/
void PrintCars (CAR * train, int numCars);

#endif
