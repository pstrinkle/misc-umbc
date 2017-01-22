#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <ppu_intrinsics.h>
#include <pthread.h>

/* The data sent to the pthread */
typedef struct ppu_pthread_data {
    spe_context_ptr_t speid;
    pthread_t pthread;
} ppu_pthread_data_t;

/* The function executed in the pthread */
void *ppu_pthread_function(void *arg) {
   ppu_pthread_data_t *data = (ppu_pthread_data_t *)arg;
   int retval;
   unsigned int entry = SPE_DEFAULT_ENTRY;
   if ((retval = spe_context_run(data->speid, 
      &entry, 0, NULL, NULL, NULL)) < 0) {
      perror("spe_context_run");
      exit (1);
   }
   pthread_exit(NULL);
}

/* Program handle representing the SPU object */
extern spe_program_handle_t spu_signal_or;
ppu_pthread_data_t data;

int main() {
   int retval;
	spe_context_ptr_t spe;
   
   /* Create the SPE Context */
   spe = spe_context_create(SPE_CFG_SIGNOTIFY1_OR, 0);
   if (!spe) {
      perror("spe_context_create");
      exit(1);
   }
   
   /* Load the program into the context */
   retval = spe_program_load(spe, &spu_signal_or);
   if (retval) {
      perror("spe_program_load");
      exit(1);
   }

   /* Create thread */
   data.speid = spe;
   if ((retval = pthread_create(&data.pthread, 
         NULL, &ppu_pthread_function, &data)) != 0) {
      perror("pthread_create");
      exit (1);
   }
   
   /* Send three signals to the SPU */
   spe_signal_write(spe, SPE_SIG_NOTIFY_REG_1, 0x1);
   spe_signal_write(spe, SPE_SIG_NOTIFY_REG_1, 0x2);
   spe_signal_write(spe, SPE_SIG_NOTIFY_REG_1, 0x4);
   
   /* Tell the SPU to check for the signals */
   spe_signal_write(spe, SPE_SIG_NOTIFY_REG_2, 0x0);
   
   /* Wait for the thread to finish */
   if ((retval = pthread_join
        (data.pthread, NULL)) != 0) {
      perror("pthread_join");
      exit (1);
   }   
   
   /* Deallocate the context */
   retval = spe_context_destroy(spe);
   if (retval) {
      perror("spe_context_destroy");
      exit(1);
   }
   return 0;
}
