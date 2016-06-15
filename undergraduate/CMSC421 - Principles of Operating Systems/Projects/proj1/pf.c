/*****************************************
 ** File: pf.c
 ** Author: Patrick Trinkle
 ** Date: March 1, 2006
 ** E-Mail: tri1@umbc.edu
 **
 ** This program calculates the prime
 ** factorization of some integer N, using 
 ** P(int) threads to calculate primes between
 ** 1 and N, and Q(int) threads to calculate
 ** of those primes, which are factors of N
 *****************************************/

/* 
** Note: using N, not sqrt of N 
*/

#include "pf.h"

int main(int argc, char * argv[])
{

   /* set up global linked list */
   primeslead = CreateNode();
   primesback = CreateNode();
   primesback -> next = primeslead -> next;
   factorlead = CreateFNode();
   factorback = CreateFNode();
   factorback -> next = factorlead -> next;

   /* check commond-line arguments */
   if (argc != 7 && argc != 2)
   {
      fprintf(stderr, "Thanks for using the factorization by primes program.\n");
      fprintf(stderr, "Created by Patrick Trinkle.\n");
      fprintf(stderr, "Proper usage: -n N -p P -q Q\n");
      fprintf(stderr, "For help, -h\n");
      exit(-1);
   }
   
   int P = 0;
   int Q = 0;
   N = 0;
   numPrimes = 0;
   
   /* initiate the mutex */
   pthread_mutex_init(&m, NULL);

   int i;
   /* i = 0 is program file */
   for (i = 1; i < argc; i++)
   {
      if (strcmp(argv[i], "-n") == 0)
      {
	 N = atoi(argv[i+1]);
	 i++;
      }
      else if (strcmp(argv[i], "-p") == 0)
      {
	 P = atoi(argv[i+1]);
	 i++;
      }
      else if (strcmp(argv[i], "-q") == 0)
      {
	 Q = atoi(argv[i+1]);
	 i++;
      }
      else
      {
	 runHelp();
	 exit(-2);
      }
   }
   
   if (N < 1 || P < 0 || Q < 0)
   {
      fprintf(stderr, "Input values must be larger than 1(N) or 0(P & Q).\n");
      exit(-3);
   }

   /* generate subsets 
      P = number of subsets
      numbers per subset = number / # subsets
   */
   numbersperSubset = 0;   
   numbersperSubset = ceil((double)N / P);
 
   /* set passing started, will increment appropriately in for loop later */
   int begin = 0;

   /* Create Thread */
   pthread_t tid[P];
   pthread_attr_t attr;
   pthread_attr_init (&attr);

   int pthreadloop = 0;
   
   for (pthreadloop = 0; pthreadloop < P; pthreadloop++)
   {
      if (pthreadloop == 0)
      {
	 begin = 1;
      }
      else
      {
	 begin += (numbersperSubset);
      }
      pthread_create(&tid[pthreadloop], &attr, &isPrime, &begin);
   }

   for (pthreadloop = 0; pthreadloop < P; pthreadloop++)
   {
      pthread_join(tid[pthreadloop], NULL);
   }

   /* begin factorization thing */
   /* get number of primes */
   begin = 0;

   numbersperFactorset = ceil((double)numPrimes / Q);

   pthread_t otid[Q];
   pthreadloop = 0;

   for (pthreadloop = 0; pthreadloop < Q; pthreadloop++)
   {
      if (pthreadloop == 0)
      {
	 begin = 1;
      }
      else
      {
	 begin += numbersperFactorset;
      }
      pthread_create(&otid[pthreadloop], &attr, &isFactor, &begin);
   }

   for (pthreadloop = 0; pthreadloop < Q; pthreadloop++)
   {
      pthread_join(otid[pthreadloop], NULL);
   }

   /* print all this crap out */
   factorlead -> prime = N;
   factorlead -> power = 1;
   printFNodes(factorlead);

   /* free all this beautiful dynamic memory */
   freeNode(primeslead);
   free(primesback);
   freeFNode(factorlead);
   free(factorback);
   /* both linked lists and their headers/tails are freed */

   /* destroy mutex */
   pthread_mutex_destroy(&m);
   
   return 0;
}
