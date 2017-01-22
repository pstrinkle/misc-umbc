#include <stdio.h>
#include <stdlib.h>
#include <libspe2.h>
#include <pthread.h>
#include <libsync.h>

/* The data sent to the pthread */
typedef struct ppu_pthread_data {
    spe_context_ptr_t speid;
    pthread_t pthread;
    void *argp;
} ppu_pthread_data_t;

/* The function executed in the pthread */
void *ppu_pthread_function(void *arg) {
   ppu_pthread_data_t *data = (ppu_pthread_data_t *)arg;
   int retval;
   unsigned int entry = SPE_DEFAULT_ENTRY;
   if ((retval = spe_context_run(data->speid, 
      &entry, 0, data->argp, NULL, NULL)) < 0) {
      perror("spe_context_run");
      exit (1);
   }
   pthread_exit(NULL);
}

/* SPU initialization data */
typedef struct _control_block {
   cond_ea_t cashier;
   mutex_ea_t cashier_mutex, served_mutex;
   unsigned long long served_addr;
} control_block;

/* SPU program handle */
extern spe_program_handle_t spu_cashier;  
ppu_pthread_data_t data[6];
control_block cb __attribute__ ((aligned (128)));

/* Declare variables */
volatile int cashier_var __attribute__ ((aligned (128)));
volatile int cashier_mutex_var __attribute__ ((aligned (128)));
volatile int served_mutex_var __attribute__ ((aligned (128)));
volatile int num_served __attribute__ ((aligned (128)));

int main(int argc, char **argv) {
   int i, retval, spus;
   
   /* Create condition variable, mutexes, pointer */
   cb.cashier = (cond_ea_t)&cashier_var;
   cb.cashier_mutex = (mutex_ea_t)&cashier_mutex_var;
   cb.served_mutex = (mutex_ea_t)&served_mutex_var;
   cb.served_addr = (unsigned long long)&num_served;
   
   /* Initialize condition variable, mutexes */
   cond_init(cb.cashier);
   mutex_init(cb.cashier_mutex);
   cond_init(cb.served_mutex);
   num_served = 0;
   
   /* Determine number of available SPUs */
   spus = spe_cpu_info_get(SPE_COUNT_USABLE_SPES, 0);
   
   /* Create contexts and threads */
   for (i=0; i<spus; i++) {
   
      /* Create context */
      if ((data[i].speid = spe_context_create
         (0, NULL)) == NULL) {
         perror("spe_context_create");
         exit(1);
      }
      
      /* Load program into the context */
      if ((retval = spe_program_load(data[i].speid, 
         &spu_cashier)) != 0) {
         perror("spe_program_load");
         exit (1);
      }
      
	   data[i].argp = &cb;
     
      /* Create thread */
      if ((retval = pthread_create(&data[i].pthread, 
         NULL, &ppu_pthread_function, &data[i])) != 0) {
         perror("pthread_create");
         exit (1);
      }
   }
   
   int count = 0;
   while (count < spus) {
      cond_signal(cb.cashier);
      count = atomic_read((atomic_ea_t)cb.served_addr);
   }
  
   for (i = 0; i < spus; i++) {
   
      /* Wait for the threads */
      if ((retval = pthread_join
          (data[i].pthread, NULL)) != 0) {
          perror("pthread_join");
          exit (1);
      }
      
      /* Deallocate the contexts */
      if ((retval = spe_context_destroy 
          (data[i].speid)) != 0) {
          perror("spe_context_destroy");
          exit (1);
      }
   }
  return 0;
}
