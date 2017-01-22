#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <ppu_intrinsics.h>

/* Program handle representing the SPU object */
extern spe_program_handle_t spu_dmabasic;

int main() {
   int i, retval;
	spe_context_ptr_t spe;
   unsigned entry = SPE_DEFAULT_ENTRY;
   spe_stop_info_t stop_info;
	
	/* The array to be DMAed into the SPU's LS */
   char ch_array[128] __attribute__ ((aligned (128)));
	
	/* Fill the array with ASCII values */
   for(i=0; i<128; i++)
	   ch_array[i] = i;
  
   /* Create the SPE Context */
   spe = spe_context_create(0, NULL);
   if (!spe) {
      perror("spe_context_create");
      exit(1);
   }
   
   /* Load the program into the context */
   retval = spe_program_load(spe, &spu_dmabasic);
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
   return 0;
}
