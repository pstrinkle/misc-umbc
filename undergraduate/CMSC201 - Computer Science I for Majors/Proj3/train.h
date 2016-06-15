
#define AUTOS   .165
#define COAL    .291
#define CATTLE  .525
#define HOGS    .631
#define EGGS    .759
#define LENGTH  12
#define ROWSPAN 5

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


/*****************************************
** Function: PrintGreeting()
** This function displays the greeting.
**
** Inputs: void
** Outputs: void
****************************************/
void PrintGreeting (void);

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
** Inputs: the pointer for the cars and
**         the number of cars in the train
** Outputs: void
****************************************/
void CalcCost (CAR* train, int numCars);

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
** Inputs: the pointer for the cars, and
**         the number of cars
**         
** Outputs: void
****************************************/
void PrintData (CAR* train, int numCars);

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
** Inputs: the number of cars the coat
**         and the weight
**         
** Outputs: void
****************************************/
void PrintTotals (int numCars, float cost, int wt);

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

