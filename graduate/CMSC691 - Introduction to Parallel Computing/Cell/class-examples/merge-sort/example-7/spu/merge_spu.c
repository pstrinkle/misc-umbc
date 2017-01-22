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

record (*array0) [bsize] __attribute__ ((aligned (128)));
record (*array1) [bsize] __attribute__ ((aligned (128)));
record (*array2) [bsize] __attribute__ ((aligned (128)));
record (*brray0) [bsize] __attribute__ ((aligned (128)));
record (*brray1) [bsize] __attribute__ ((aligned (128)));
record (*brray2) [bsize] __attribute__ ((aligned (128)));
record (*crray0) [bsize] __attribute__ ((aligned (128)));
record (*crray1) [bsize] __attribute__ ((aligned (128)));
record (*crray2) [bsize] __attribute__ ((aligned (128)));

record   darrayA0 [bsize] __attribute__ ((aligned (128)));
record   darrayA1 [bsize] __attribute__ ((aligned (128)));
record   darrayB0 [bsize] __attribute__ ((aligned (128)));
record   darrayB1 [bsize] __attribute__ ((aligned (128)));
record   darrayC0 [bsize] __attribute__ ((aligned (128)));
record   darrayC1 [bsize] __attribute__ ((aligned (128)));

unsigned long arrayA;
unsigned long arrayB;
unsigned long arrayC;

void *phase1C ( record (*A0) [bsize], record (*A1) [bsize] ) ;
void *phase1  ( record (*A0) [bsize], record (*A1) [bsize] ) ;
void phase21C ( record (*) [bsize], record (*) [bsize], int *, int *, int  ) ;
void phase21  ( record (*) [bsize], record (*) [bsize], int *, int *, int  ) ;
void phase22C ( record (*) [bsize], record (*) [bsize], record (*) [bsize], int *, int *, int *, int ) ;
void phase22  ( record (*) [bsize], record (*) [bsize], record (*) [bsize], int *, int *, int *, int ) ;

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


void waitfor_matrix_io ( int tag ) {
	mfc_write_tag_mask(1<<tag);
	mfc_read_tag_status_all();   // Wait for the data array DMA to complete.
}

int assemtest=0;


