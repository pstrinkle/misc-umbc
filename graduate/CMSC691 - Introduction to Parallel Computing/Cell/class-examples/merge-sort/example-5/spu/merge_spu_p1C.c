/* PROLOG END TAG zYx                                              */
#include "../common.h"
#include <spu_mfcio.h>
#include <stdio.h>

record (*array0) [bsize] __attribute__ ((aligned (128)));
record (*array1) [bsize] __attribute__ ((aligned (128)));
record (*array2) [bsize] __attribute__ ((aligned (128)));

void *
phase1C ( record (*A0) [bsize], record (*A1) [bsize], int sz ) {
	int j, k, k2 ;
	int j1, j2, j3 ;
	int size;

	size = sz;
	array0 = A0;  array1 = A1;
	for(k=2; k<=size; k<<=1 ) {  k2 = k/2 ;
		array2 = array0 ;  array0 = array1 ;  array1 = array2 ;

		for(j=0; j<size; j+=k ) {
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

	return array1;
}
