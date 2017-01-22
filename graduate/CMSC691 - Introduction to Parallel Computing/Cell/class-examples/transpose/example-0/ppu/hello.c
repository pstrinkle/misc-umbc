/* --------------------------------------------------------------  */
/* (C)Copyright 2001,2007,                                         */
/* International Business Machines Corporation,                    */
/* Sony Computer Entertainment, Incorporated,                      */
/* Toshiba Corporation,                                            */
/*                                                                 */
/* All Rights Reserved.                                            */
/* --------------------------------------------------------------  */
/* PROLOG END TAG zYx                                              */
#include "../common.h"

#include <libspe2.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>


#define NUM_THREADS 6

typedef struct {
  spe_context_ptr_t spe_context;
  void *argp;
  void *envp;
} thread_args_t;



void *spe_thread( void *voidarg ) {

  thread_args_t *arg = (thread_args_t *)voidarg;

  unsigned int runflags = 0;
  unsigned int entry = SPE_DEFAULT_ENTRY;

  spe_context_run( arg->spe_context, &entry, runflags, arg->argp, arg->envp, NULL );
  pthread_exit( NULL );
}




/* String to pass to SPE */
char parameter_data[ NUM_THREADS ][128] __attribute__ ((aligned (128)));


/* this is the pointer to the SPE code, to be used at thread creation time */
extern spe_program_handle_t hello_spu;


int main( int argc, char *argv[] ) {

  int i;

  puts( "PPE: Hello World!");

  for ( i=0; i < NUM_THREADS; i++ ) {
    sprintf( parameter_data[i], "This space for rent. (%d)\n", i );
  }

  pthread_t threads[ NUM_THREADS ];
  spe_context_ptr_t spe_contexts[ NUM_THREADS ];
  thread_args_t thread_args[ NUM_THREADS ];


  for ( i=0; i < NUM_THREADS; i++ ) {

    spe_contexts[i] = spe_context_create( 0, NULL ); // (flags, gang)
    spe_program_load( spe_contexts[i], &hello_spu );

    thread_args[i].spe_context = spe_contexts[i];
    thread_args[i].argp = &parameter_data[i];
    thread_args[i].envp = NULL;

    pthread_create( &threads[i], NULL, &spe_thread, &thread_args[i] );
  }
    

  for ( i=0; i < NUM_THREADS; i++ ) {
    pthread_join( threads[i], NULL );
  }

  for ( i=0; i < NUM_THREADS; i++ ) {
    spe_context_destroy( spe_contexts[i] );
  }

  printf("PPE: Done\n");

  return 0;
}
