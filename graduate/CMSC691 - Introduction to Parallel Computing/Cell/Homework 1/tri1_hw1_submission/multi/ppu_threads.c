
#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <pthread.h>
#include <ppu_intrinsics.h>

#include "pu_threads.h"

/* The data sent to the pthread */
typedef struct ppu_pthread_data
{
    spe_context_ptr_t speid;
    pthread_t         pthread;
    void             *argp;
} ppu_pthread_data_t;

/* The function executed in the pthread */
void*
ppu_pthread_function(
   void *arg)
{
   ppu_pthread_data_t *data = (ppu_pthread_data_t *)arg;
   int retval;
   unsigned int entry = SPE_DEFAULT_ENTRY;

   if ((retval = 
	spe_context_run(data->speid, &entry, 0, data->argp, NULL, NULL)) < 0)
   {
      perror("spe_context_run");
      exit (1);
   }

   pthread_exit(NULL);
}


/* SPU program handle */
extern spe_program_handle_t spu_threads;  
ppu_pthread_data_t data[8] ;
transpose_package_t packages[8] __attribute__ ((aligned(16)));

float srcbuf[N][N] __attribute__ ((aligned(128)));
float destbuf[N][N] __attribute__ ((aligned(128)));

int main(int argc, char **argv)
{
   int i, j, retval, spus, test;
   unsigned long long startTime, stopTime;

   /* initialize whole thing to 1.1 */
   for (i = 0; i < N; ++i)
      for (j = 0; j < N; ++j)
	 srcbuf[i][j] = i + j + 0.1;

   /* set first row of first block to sig */
   for (i = 0; i < N; ++i)
      srcbuf[0][i] = i + 0.1;

   /* Determine number of available SPUs */
   spus = spe_cpu_info_get(SPE_COUNT_USABLE_SPES, 0);
   
   if (spus < THREADCNT)
   {
      perror("Requested more threads than SPUs");
      exit (1);
   }

   /* DEBUG */
   spus = THREADCNT;

   startTime = __mftb();
   /* Create a context and thread for each SPU */
   for (i = 0; i < spus; i++)
   {
      /* Create context */
      if ((data[i].speid = spe_context_create(0, NULL)) == NULL)
      {
         perror("spe_context_create");
         exit(1);
      }
      
      /* Load program into the context */
      if ((retval =
	   spe_program_load(data[i].speid, &spu_threads)) != 0)
      {
         perror("spe_program_load");
         exit (1);
      }

      packages[i].srcbuf = (unsigned long long)&(srcbuf[0][0]);
      packages[i].destbuf = (unsigned long long)&(destbuf[0][0]);
      packages[i].id = i;

      /* Initialize control block and thread data */
      data[i].argp = (void*)&(packages[i]);
      
      /* Create thread */
      if ((retval = 
	   pthread_create(
              &data[i].pthread,
              NULL,
              &ppu_pthread_function,
              &data[i])) != 0)
      {
         perror("pthread_create");
         exit (1);
      }
   }
   
   /* Wait for the threads to finish processing */
   for (i = 0; i < spus; i++)
   {
      if ((retval = pthread_join(data[i].pthread, NULL)) != 0)
      {
	 perror("pthread_join");
	 exit (1);
      }
      
      if ((retval = spe_context_destroy (data[i].speid)) != 0)
      {
	 perror("spe_context_destroy");
	 exit (1);
      }
   }
   stopTime = __mftb();

   printf("Time Calculating: %fs\n", (stopTime - startTime) / (double)14318000.0);

   test = 1;

   for (i = 0; i < N; ++i)
   {      
      for (j = 0; j < N; ++j)
      {
	 if (srcbuf[i][j] != destbuf[j][i])
	 {
	    printf("Broken at srcbuf[%d][%d]: %f\n", i, j, srcbuf[i][j]);
	    printf("destbuf[%d][%d]: %f\n", j, i, destbuf[j][i]);
	    test = 0;
	    break;
	 }
      }
      
      if (!test)
	 break;
   }

   if (test)
      printf("DMA Passed\n");
   else
      printf("DMA Failed\n");

   return 0;
}
