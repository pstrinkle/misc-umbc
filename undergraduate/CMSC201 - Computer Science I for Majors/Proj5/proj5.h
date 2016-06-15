#ifndef _proj5_h
#define _proj5_h


#define AUTOS  .165
#define COAL   .291
#define CATTLE .525
#define HOGS   .631
#define EGGS   .759
#define LENGTH 12

typedef struct trackinfo * TRACKPTR;
typedef struct car * CARPTR;
typedef struct node * NODEPTR;

typedef struct car
{
   int   carNum;
   char  cargo[LENGTH];
   char  origin[LENGTH];
   char  destination[LENGTH];
   int   weight;
   int   miles;
   float cost;
}CAR;

typedef struct node
{
   CAR     data;
   int     trackId;
   NODEPTR next;
}NODE;

typedef struct trackinfo
{
   int     numCars;
   int     trackId;
   char    destination[LENGTH];
   int     totalWeight;
   float   totalCost;
   NODEPTR head;
   NODEPTR tail;
}TRACK;


/* queue related */
/* ------------------------------------------------ */

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

/* proj3 with mods */
void CalcCost(CARPTR newcar);

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


/* free memory */
/* ------------------------------------------------ */

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


/* stack related */
/* ------------------------------------------------ */

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


/* printing */
/* ---------------------------------------------------------- */

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

/* from proj3 with mods */
void PrintData(TRACKPTR * track, FILE * ofp);

/* from proj3 with mods */
void PrintTotals(TRACKPTR * track, FILE * ofp);

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
