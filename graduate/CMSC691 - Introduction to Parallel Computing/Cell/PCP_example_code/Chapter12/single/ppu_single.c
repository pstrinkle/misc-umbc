#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <ppu_intrinsics.h>

#define SIZE 4096*8

/* Program handle representing the SPU object */
extern spe_program_handle_t spu_single;

int main() {
   int i, retval;
	spe_context_ptr_t spe;
   unsigned entry = SPE_DEFAULT_ENTRY;
   spe_stop_info_t stop_info;
	
	/* The array to be DMAed into the SPU's LS */
   unsigned int ch_array[SIZE] __attribute__ ((aligned (128)));
	
	/* Fill the array with ASCII values */
   for(i=0; i<SIZE; i++)
	   ch_array[i] = i;
  
   /* Create the SPE Context */
   spe = spe_context_create(0, NULL);
   if (!spe) {
      perror("spe_context_create");
      exit(1);
   }
   
   /* Load the program into the context */
   retval = spe_program_load(spe, &spu_single);
   if (retval) {
      perror("spe_program_load");
      exit(1);
   }

	/* Run the program inside the context */
   retval = spe_context_run(spe, &entry, 0, 
                        ch_array, NULL, &stop_info);
   if (retval < 0) {
      perror("spe_context_run");
      exit(1);
   }
	
   /* Deallocate the context */
   retval = spe_context_destroy(spe);
   if (retval) {
      perror("spe_context_destroy");
      exit(1);
   }
	
   int test = 1;
   for(i=0; i<SIZE; i++) {
      if(ch_array[i] != i+1) {
         test = 0;
         break;
      }
   }
   if(test)
	   printf("DMA Passed.\n");
   else
	   printf("DMA Failed.\n");
   return 0;
}
