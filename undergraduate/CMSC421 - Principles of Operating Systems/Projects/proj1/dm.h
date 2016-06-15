/*****************************************
 ** File: dm.h
 ** Author: Patrick Trinkle
 ** Date: March 1, 2006
 ** E-Mail: tri1@umbc.edu
 **
 ** This file contains all libraries required
 ** by dm.c to compile and run properly, as
 ** well as all global variables.
 *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>

int numDonuts;
int numShelves;

int * shelves;
int * producer;
int * consumer;

/* locks */
int baker;
int student;
