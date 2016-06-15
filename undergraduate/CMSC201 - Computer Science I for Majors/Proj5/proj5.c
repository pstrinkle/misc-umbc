#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "proj5.h"

int main(int argc, char * argv[])
{
   /* create file pointers for input and output files */
   FILE * ifp;
   FILE * ofp1;
   FILE * ofp2;
   FILE * ofp3;
   FILE * ofp4; 

   /* creates pointers to track headnodes */
   TRACKPTR queueheadnodePtr, transferheadnodePtr, track1, track2, track3, track4;

   /* check commond-line arguments */
   if (argc != 2)
   {
      fprintf(stderr, "You need to enter in\n");
      fprintf(stderr, " the input data file.\n");
      exit(-1);
   }
   
   /* open and check input file */
   ifp = fopen(argv[1], "r");
   if (ifp == NULL)
   {
      fprintf(stderr, "File could not be opened.\n");
      exit(-2);
   }

   /* open output files and check them */
   ofp1 = fopen("acct1.txt", "w");
   ofp2 = fopen("acct2.txt", "w");
   ofp3 = fopen("acct3.txt", "w");
   ofp4 = fopen("acct4.txt", "w");
   if (ofp1 == NULL || ofp2 == NULL || ofp3 == NULL || ofp4 == NULL)
   {
      fprintf(stderr, "Files could not be created, check permissions.\n");
      exit(-10);
   }

   /* print greeting */
   PrintGreeting();

   /* build incoming track queue */
   BuildQueue(&queueheadnodePtr, ifp);

   /* done with input file, so it's closed */
   fclose(ifp);

   /* move all cars to their appropriate tracks */
   ChangeTracks(&queueheadnodePtr, &transferheadnodePtr, &track1, &track2, &track3, &track4);
   
   /* print the individual accounting files for the 4 tracks */
   PrintAcctFiles(&track1, ofp1);
   PrintAcctFiles(&track2, ofp2);
   PrintAcctFiles(&track3, ofp3);
   PrintAcctFiles(&track4, ofp4);

   /* close the 4 output files */
   fclose(ofp1);
   fclose(ofp2);
   fclose(ofp3);
   fclose(ofp4);

   /* free all memory associated with the incoming queue */
   DestroyQueue(&queueheadnodePtr);

   /* free all memory associated with the stacks */
   DestroyStack(&transferheadnodePtr);
   DestroyStack(&track1);
   DestroyStack(&track2);
   DestroyStack(&track3);
   DestroyStack(&track4);

   /* free all the pointers to the headnodes */
   free(queueheadnodePtr);
   free(transferheadnodePtr);
   free(track1);
   free(track2);
   free(track3);
   free(track4);

   return 0;
}


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
** Function: PrintGreeting()
** This function displays the greeting.
**
** Inputs:  void
** Outputs: void
****************************************/
void PrintGreeting(void)
{
   /* Print an on-screen greeting */
   fprintf(stdout, "\nWelcome to the Train Switching Station Control System\n");
   fprintf(stdout, "Instructions are printed out below after the incoming train has been analyzed.\n\n");
}


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

void CalcCost (CARPTR newcar)
{
   int compared;
   float temp = 0;
   float price;

   /* compares the cargo of the car and calculates the cost of transport */

   compared = strcmp(newcar -> cargo, "autos");
   if (compared == 0)
   {
      price = AUTOS;
   }

   compared = strcmp(newcar -> cargo, "coal");
   if (compared == 0)
   {
      price = COAL;
   }

   compared = strcmp(newcar -> cargo, "cattle");
   if (compared == 0)
   {
      price = CATTLE;
   }

   compared = strcmp(newcar -> cargo, "hogs");
   if (compared == 0)
   {
      price = HOGS;
   }

   compared = strcmp(newcar -> cargo, "eggs");
   if (compared == 0)
   {
      price = EGGS;
   }

   /* here it actually uses the price and weight of the car to calculate */

   temp = ( ( (float) (newcar -> weight) ) / 2000 );
   temp = temp * price * (newcar -> miles);

   newcar -> cost = temp;
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
void BuildInstructions(TRACKPTR * transferheadnodePtr, TRACKPTR * queueheadnodePtr)
{
   NODEPTR lead, end;
   int id = 0;

   /* set cars to be examined */
   lead = (*transferheadnodePtr) -> head;
   end = (*queueheadnodePtr) -> head;
   id = lead -> trackId;

   if ((*transferheadnodePtr) -> numCars > 1)
   {
      /* instructions for if the stack held multiple cars, all going to the same place */
      fprintf(stdout, "Uncouple between cars %d and %d and back them onto track %d\n", lead -> data.carNum, end -> data.carNum, id);
   }
   else
   {
      /* only one car in the transfer stack */
      fprintf(stdout, "Uncouple between cars %d and %d and back car %d onto track %d\n", lead -> data.carNum, end -> data.carNum, lead -> data.carNum, id);
   }
}

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
void BuildFinalInstructions(TRACKPTR * transferheadnodePtr)
{
   NODEPTR curr;
   int id = 0;

   /* set the car to be viewed */
   curr = (*transferheadnodePtr) -> head;

   id = curr -> trackId;

   if ((*transferheadnodePtr) -> numCars > 1)
   {
      /* if multiple cars in the transfer stack and the queue is empty. */
      fprintf(stdout, "Back remaining cars onto track %d\n", id);
   }
   else
   {
      /* only one car on the transfer stack and the queue is empty */
      fprintf(stdout, "Back remaining car %d onto track %d\n", curr -> data.carNum, id);
   }
}

void PrintData (TRACKPTR * track, FILE * ofp)
{
   NODEPTR curr, prev;

   prev = NULL;
   curr = (*track) -> head;

   while (curr != NULL)
   {
      /* this prints the data for each car */

      fprintf(ofp, "\n");
      fprintf(ofp, " Car number : %d\n", curr -> data.carNum);
      fprintf(ofp, "      Cargo : %s\n", curr -> data.cargo);
      fprintf(ofp, "     Origin : %s\n", curr -> data.origin);
      fprintf(ofp, "Destination : %s\n", curr -> data.destination);
      fprintf(ofp, "     Weight : %d pounds\n", curr -> data.weight);
      fprintf(ofp, "   Distance : %d\n", curr -> data.miles);
      fprintf(ofp, "       Cost : $ %.2lf\n", curr -> data.cost);

      prev = curr;
      curr = curr -> next;
   }
}

void PrintTotals (TRACKPTR * track, FILE * ofp)
{
   float tempwt;


   /* this uses the temporary weight and calcs the weight in tons */
   tempwt = ( (float) ((*track)-> totalWeight) ) / 2000;

   fprintf(ofp, "  Total weight : %11.2lf tons\n", tempwt);
   fprintf(ofp, "    Total bill : $%10.2lf\n", (*track) -> totalCost);
   fprintf(ofp, "\n\n");

}

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
void PrintAcctFiles(TRACKPTR * track, FILE * ofp)
{
   /* prints accounting output files based on the track */

   fprintf(ofp, "Track %d: A total of %d cars board for %s\n\n", (*track) -> trackId, (*track) -> numCars, (*track) -> destination);
   
   PrintData(track, ofp);
   PrintTotals(track, ofp);
}
