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


record (*array0) [tsize] __attribute__ ((aligned (128)));
record (*array1) [tsize] __attribute__ ((aligned (128)));
record (*array2) [tsize] __attribute__ ((aligned (128)));
record (*arrayT) [tsize] __attribute__ ((aligned (128)));
record   pdarray0 [tsize] __attribute__ ((aligned (128)));
record   pdarray1 [tsize] __attribute__ ((aligned (128)));


int logarithm2( int a ) {
	int i=0;
	while(a) { a>>=1; i++; }
	return i-1;
}


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
	int i, j, dummy;
	pthread_t         threads     [ NUM_THREADS ];
	spe_context_ptr_t spe_contexts[ NUM_THREADS ];
	thread_args_t     thread_args [ NUM_THREADS ];
	int block;
	int Sthreads;
	int log_buffers, log_threads, passes;

	dummy = argc; dummy = (int)argv;

	// initialize initial & final matrix

	for(i=0;i<tsize;i++) {
		pdarray0[i].key  = i ;
		pdarray0[i].data = tsize-i-1 ;
		pdarray1[i].key  = i ;
	}
	
	if ( NUM_THREADS >= 1 ) Sthreads = 1;
	if ( NUM_THREADS >= 2 ) Sthreads = 2;
	if ( NUM_THREADS >= 4 ) Sthreads = 4;
	if ( NUM_THREADS >= 8 ) Sthreads = 8;
	
	log_buffers = logarithm2( buffers );   log_threads = logarithm2( Sthreads );


	// perform merge
	printf ( "PPE: Merge   elements=%d  bytes=%d l(%d,%d) \n",tsize,tsize*sizeof(pdarray0[0]),log_buffers,log_threads);

	gettimeofday( &time0, &tzone );


	// sort each block

	array0 = &pdarray0 ;
	array1 = &pdarray1 ;
	block = buffers/Sthreads ;	// determine amount of work each spe should do
	for ( i=0; i < Sthreads; i++ ) {

		// set arguments
		args[i].a.sortType  = 0 ;  // mini sort step
		args[i].a.inA       = (record (*)[tsize])&((*array0)[0].key) ;
		args[i].a.out       = (record (*)[tsize])&((*array1)[0].key) ;
		args[i].a.blocks    = block ;
		args[i].a.i_initial = i*block ;
		if ( (i+1)*block > tsize ) args[i].a.i_final = tsize ;
		else                       args[i].a.i_final = (i+1)*block ;
		
		spe_contexts[i] = spe_context_create( 0, NULL ); // (flags, gang)
		spe_program_load( spe_contexts[i], &merge_spu );
		
		thread_args[i].spe_context = spe_contexts[i];
		thread_args[i].argp = &args[i] ;
		thread_args[i].envp = NULL;
		
		pthread_create( &threads[i], NULL, &spe_thread, &thread_args[i] );

	}
	
	// wait for tasks to complete
	for ( i=0; i < Sthreads; i++ ) { pthread_join( threads[i], NULL ); }        // wait for threads
	for ( i=0; i < Sthreads; i++ ) { spe_context_destroy( spe_contexts[i] ); }  // destroy threads

	arrayT=array0; array0=array1; array1=arrayT;
	array2 = array0 ;


	// merge most blocks (power of 2 tasks)

	for ( i=0; i < Sthreads; i++ ) {

		// set arguments
		args[i].a.sortType  = 1 ;  // mini merge step
		args[i].a.inA       = (record (*)[tsize])&((*array0)[0].key) ;
		args[i].a.out       = (record (*)[tsize])&((*array1)[0].key) ;
		args[i].a.i_initial = i*block ;
		args[i].a.blocks    = block ;
		if ( (i+1)*block > tsize ) args[i].a.i_final = tsize ;
		else                       args[i].a.i_final = (i+1)*block ;
		
		spe_contexts[i] = spe_context_create( 0, NULL ); // (flags, gang)
		spe_program_load( spe_contexts[i], &merge_spu );
		
		thread_args[i].spe_context = spe_contexts[i];
		thread_args[i].argp = &args[i] ;
		thread_args[i].envp = NULL;
		
		pthread_create( &threads[i], NULL, &spe_thread, &thread_args[i] );

	}
	
	// wait for tasks to complete
	for ( i=0; i < Sthreads; i++ ) { pthread_join( threads[i], NULL ); }        // wait for threads
	for ( i=0; i < Sthreads; i++ ) { spe_context_destroy( spe_contexts[i] ); }  // destroy threads
	
	passes = log_buffers-log_threads;
	if ( passes&1 ) { arrayT=array0; array0=array1; array1=arrayT; }
	array2 = array0 ;


	// last merge steps
	if ( Sthreads>1 ) {
	for ( j=Sthreads/2; j>=1; j>>=1 ) {
		block = buffers/j ;	// determine amount of work each spe should do
		for ( i=0; i < j; i++ ) {
	
			// set arguments
			args[i].a.sortType  = 2 ;  // mini merge step
			args[i].a.inA       = (record (*)[tsize])&((*array0)[0].key) ;
			args[i].a.out       = (record (*)[tsize])&((*array1)[0].key) ;
			args[i].a.blocks    = block ;
			args[i].a.i_initial = i*block ;
			if ( (i+1)*block > tsize ) args[i].a.i_final = tsize ;
			else                       args[i].a.i_final = (i+1)*block ;

			spe_contexts[i] = spe_context_create( 0, NULL ); // (flags, gang)
			spe_program_load( spe_contexts[i], &merge_spu );
			
			thread_args[i].spe_context = spe_contexts[i];
			thread_args[i].argp = &args[i] ;
			thread_args[i].envp = NULL;
			
			pthread_create( &threads[i], NULL, &spe_thread, &thread_args[i] );
	
		}
	
		// wait for tasks to complete
		for ( i=0; i < j; i++ ) { pthread_join( threads[i], NULL ); }        // wait for threads
		for ( i=0; i < j; i++ ) { spe_context_destroy( spe_contexts[i] ); }  // destroy threads
		arrayT=array0; array0=array1; array1=arrayT;
	}}
	array2 = array0 ;


	gettimeofday( &time1, &tzone );

	// print time to complete
	sec  = time1.tv_sec  - time0.tv_sec ;
	usec = time1.tv_usec - time0.tv_usec ;
	if ( usec < 0 ) { sec--; usec+=1000000 ; }
	printf("PPE: Merge Done -- matrix[%d]: time=%d.%06d  tasks=%d \n"
	,tsize,sec,usec,NUM_THREADS);


	
	// Check for correctness of final matrix
# ifndef NEVER
	{
		int error=0 ;
		int fsterror0=0 ;
		for(i=1;i<tsize;i++) {
				if ( (*array2)[i-1].key < (*array2)[i].key ) { if(!error) { fsterror0 = i; } error = 1 ;  }
		}
		if (error) { 
			printf("Error in merge. (%d)= %d %d \n",fsterror0,(int)(*array2)[fsterror0].key
			,(int)(*array2)[fsterror0].data); fflush(stdout); 
		} else { printf("Merge sort is correct.\n"); fflush(stdout); }
	}
# endif
# ifdef NEVER
	{
		for(i=0;i<10;i++) {
			printf("%d %ld %ld \n",i, (*array2)[i].key, (*array2)[i].data);
		}
	}
# endif

	return 0;
}
