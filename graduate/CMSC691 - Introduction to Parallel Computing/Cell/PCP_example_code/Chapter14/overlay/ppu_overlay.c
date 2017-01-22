#include <stdio.h>
#include <libspe2.h>
#include <ppu_intrinsics.h>

/* Program handle representing the SPU object */
extern spe_program_handle_t spu_overlay;

int main() {
   int i, retval;
	spe_context_ptr_t spe;
   unsigned entry = SPE_DEFAULT_ENTRY;
  
   /* Create the SPE Context */
   spe = spe_context_create(0, NULL);
   if (!spe) {
      perror("spe_context_create");
      exit(1);
   }
   
   /* Load the program into the context */
   retval = spe_program_load(spe, &spu_overlay);
   if (retval) {
      perror("spe_program_load");
      exit(1);
   }

	/* Run the program inside the context */
   retval = spe_context_run(spe, &entry, 0, 
                        NULL, NULL, NULL);
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
}
