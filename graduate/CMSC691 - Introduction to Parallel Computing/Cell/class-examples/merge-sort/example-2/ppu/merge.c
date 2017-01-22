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

union {
struct arguments a;
char bytes[128];
} args[NUM_THREADS] __attribute__ ((aligned (128)));


typedef struct {
  spe_context_ptr_t spe_context;
  void *argp;
  void *envp;
} thread_args_t;


//record (*array0) [tsize] __attribute__ ((aligned (128)));
//record (*array1) [tsize] __attribute__ ((aligned (128)));
//record (*array2) [tsize] __attribute__ ((aligned (128)));
record   pdarray0 [tsize] __attribute__ ((aligned (128)));
record   pdarray1 [tsize] __attribute__ ((aligned (128)));


void *spe_thread( void *voidarg ) {

  thread_args_t *arg = (thread_args_t *)voidarg;

  unsigned int runflags = 0;
  unsigned int entry = SPE_DEFAULT_ENTRY;

  spe_context_run( arg->spe_context, &entry, runflags, arg->argp, arg->envp, NULL );

  pthread_exit( NULL );

}


/* this is the pointer to the SPE code, to be used at thread creation time */
extern spe_program_handle_t merge_spu;


int main( int argc, char *argv[] ) {
	int i, dummy;
	pthread_t         threads     [ NUM_THREADS ];
	spe_context_ptr_t spe_contexts[ NUM_THREADS ];
	thread_args_t     thread_args [ NUM_THREADS ];

	int rows;
	dummy = argc; dummy = (int)argv;

	// initialize initial & final matrix

	for(i=0;i<tsize;i++) {
		pdarray0[i].key  = i ;
		pdarray0[i].data = tsize-i-1 ;
		pdarray1[i].key  = i ;
	}


	// perform merge
	printf ( "PPE: Merge   elements=%d  bytes=%d\n",tsize,tsize*sizeof(pdarray0[0]));

	gettimeofday( &time0, &tzone );
	
# ifdef NEVER
	printf("pdarray0 ppe\n");
	{
		for(i=0;i<10;i++) {
			printf("%d %ld %ld \n",i, pdarray0[i].key, pdarray0[i].data);
		}
	}
# endif
	// start jobs

	rows = (((tsize/32)+NUM_THREADS-1)/NUM_THREADS)*32 ;	// determine amount of work each spe should do
	for ( i=0; i < NUM_THREADS; i++ ) {

		// set arguments
		args[i].a.initial   = (record (*)[tsize])&pdarray0 ;
		args[i].a.final     = (record (*)[tsize])&pdarray1 ;
		args[i].a.i_initial = i*rows ;
		if ( (i+1)*rows > tsize ) args[i].a.i_final = tsize ;
		else                      args[i].a.i_final = (i+1)*rows ;
		
		spe_contexts[i] = spe_context_create( 0, NULL ); // (flags, gang)
		spe_program_load( spe_contexts[i], &merge_spu );
		
		thread_args[i].spe_context = spe_contexts[i];
		thread_args[i].argp = &args[i] ;
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
	printf("PPE: Merge Done -- matrix[%d]: time=%d.%06d  tasks=%d loops=%d \n"
	,tsize,sec,usec,NUM_THREADS,loops);


	for ( i=0; i < NUM_THREADS; i++ ) { spe_context_destroy( spe_contexts[i] ); }  // destroy threads
	
	// Check for correctness of final matrix
# ifndef NEVER
	{
		int error ;
		error = 0;
		for(i=1;i<tsize;i++) {
				if ( pdarray1[i-1].key < pdarray1[i].key ) error = 1 ;
		}
		if (error) { printf("Error in merge.\n"); fflush(stdout); }
		else { printf("Merge sort is correct.\n"); fflush(stdout); }
	}
# endif
# ifdef NEVER
	{
		for(i=0;i<10;i++) {
			printf("%d %ld %ld \n",i, pdarray1[i].key, pdarray1[i].data);
		}
	}
# endif

	return 0;
}
