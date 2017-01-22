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

// total 1000*1000 = 4,000,000 B
// total 4000*4000 = 64,000,000 B
# define tsize 128*32
# define loops 1

float matrix [tsize] [tsize];

struct timezone tzone;
struct timeval time0,time1;
int sec, usec ;


//int main( int argc, char *argv[] ) {
int main( void ) {

	int i, j, l ;
	float temp ;

	for(i=0;i<tsize;i++) {
		for(j=0;j<tsize;j++) {
			matrix[i][j] = tsize*i+j ;
		}
	}


	puts( "PPE-only: Transpose");  fflush(stdout);

	gettimeofday( &time0, &tzone );

	for(l=0;l<loops;l++) {
		for(i=0;i<tsize;i++) {
			for(j=i+1;j<tsize;j++) {
				temp         = matrix[i][j] ;
				matrix[i][j] = matrix[j][i] ;
				matrix[j][i] = temp ;
			}
		}
	}

	gettimeofday( &time1, &tzone );

	sec  = time1.tv_sec  - time0.tv_sec ;
	usec = time1.tv_usec - time0.tv_usec ;
	if ( usec < 0 ) { sec--; usec+=1000000 ; }


	printf("PPE: Done matrix[%d][%d]: time=%d.%06d\n",tsize,tsize,sec,usec);  fflush(stdout);

# ifndef NEVER
	{
		int error ;
		error = 0;
		for(i=0;i<tsize;i++) {
			for(j=0;j<tsize;j++) {
				if ( matrix[j][i] != tsize*i+j ) error = 1 ;
			}
		}
		if (error) { printf("Error in transpose.\n"); fflush(stdout); }
		else { printf("Transpose is correct.\n"); fflush(stdout); }
	}
# endif

	return 0;
}
