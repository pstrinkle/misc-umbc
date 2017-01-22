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

float Amatrix [tsize] [tsize];
float Bmatrix [tsize] [tsize];
float Cmatrix [tsize] [tsize];
float Dmatrix [tsize] [tsize];

struct timezone tzone;
struct timeval time0,time1;
int sec, usec ;


//int main( int argc, char *argv[] ) {
int main( void ) {

	int i, j, k, l ;
	int tmi, tmj;

	for(i=0;i<tsize;i++) {
		for(j=0;j<tsize;j++) {
			tmi = tsize-i;  tmj = tsize-j;
			Amatrix[i][j] = 3*tmi+tmj ;
			Bmatrix[i][j] = 3*tmi+tmj ;
			Cmatrix[i][j] = 0 ;
			Dmatrix[i][j] = 0 ;
		}
	}


	puts( "PPE-only: Multiply");  fflush(stdout);

	gettimeofday( &time0, &tzone );

	for(l=0;l<loops;l++) {
		for(i=0;i<tsize;i++) {
			for(j=0;j<tsize;j++) {
				for(k=0;k<tsize;k++) {
					Cmatrix[i][j] += Amatrix[i][k] * Bmatrix[k][j] ;
					Dmatrix[i][j] =  Cmatrix[i][j] ;
					
				}
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
				if ( Cmatrix[i][j] != Dmatrix[i][j] ) error = 1 ;
			}
		}
		if (error) { printf("Error in Multiply.\n"); fflush(stdout); }
		else { printf("Multiply is correct.\n"); fflush(stdout); }
	}
# endif

# ifdef NEVER
		printf("\n ");
		for(i=0;i<tsize;i++) {
			for(j=0;j<10;j++) {
//			for(j=tsize-10;j<tsize;j++) {
				printf("%14.8e ",Cmatrix[i][j]);
			}
			printf("\n ");
		}
# endif

# ifdef NEVER
		printf("\n ");
		for(i=0;i<tsize;i++) {
			printf("%d -- %14.8e %14.8e %14.8e \n",i,Amatrix[tsize-1][i],Bmatrix[i][tsize-1],Cmatrix[i][tsize-1]);
		}
# endif

	return 0;
}
