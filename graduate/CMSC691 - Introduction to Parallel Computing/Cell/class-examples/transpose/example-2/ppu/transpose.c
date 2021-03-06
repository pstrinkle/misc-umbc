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

#include <sys/time.h>
struct timezone tzone;
struct timeval time0,time1;
int sec, usec ;


# define loops 10

float initial_matrix [tsize] [tsize] __attribute__ ((aligned (128)));
float final_matrix   [tsize] [tsize] __attribute__ ((aligned (128)));
struct arguments args;


#define NUM_THREADS 1

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
//char parameter_data[ NUM_THREADS ][128] __attribute__ ((aligned (128)));


/* this is the pointer to the SPE code, to be used at thread creation time */
extern spe_program_handle_t transpose_spu;


int main( int argc, char *argv[] ) {
	int i, j, dummy;
	pthread_t         threads     [ NUM_THREADS ];
	spe_context_ptr_t spe_contexts[ NUM_THREADS ];
	thread_args_t     thread_args [ NUM_THREADS ];

	int rows;
	dummy = argc; dummy = (int)argv;

	// initialize initial & final matrix

# ifndef NEVER
	for(i=0;i<tsize;i++) {
		for(j=0;j<tsize;j++) {
			initial_matrix [i][j] = tsize*i+j ;
			final_matrix   [i][j] = 0 ;
		}
	}
# endif


	// perform transpose
	printf ( "SPE: Transpose \n");

	gettimeofday( &time0, &tzone );
	
	// start jobs

	rows = ((tsize/32)+NUM_THREADS-1)/NUM_THREADS ;	// determine amount of work each spe should do
	for ( i=0; i < NUM_THREADS; i++ ) {

		// set arguments
		args.initial   = (float (*)[tsize][tsize])initial_matrix ;
		args.final     = (float (*)[tsize][tsize])final_matrix ;
		args.i_initial = i*rows ;
		
		spe_contexts[i] = spe_context_create( 0, NULL ); // (flags, gang)
		spe_program_load( spe_contexts[i], &transpose_spu );
		
		thread_args[i].spe_context = spe_contexts[i];
		thread_args[i].argp = &args ;
		thread_args[i].envp = NULL;
		
		pthread_create( &threads[i], NULL, &spe_thread, &thread_args[i] );

	}
	
	// wait for tasks to complete
	for ( i=0; i < NUM_THREADS; i++ ) { pthread_join( threads[i], NULL ); }        // wait for threads

	gettimeofday( &time1, &tzone );

	// print time to complete
	sec  = time1.tv_sec  - time0.tv_sec ;
	usec = time1.tv_usec - time0.tv_usec ;
	if ( usec < 0 ) { sec--; usec+=1000000 ; }
	printf("SPE: Transpose Done -- matrix[%d][%d]: time=%d.%06d\n",tsize,tsize,sec,usec);


	for ( i=0; i < NUM_THREADS; i++ ) { spe_context_destroy( spe_contexts[i] ); }  // destroy threads
	
	// Check for correctness of final matrix
# ifndef NEVER
	{
		int error ;
		error = 0;
		for(i=0;i<tsize;i++) {
			for(j=0;j<tsize;j++) {
				if ( final_matrix[j][i] != tsize*i+j ) error = 1 ;
			}
		}
		if (error) { printf("Error in transpose.\n"); }
		else { printf("Transpose is correct.\n"); }
	}
# endif
# ifdef NEVER
	{ int i, j;
	for (i=0;i<10;i++) {
		for (j=0;j<32;j++) {
			printf(" %8.2f",final_matrix[i][j]);
		}
		printf("\n");
	}
	}
# endif

	return 0;
}
