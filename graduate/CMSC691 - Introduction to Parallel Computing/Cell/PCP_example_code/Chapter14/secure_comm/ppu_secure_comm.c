#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
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
extern spe_program_handle_t spu_secure_comm;
ppu_pthread_data_t data;

int main() {
   int retval;
	spe_context_ptr_t spe;
   
   /* Create a vector to hold received data */
   vector unsigned int message = {1, 2, 3, 4}; 
   unsigned int addr_halves[2];
   
   /* Create the SPE Context */
   spe = spe_context_create(SPE_ISOLATE_EMULATE, NULL);
   if (!spe) {
      perror("spe_context_create");
      exit(1);
   }
   
   /* Load the program into the context */
   retval = spe_program_load(spe, &spu_secure_comm);
   if (retval) {
      perror("spe_program_load");
      exit(1);
   }

   /* Create thread */
   data.speid = spe;
   if ((retval = pthread_create(&data.pthread, NULL, &ppu_pthread_function, &data)) != 0) {
      perror("pthread_create");
      exit (1);
   }
   
   /* Split the address into high/low 32-bit halves */
   addr_halves[0] = (unsigned int)((unsigned long long)&message & (unsigned long long)0x0ffffffff);
   addr_halves[1] = (unsigned int)((unsigned long long)&message >> 32);
   
   /* Send the high half of the address */
   while(spe_in_mbox_status(spe) == 0);
   spe_in_mbox_write(spe, addr_halves, 2, SPE_MBOX_ALL_BLOCKING);
   
   /* Wait for the thread to finish */
   if ((retval = pthread_join(data.pthread, NULL)) != 0) {
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
