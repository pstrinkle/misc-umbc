/* PROLOG END TAG zYx                                              */
#include "../common.h"
#include <spu_mfcio.h>
#include <stdio.h>

record (*array0) [bsize] __attribute__ ((aligned (128)));
record (*array1) [bsize] __attribute__ ((aligned (128)));
record (*array2) [bsize] __attribute__ ((aligned (128)));

void
phase22C (
	record (*A0) [bsize],
	record (*A1) [bsize],
	record (*A2) [bsize],
	int *xj1,
	int *xj2,
	int *xj3,
	int maxsz ) {
	int j1, j2, j3 ;

	j1=*xj1; j2=*xj2; j3=*xj3;
	array0 = A0;  array1 = A1;  array2 = A2;

	while ( j1!=maxsz && j2!=maxsz && j3!=maxsz ) {
		if ( (*array0)[j1].key > (*array1)[j2].key ) {
			(*array2)[j3] = (*array0)[j1]; j3++; j1++;
		} else {
			(*array2)[j3] = (*array1)[j2]; j3++; j2++;
		}
	}

	*xj1=j1; *xj2=j2; *xj3=j3;

}
