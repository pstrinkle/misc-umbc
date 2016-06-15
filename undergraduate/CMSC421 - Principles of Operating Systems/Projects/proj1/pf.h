/*****************************************
 ** File: pf.h
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
#include <math.h>

#include <pthread.h>
#include <unistd.h>

/*special data types */
typedef struct node * NODEPTR;

typedef struct node
{
      int     prime;
      NODEPTR next;
}NODE;

typedef struct fnode * FNODEPTR;

typedef struct fnode
{
      int prime;
      int power;
      FNODEPTR next;
}FNODE;

/* shared data */
int numbersperSubset;
int numbersperFactorset;
int N;
int numPrimes;
NODEPTR primeslead;
NODEPTR primesback;
FNODEPTR factorlead;
FNODEPTR factorback;

/* declare locking mechanism */
/*
  I decided not to use the macro
  pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
*/

pthread_mutex_t m;

/* CreateNode()
** Initializes the node
*/

NODEPTR CreateNode(void)
{
   NODEPTR temp;

   temp = (NODEPTR)malloc(sizeof(NODE));
   if (temp == NULL)
   {
      fprintf(stderr, "Not enough memory.\n");
      exit(-4);
   }

   temp -> prime = 0;
   temp -> next = NULL;

   return temp;
}

/* CreateFNode()
** Initializes the node
*/

FNODEPTR CreateFNode(void)
{
   FNODEPTR temp;

   temp = (FNODEPTR)malloc(sizeof(FNODE));
   if (temp == NULL)
   {
      fprintf(stderr, "Not enough memory.\n");
      exit(-5);
   }

   temp -> prime = 0;
   temp -> power = 0;
   temp -> next = NULL;

   return temp;
}

/* printFNodes()
** Prints the Factors
*/

void printFNodes(FNODEPTR head)
{
   printf("%d^%d = ", head -> prime, head -> power);

   FNODEPTR printing = head -> next;
   while(printing != NULL)
   {
      if (printing -> next != NULL)
      {
	 printf("%d^%d * ", printing -> prime, printing -> power);
      }
      else
      {
	 printf("%d^%d", printing -> prime, printing -> power);
      }
      printing = printing -> next;
   }
   printf("\n");
}


/* isPrime()
** Runner program for the thread, finds
** primes in the range.
*/

void * isPrime(void * param)
{
   /* params */
   int begin, end;

   /* looping */
   int i, j;

   /* fake bool */
   int isPrime = 0;

   /* temp var */
   NODEPTR other = NULL;

   /* set begin & end */
   begin = *(int*)param;
   end = begin + numbersperSubset - 1;

   if (end > N)
   {
      end = N;
   }

   for (j = begin; j <= end; ++j)
   {      
      /* initial test */
      if ((j % 1) == 0 && (j % j) == 0)
	 isPrime = 1;

      /* case 1 out */
      if (j == 1)
	 isPrime = 0;

      /* secondary test 
        won't be able to run through this
      */
      for (i = 1; i <= j; ++i)
      {
	 if ((i != j) && (j % i) == 0 && i != 1)
	    isPrime = 0;
      }

      /* action */
      /* critical section */
      if (isPrime == 1)
      {
	 NODEPTR temp = CreateNode();
	 temp -> prime = j;
	 /* if first node */
	 
	 pthread_mutex_lock(&m);
	 numPrimes++;

	 if (j == 2) /* first possible */
	    primeslead -> next = temp;
	 else
	 {
	    other = primesback -> next;
	    other -> next = temp;
	 }

	 /* repoint back */
	 primesback -> next = temp;

	 pthread_mutex_unlock(&m);
      }
      /* end critical section */
   }
   pthread_exit(0);
}

/* isFactor()
** Sorts out which primes are factors
*/

void * isFactor(void * param)
{
   /* params */
   int begin = 0;
   int end = 0;
   
   /* looping */
   int i = 0;

   /* set begin & end */
   begin = *(int*)param;
   end = begin + numbersperFactorset - 1;

   if (end > numPrimes)
   {
      end = numPrimes;
   }

   /* get into position with linked list */
   NODEPTR current = primeslead;
   for (i = 0; i < begin; ++i)
      current = current -> next;

   /* begin going through it */
   FNODEPTR other = NULL;
   i = 0;
   i = begin;
   int route = 1;
   int count = 0;
   int divisor = 0;
   
   while (current != NULL && i <= end)
   {
      if (N % (current -> prime) == 0)
      {
	 /* it is a factor */
	 /* add the prime */
	 FNODEPTR temp = CreateFNode();
	 temp -> prime = current -> prime;
	 divisor = temp -> prime;

	 count = 0;
	 route = 1;
	 /* by home much is it a factor? */
	 while(route)
	 {
	    if (N % divisor == 0)
	    {
	       count++;
	       divisor = pow(temp -> prime, count);
	    }
	    else
	    {
	       count--;
	       route = 0;
	    }
	 }
	
	 temp -> power = count;
	 
	 /* if first node */
	 /* critical section */
	 pthread_mutex_lock(&m);
	 if (factorlead -> next == NULL)
	    factorlead -> next = temp;
	 else
	 {
	    other = factorback -> next;
	    other -> next = temp;
	 }

	 /* repoint back */
	 factorback -> next = temp;
	 pthread_mutex_unlock(&m);
	 /* critical section */
      }
      current = current -> next;
      i++;
   }

   pthread_exit(0);
}

/* runHelp()
** Prints help message
*/

void runHelp()
{
   fprintf(stderr, "N is the number to be factored. >1\n");
   fprintf(stderr, "P is the number of threads to be used to find primes. >1\n");
   fprintf(stderr, "Q is the number of threads to be used to find factorizations of primes. >1\n");
}

/* freeNode()
** Frees node and all linked
*/

void freeNode(NODEPTR head)
{
   NODEPTR prev = NULL;
   NODEPTR curr = head -> next;
   while(curr != NULL)
   {
      prev = curr;
      curr = curr -> next;
      free(prev);
   }
   free(head);
}

/* freeFNode()
** Frees node and all linked
*/

void freeFNode(FNODEPTR head)
{
   FNODEPTR fprev = NULL;
   FNODEPTR fcurr = head -> next;
   while(fcurr != NULL)
   {
      fprev = fcurr;
      fcurr = fcurr -> next;
      free(fprev);
   }
   free(head);
}
