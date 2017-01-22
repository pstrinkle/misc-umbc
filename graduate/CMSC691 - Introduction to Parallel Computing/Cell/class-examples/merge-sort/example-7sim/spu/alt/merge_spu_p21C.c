/* PROLOG END TAG zYx                                              */
#include "../common.h"
#include <spu_mfcio.h>
#include <stdio.h>

record (*array0) [bsize] __attribute__ ((aligned (128)));
record (*array2) [bsize] __attribute__ ((aligned (128)));

void
phase21C ( 
	record (*A0) [bsize],
	record (*A1) [bsize],
	int *xj1,
	int *xj3,
	int maxsz ) {
	int j1, j3 ;

	j1=*xj1; j3=*xj3;
	array0 = A0;  array2 = A1;

	while ( j1!=maxsz && j3!=maxsz ) {
		(*array2)[j3] = (*array0)[j1]; j3++; j1++;
	}

	*xj1=j1; *xj3=j3;

}
