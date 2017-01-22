/* --------------------------------------------------------------  */
/* (C)Copyright 2001,2006,                                         */
/* International Business Machines Corporation,                    */
/* Sony Computer Entertainment, Incorporated,                      */
/* Toshiba Corporation,                                            */
/*                                                                 */
/* All Rights Reserved.                                            */
/* --------------------------------------------------------------  */
/* PROLOG END TAG zYx                                              */
#include "../common.h"
#include <spu_mfcio.h>
#include <stdio.h>



//unsigned char parameter_area[128] __attribute__ ((aligned (128)));
struct arguments args __attribute__ ((aligned (128)));
struct arguments args2 __attribute__ ((aligned (128)));

record (*array0) [tsize] __attribute__ ((aligned (128)));
record (*array1) [tsize] __attribute__ ((aligned (128)));
record (*array2) [tsize] __attribute__ ((aligned (128)));

record   darrayA0 [tsize] __attribute__ ((aligned (128)));
record   darrayA1 [tsize] __attribute__ ((aligned (128)));
record   darrayB0 [tsize] __attribute__ ((aligned (128)));
record   darrayB1 [tsize] __attribute__ ((aligned (128)));
record   darrayC0 [tsize] __attribute__ ((aligned (128)));
record   darrayC1 [tsize] __attribute__ ((aligned (128)));

void getlarge( void* to, unsigned long from, int size, int tag ) {
	unsigned long ito, ifrom;
	ito   = (unsigned long)to;
	ifrom = (unsigned long)from;
	while ( size >= 16384 ) {
		mfc_get((void*)ito, (unsigned long)ifrom, 16384, tag, 0, 0);
		size  -= 16384;
		ito   += 16384;
		ifrom += 16384;
	}
	if (size > 0 ) {
		mfc_get((void*)ito, (unsigned long)ifrom, size, tag, 0, 0);
	}
}

void putlarge( void* from, unsigned long to, int size, int tag ) {
	unsigned long ito, ifrom;
	ito   = (unsigned long)to;
	ifrom = (unsigned long)from;
	while ( size >= 16384 ) {
		mfc_put((void*)ifrom, (unsigned long)ito, 16384, tag, 0, 0);
		size  -= 16384;
		ito   += 16384;
		ifrom += 16384;
	}
	if (size > 0 ) {
		mfc_put((void*)ifrom, (unsigned long)ito, size, tag, 0, 0);
	}
}

int main(unsigned long long speid, addr64 argp, addr64 envp) 
{
	unsigned long long dummy;

	int l ;
	int k, k2, j, j1, j2, j3 ;
	
	/* Here is the actual DMA call */
	/* the first parameter is the address in local store to place the data */
	/* the second parameter holds the main memory address                  */
	/* the third parameter holds the number of bytes to DMA                */
	/* the fourth parameter identifies a "tag" to associate with this DMA  */
	/* (this should be a number between 0 and 31, inclusive)               */
	/* the last two parameters are only useful if you've implemented your  */
	/* own cache replacement management policy.  Otherwise set them to 0.  */
	dummy = envp.ull ;
	
	mfc_get((void*)&args, argp.ull, 128, 31, 0, 0);
	
	/* Now, we set the "tag bit" into the correct channel on the hardware  */
	/* this is always 1 left-shifted by the tag specified with the DMA     */
	/* for whose completion you wish to wait.                              */
	mfc_write_tag_mask(1<<31);

	/* Wait for the data array DMA to complete. */
	mfc_read_tag_status_all();


	printf("SPE(%lld): Data received is: %d %d %d\n", speid, (int)args.initial, (int)args.final, (int)args.i_initial );
	printf("SPE(%lld): Data received is: %x %x %d\n", speid, (int)args.initial, (int)args.final, (int)args.i_initial );
	printf("SPE(%lld): size= %d \n", speid, (int)args.final-(int)args.initial );

//	mfc_get((void*)&darray0, (unsigned long)args.initial, stsize*sizeof(record), 31, 0, 0);
	getlarge( (void*)&darrayA0, (unsigned long)args.initial, stsize*sizeof(record), 31 );
	mfc_read_tag_status_all(); // Wait for the data array DMA to complete.

# ifdef NEVER
	printf("darrayA0 spe %x %ld\n",&(darrayA0[0].key),stsize*sizeof(record));
	{ int i;
	for (i=0;i<10;i++) {
		printf("%2d %3ld %3ld \n",i,darrayA0[i].key,darrayA0[i].data);
	}
	}
# endif

	for(l=0;l<loops;l++) {
		array0 = &darrayC0 ;  array1 = &darrayA0 ;
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


# ifdef NEVER
	printf("darray1\n");
	{ int i;
	for (i=0;i<10;i++) {
		printf("%2d %3d \n",i,darray1[i].key);
	}
	}
	printf("(*array0)\n");
	{ int i;
	for (i=0;i<10;i++) {
		printf("%2d %3d \n",i,(*array0)[i].key);
	}
	}
	printf("(*array1)\n");
	{ int i;
	for (i=0;i<10;i++) {
		printf("%2d %3d \n",i,(*array1)[i].key);
	}
	}
# endif


	putlarge( (void*)&((*array1)[0]), (unsigned long)args.final, stsize*sizeof(record), 31 );
	mfc_read_tag_status_all(); // Wait for the data array DMA to complete.

	return 0;
}