int main(unsigned long long speid, addr64 argp, addr64 envp) 
{
	unsigned long long dummy;

	int l ;
	int p0, p1 ;
	int i1, i2, i3 ;
	int j1, j2, j3 ;
	dummy = envp.ull ;
	dummy = speid ;


	// get arguments
	mfc_get((void*)&args, argp.ull, 128, 31, 0, 0);
	waitfor_matrix_io  ( 31 );


//	printf("SPE(%lld): Data received is: %d %d %d %d\n", speid, (int)args.inA
//	, (int)args.out, (int)args.i_initial, (int)args.i_final );
//	printf("SPE(%lld): Data received is: %x %x %d %d\n", speid, (int)args.inA
//	, (int)args.out, (int)args.i_initial, (int)args.i_final );
//	printf("SPE(%lld): size= %d \n", speid, (int)args.out-(int)args.inA );
//	fflush(stdout);



	if ( args.sortType == 0 ) {
		l = args.i_initial ;
		getlarge( (void*)&darrayA0, (unsigned long)(args.inA)+(l*bsize*sizeof(record)), bsize*sizeof(record), 31 );
		for( l=args.i_initial; l<args.i_final; l+=2 ) {
			
			getlarge( (void*)&darrayA1, (unsigned long)(args.inA)+((l+1)*bsize*sizeof(record)), bsize*sizeof(record), 30 );

			waitfor_matrix_io  ( 31 );
			array0 = &darrayC0 ;  array1 = &darrayA0 ;
			array1 = phase1(array0,array1);

			putlarge( (void*)&((*array1)[0]), (unsigned long)(args.out)+(l*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			getlarge( (void*)&darrayA0, (unsigned long)(args.inA)+((l+2)*bsize*sizeof(record)), bsize*sizeof(record), 31 );

			waitfor_matrix_io  ( 30 );
			brray0 = &darrayC1 ;  brray1 = &darrayA1 ;
			brray1 = phase1(brray0,brray1);

			putlarge( (void*)&((*brray1)[0]), (unsigned long)(args.out)+((l+1)*bsize*sizeof(record)), bsize*sizeof(record), 30 );
		}
		waitfor_matrix_io  ( 31 );
		waitfor_matrix_io  ( 30 );
	} else if ( args.sortType == 1 ) {
		arrayA = (unsigned long)args.out;
		arrayB = (unsigned long)args.inA;

		for( p0=1; p0<args.blocks; p0<<=1 ) {
			arrayC=arrayA; arrayA=arrayB; arrayB=arrayC; 
		for( p1=args.i_initial; p1<args.i_final; p1+=(p0*2) ) {
			i1 = p1 ;  i2 = p1+p0;  i3 = p1;
			
			array0 = &darrayA0 ;  array1 = &darrayB0 ;  array2 = &darrayC0 ;
			brray0 = &darrayA1 ;  brray1 = &darrayB1 ;  brray2 = &darrayC1 ;
			j1=0;  j2=0;  j3=0;
	
			getlarge( (void*)array0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			getlarge( (void*)array1, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			
			i1++; 
			if ( i1<(p1+p0) ) { // prefetch next array0 buffer
				getlarge( (void*)brray0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 30 );
			}
			i2++; 
			if ( i2<(p1+2*p0) ) { // prefetch next array1 buffer
				getlarge( (void*)brray1, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 29 );
			}
		
			waitfor_matrix_io  ( 31 );
			while ( i1<=(p1+p0) && i2<=(p1+2*p0) ) {

				phase22(array0,array1,array2,&j1,&j2,&j3,bsize);

				if ( j1>=bsize ) {
					i1++; 
					if ( i1<=(p1+p0) ) {
						waitfor_matrix_io  ( 30 );  j1=0;
						crray0 = array0; array0 = brray0; array0 = crray0;
						if ( i1<(p1+p0) ) {
							getlarge( (void*)brray0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 30 );
						}
					}
				}
				if ( j2>=bsize ) {
					i2++; 
					if ( i2<=(p1+2*p0) ) {
						waitfor_matrix_io  ( 29 );  j2=0;
						crray1 = array1; array1 = brray1; array0 = crray1;
						if ( i2<(p1+2*p0) ) {
							getlarge( (void*)brray1, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 29 );
						}
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						waitfor_matrix_io  ( 28 );  j3=0;
						crray2 = array2; array2 = brray2; array2 = crray2;
						putlarge( (void*)brray2, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 28 );
					}
					i3++;
				}
			}
			
			while ( i1<=(p1+p0) ) {

				phase21(array0,array2,&j1,&j3,bsize);
				
				if ( j1>=bsize ) {
					i1++; 
					if ( i1<=(p1+p0) ) {
						waitfor_matrix_io  ( 30 );  j1=0;
						crray0 = array0; array0 = brray0; array0 = crray0;
						if ( i1<(p1+p0) ) {
							getlarge( (void*)brray0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 30 );
						}
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						waitfor_matrix_io  ( 28 );  j3=0;
						crray2 = array2; array2 = brray2; array2 = crray2;
						putlarge( (void*)brray2, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 28 );
					}
					i3++;
				}
			}
			
			while ( i2<=(p1+2*p0) ) {
				
				phase21(array1,array2,&j2,&j3,bsize);
				
				if ( j2>=bsize ) {
					i2++; 
					if ( i2<=(p1+2*p0) ) {
						waitfor_matrix_io  ( 29 );  j2=0;
						crray1 = array1; array1 = brray1; array0 = crray1;
						if ( i2<(p1+2*p0) ) {
							getlarge( (void*)brray1, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 29 );
						}
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						waitfor_matrix_io  ( 28 );  j3=0;
						crray2 = array2; array2 = brray2; array2 = crray2;
						putlarge( (void*)brray2, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 28 );
					}
					i3++;
				}
			}
		
		}
			waitfor_matrix_io  ( 28 );
		}
	
	} else if ( args.sortType == 2 ) {
			arrayA = (unsigned long)args.inA;
			arrayB = (unsigned long)args.out;
	
			p0 = args.blocks/2 ;  p1 = args.i_initial ;
			i1 = p1;  i2 = p1+p0;  i3 = p1;
	
			array0 = &darrayA0 ;  array1 = &darrayB0 ;  array2 = &darrayC0 ;
			brray0 = &darrayA1 ;  brray1 = &darrayB1 ;  brray2 = &darrayC1 ;
			j1=0;  j2=0;  j3=0;
	
			getlarge( (void*)array0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			getlarge( (void*)array1, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			
			i1++; 
			if ( i1<(p1+p0) ) { // prefetch next array0 buffer
				getlarge( (void*)brray0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 30 );
			}
			i2++; 
			if ( i2<(p1+2*p0) ) { // prefetch next array1 buffer
				getlarge( (void*)brray1, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 29 );
			}
		
			waitfor_matrix_io  ( 31 );
			while ( i1<=(p1+p0) && i2<=(p1+2*p0) ) {

				phase22(array0,array1,array2,&j1,&j2,&j3,bsize);

				if ( j1>=bsize ) {
					i1++; 
					if ( i1<=(p1+p0) ) {
						waitfor_matrix_io  ( 30 );  j1=0;
						crray0 = array0; array0 = brray0; array0 = crray0;
						if ( i1<(p1+p0) ) {
							getlarge( (void*)brray0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 30 );
						}
					}
				}
				if ( j2>=bsize ) {
					i2++; 
					if ( i2<=(p1+2*p0) ) {
						waitfor_matrix_io  ( 29 );  j2=0;
						crray1 = array1; array1 = brray1; array0 = crray1;
						if ( i2<(p1+2*p0) ) {
							getlarge( (void*)brray1, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 29 );
						}
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						waitfor_matrix_io  ( 28 );  j3=0;
						crray2 = array2; array2 = brray2; array2 = crray2;
						putlarge( (void*)brray2, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 28 );
					}
					i3++;
				}
			}
			
			while ( i1<=(p1+p0) ) {

				phase21(array0,array2,&j1,&j3,bsize);
				
				if ( j1>=bsize ) {
					i1++; 
					if ( i1<=(p1+p0) ) {
						waitfor_matrix_io  ( 30 );  j1=0;
						crray0 = array0; array0 = brray0; array0 = crray0;
						if ( i1<(p1+p0) ) {
							getlarge( (void*)brray0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 30 );
						}
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						waitfor_matrix_io  ( 28 );  j3=0;
						crray2 = array2; array2 = brray2; array2 = crray2;
						putlarge( (void*)brray2, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 28 );
					}
					i3++;
				}
			}
			
			while ( i2<=(p1+2*p0) ) {
				
				phase21(array1,array2,&j2,&j3,bsize);
				
				if ( j2>=bsize ) {
					i2++; 
					if ( i2<=(p1+2*p0) ) {
						waitfor_matrix_io  ( 29 );  j2=0;
						crray1 = array1; array1 = brray1; array0 = crray1;
						if ( i2<(p1+2*p0) ) {
							getlarge( (void*)brray1, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 29 );
						}
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						waitfor_matrix_io  ( 28 );  j3=0;
						crray2 = array2; array2 = brray2; array2 = crray2;
						putlarge( (void*)brray2, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 28 );
					}
					i3++;
				}
			}

	}


	return 0;
}
