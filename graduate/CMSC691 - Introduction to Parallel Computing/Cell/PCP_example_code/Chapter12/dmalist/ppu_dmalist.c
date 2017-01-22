#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <ppu_intrinsics.h>

#define SIZE 4096

/* Program handle representing the SPU object */
extern spe_program_handle_t spu_dmalist;

int main() {
   int i, retval;
	spe_context_ptr_t spe;
   unsigned entry = SPE_DEFAULT_ENTRY;
   spe_stop_info_t stop_info;
	
	/* Array to be transfered into the SPU's LS */
   unsigned int large_array[SIZE*4] __attribute__ ((aligned (128)));
   
   /* Arrays to hold data transferred out of the LS */
   unsigned int small_1[SIZE] __attribute__ ((aligned (128)));
   unsigned int small_2[SIZE] __attribute__ ((aligned (128)));
   unsigned int small_3[SIZE] __attribute__ ((aligned (128)));
   unsigned int small_4[SIZE] __attribute__ ((aligned (128)));
	
	/* Fill the array with whole numbers */
   for(i=0; i<SIZE*4; i++)
	   large_array[i] = i;
   
   /* Initialize the array of array addresses */
   unsigned long long control_block[6];
   control_block[0] = (unsigned long long)large_array;
   control_block[1] = (unsigned long long)small_1;
   control_block[2] = (unsigned long long)small_2;
   control_block[3] = (unsigned long long)small_3;
   control_block[4] = (unsigned long long)small_4;
   control_block[5] = (unsigned long long)NULL;
   
   /* Create the SPE Context */
   spe = spe_context_create(0, NULL);
   if (!spe) {
      perror("spe_context_create");
      exit(1);
   }
   
   /* Load the program into the context */
   retval = spe_program_load(spe, &spu_dmalist);
   if (retval) {
      perror("spe_program_load");
      exit(1);
   }

	/* Run the program inside the context */
   retval = spe_context_run(spe, &entry, SPE_RUN_USER_REGS, 
               control_block, NULL, &stop_info);
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

   /* Check that the received data is valid */
	int test = 1;
	for(i=0; i<SIZE; i++) {
	   if(small_1[i] != i)
		   test = 0;
      if(small_2[i] != SIZE+i)
		   test = 0;
	   if(small_3[i] != 2*SIZE+i)
		   test = 0;     
	   if(small_4[i] != 3*SIZE+i)
		   test = 0;         
   }
   if(test)
	   printf("DMA Passed.\n");
   else
	   printf("DMA Failed.\n");
   return 0;
}
