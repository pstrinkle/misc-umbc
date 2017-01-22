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


record (*array0) [tsize] __attribute__ ((aligned (128)));
record (*array1) [tsize] __attribute__ ((aligned (128)));
record (*array2) [tsize] __attribute__ ((aligned (128)));
record   darray0 [tsize] __attribute__ ((aligned (128)));
record   darray1 [tsize] __attribute__ ((aligned (128)));


struct timezone tzone;
struct timeval time0,time1;
int sec, usec ;


//int main( int argc, char *argv[] ) {
int main( void ) {

	int l ;
	int k, k2, j, j1, j2, j3, i ;

	for(i=0;i<tsize;i++) {
		darray0[i].key  = i ;
		darray0[i].data = tsize-i-1 ;
	}


	puts( "PPE-only: Merge Sort");  fflush(stdout);

	gettimeofday( &time0, &tzone );

	for(l=0;l<loops;l++) {
		array0 = &darray1 ;  array1 = &darray0 ;
		for(k=2; k<=tsize; k<<=1 ) {  k2 = k/2 ;
			array2 = array0 ;  array0 = array1 ;  array1 = array2 ;

			for(j=0; j<tsize; j+=k ) {
				j1=j; j2=j+k2;  j3=j;
				while ( j1<j+k2 && j2<j+k ) {
					if ( (*array0)[j1].key > (*array0)[j2].key ) {
						(*array1)[j3] = (*array0)[j1]; j3++; j1++;
					} else {
						(*array1)[j3] = (*array0)[j2]; j3++; j2++;
					}
				}
				while ( j1<j+k2 ) {
					(*array1)[j3] = (*array0)[j1]; j3++; j1++; 
					}
				while ( j2<j+k  ) { 
					(*array1)[j3] = (*array0)[j2]; j3++; j2++;
					}
			}

		}
	}

	gettimeofday( &time1, &tzone );

	sec  = time1.tv_sec  - time0.tv_sec ;
	usec = time1.tv_usec - time0.tv_usec ;
	if ( usec < 0 ) { sec--; usec+=1000000 ; }


	printf("PPE: Done array[%d] : time=%d.%06d\n",tsize,sec,usec);  fflush(stdout);

# ifndef NEVER
	{
		int error ;
		error = 0;
		for(i=1;i<tsize;i++) {
				if ( (*array1)[i-1].data > (*array1)[i].data ) error = 1 ;
		}
		if (error) { printf("Error in merge.\n"); fflush(stdout); }
		else { printf("Merge sort is correct.\n"); fflush(stdout); }
	}
# endif
# ifdef NEVER
	{
		for(i=0;i<32;i++) {
			printf("%d %d \n",i,(*array1)[i].key);
		}
	}
# endif

	return 0;
}
