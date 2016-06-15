
#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <ppu_intrinsics.h>

#include "pu_threads.h"

/* SPU program handle */
extern spe_program_handle_t spu_single;
transpose_package_t packages[8] __attribute__ ((aligned(16)));

float srcbuf[N][N] __attribute__ ((aligned(128)));
float destbuf[N][N] __attribute__ ((aligned(128)));

int main(int argc, char **argv)
{
   int i, j, retval, test;
   unsigned long long startTime, stopTime;
   spe_context_ptr_t speid;
   void *argp;

   /* initialize whole thing to 1.1 */
   for (i = 0; i < N; ++i)
      for (j = 0; j < N; ++j)
	 srcbuf[i][j] = i + j + 0.1;

   /* set first row of first block to sig */
   for (i = 0; i < N; ++i)
      srcbuf[0][i] = i + 0.1;

   speid = spe_context_create(0, NULL);
   if (!speid)
   {
      perror("spe_context_create");
      exit(1);
   }
   
   /* Load program into the context */
   if ((retval =
	spe_program_load(speid, &spu_single)) != 0)
   {
      perror("spe_program_load");
      exit (1);
   }
   
   packages[0].srcbuf = (unsigned long long)&(srcbuf[0][0]);
   packages[0].destbuf = (unsigned long long)&(destbuf[0][0]);
   packages[0].id = i;
   
   /* Initialize control block and thread data */
   argp = (void*)&(packages[0]);
   
   unsigned int entry = SPE_DEFAULT_ENTRY;

   startTime = __mftb();
   if ((retval =
        spe_context_run(speid, &entry, 0, argp, NULL, NULL)) < 0)
   {
      perror("spe_context_run");
      exit (1);
   }
   stopTime = __mftb();

   // divide by 14318000.0

   printf("Time Calculating: %fs\n", (stopTime - startTime) / (double)14318000.0);

   if ((retval = spe_context_destroy (speid)) != 0)
   {
      perror("spe_context_destroy");
      exit (1);
   }

   test = 1;

   for (i = 0; i < N; ++i)
   {
      for (j = 0; j < N; ++j)
      {
	 if (srcbuf[i][j] != destbuf[j][i])
	 {
	    printf("Failed at [%d][%d]\n", i, j);
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
