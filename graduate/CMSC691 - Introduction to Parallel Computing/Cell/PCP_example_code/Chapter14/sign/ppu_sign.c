#include <libspe2.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

// Program handle representing the SPU object
extern spe_program_handle_t spu_sign;

int main() {
   int retval;
	spe_context_ptr_t spe;
   unsigned entry = SPE_DEFAULT_ENTRY;
  
   // Create the SPE Context
   spe = spe_context_create(SPE_ISOLATE_EMULATE, NULL);
   if (!spe) {
      perror("spe_context_create");
      exit(1);
   }
   printf("Context created.\n");
   
   // Load the program into the context
   retval = spe_program_load(spe, &spu_sign);
   if (retval) {
      perror("spe_program_load");
      exit(1);
   }
   printf("Context loaded.\n");
   
	// Run the program inside the context
   retval = spe_context_run(spe, &entry, 0, 
                        NULL, NULL, NULL);
   if (retval < 0) {
      perror("spe_context_run");
      exit(1);
   }
	printf("Context executed.\n");
   
   // Deallocate the context
   retval = spe_context_destroy(spe);
   if (retval) {
      perror("spe_context_destroy");
      exit(1);
   }
	printf("Context destroyed.\n");   
   
   return 0;
}
