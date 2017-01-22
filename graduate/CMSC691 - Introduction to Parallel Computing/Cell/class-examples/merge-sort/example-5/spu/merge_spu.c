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

record   darrayA0 [bsize] __attribute__ ((aligned (128)));
//record   darrayA1 [bsize] __attribute__ ((aligned (128)));
record   darrayB0 [bsize] __attribute__ ((aligned (128)));
//record   darrayB1 [bsize] __attribute__ ((aligned (128)));
record   darrayC0 [bsize] __attribute__ ((aligned (128)));
//record   darrayC1 [bsize] __attribute__ ((aligned (128)));

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
		for( l=args.i_initial; l<args.i_final; l++ ) {
			getlarge( (void*)&darrayA0, (unsigned long)(args.inA)+(l*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			waitfor_matrix_io  ( 31 );

			array0 = &darrayC0 ;  array1 = &darrayA0 ;
# ifdef NEVER
			{
			int j, k, k2 ;
			for(k=2; k<=bsize; k<<=1 ) {  k2 = k/2 ;
				array2 = array0 ;  array0 = array1 ;  array1 = array2 ;

				for(j=0; j<bsize; j+=k ) {
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
# else
# ifdef NEVER
			array1 = phase1C(array0,array1,bsize);
# else
			array1 = phase1(array0,array1);
# endif
# endif
			
			putlarge( (void*)&((*array1)[0]), (unsigned long)(args.out)+(l*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			waitfor_matrix_io  ( 31 );
		}
	} else if ( args.sortType == 1 ) {
		arrayA = (unsigned long)args.out;
		arrayB = (unsigned long)args.inA;

		for( p0=1; p0<args.blocks; p0<<=1 ) {
			arrayC=arrayA; arrayA=arrayB; arrayB=arrayC; 
		for( p1=args.i_initial; p1<args.i_final; p1+=(p0*2) ) {
			i1 = p1 ;  i2 = p1+p0;  i3 = p1;
	
			getlarge( (void*)&darrayA0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			array0 = &darrayA0 ; j1=0;
			getlarge( (void*)&darrayB0, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			array1 = &darrayB0 ; j2=0;
			waitfor_matrix_io  ( 31 );
			array2 = &darrayC0 ; j3=0;
		
			while ( i1<(p1+p0) && i2<(p1+2*p0) ) {
# ifdef NEVER
				if ( (*array0)[j1].key > (*array1)[j2].key ) {
					(*array2)[j3] = (*array0)[j1]; j3++; j1++;
				} else {
					(*array2)[j3] = (*array1)[j2]; j3++; j2++;
				}
# else
# ifdef NEVER
				phase22C(array0,array1,array2,&j1,&j2,&j3,bsize);
# else
				phase22(array0,array1,array2,&j1,&j2,&j3,bsize);
# endif
# endif
				if ( j1>=bsize ) {
					i1++;
					if ( i1<(p1+p0) ) {
						getlarge( (void*)&darrayA0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j1=0;
					}
				}
				if ( j2>=bsize ) {
					i2++;
					if ( i2<(p1+2*p0) ) {
						getlarge( (void*)&darrayB0, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j2=0;
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						putlarge( (void*)&darrayC0, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j3=0;
					}
					i3++;
				}
			}
			
			while ( i1<(p1+p0) ) {
# ifdef NEVER
				(*array2)[j3] = (*array0)[j1]; j3++; j1++;
# else
# ifdef NEVER
				phase21C(array0,array2,&j1,&j3,bsize);
# else
				phase21(array0,array2,&j1,&j3,bsize);
# endif
# endif
				if ( j1>=bsize ) {
					i1++;
					if ( i1<(p1+p0) ) {
						getlarge( (void*)&darrayA0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j1=0;
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						putlarge( (void*)&darrayC0, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j3=0;
					}
					i3++;
				}
			}
			
			while ( i2<(p1+2*p0) ) {
# ifdef NEVER
				(*array2)[j3] = (*array1)[j2]; j3++; j2++;
# else
# ifdef NEVER
				phase21C(array1,array2,&j2,&j3,bsize);
# else
				phase21(array1,array2,&j2,&j3,bsize);
# endif
# endif
				if ( j2>=bsize ) {
					i2++;
					if ( i2<(p1+2*p0) ) {
						getlarge( (void*)&darrayB0, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j2=0;
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						putlarge( (void*)&darrayC0, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j3=0;
					}
					i3++;
				}
			}
		
		}}
	
	} else if ( args.sortType == 2 ) {
			arrayA = (unsigned long)args.inA;
			arrayB = (unsigned long)args.out;
	
			p0 = args.blocks/2 ;  p1 = args.i_initial ;
			i1 = p1;  i2 = p1+p0;  i3 = p1;
	
			getlarge( (void*)&darrayA0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			array0 = &darrayA0 ; j1=0;
			getlarge( (void*)&darrayB0, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 31 );
			array1 = &darrayB0 ; j2=0;
			waitfor_matrix_io  ( 31 );
			array2 = &darrayC0 ; j3=0;
		
			while ( i1<(p1+p0) && i2<(p1+2*p0) ) {
# ifdef NEVER
				if ( (*array0)[j1].key > (*array1)[j2].key ) {
					(*array2)[j3] = (*array0)[j1]; j3++; j1++;
				} else {
					(*array2)[j3] = (*array1)[j2]; j3++; j2++;
				}
# else
# ifdef NEVER
				phase22C(array0,array1,array2,&j1,&j2,&j3,bsize);
# else
				phase22(array0,array1,array2,&j1,&j2,&j3,bsize);
# endif
# endif
				if ( j1>=bsize ) {
					i1++;
					if ( i1<(p1+p0) ) {
						getlarge( (void*)&darrayA0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j1=0;
					}
				}
				if ( j2>=bsize ) {
					i2++;
					if ( i2<(p1+2*p0) ) {
						getlarge( (void*)&darrayB0, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j2=0;
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						putlarge( (void*)&darrayC0, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j3=0;
					}
					i3++;
				}
			}
			
			while ( i1<(p1+p0) ) {
# ifdef NEVER
				(*array2)[j3] = (*array0)[j1]; j3++; j1++;
# else
# ifdef NEVER
				phase21C(array0,array2,&j1,&j3,bsize);
# else
				phase21(array0,array2,&j1,&j3,bsize);
# endif
# endif
				if ( j1>=bsize ) {
					i1++;
					if ( i1<(p1+p0) ) {
						getlarge( (void*)&darrayA0, (unsigned long)(arrayA)+(i1*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j1=0;
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						putlarge( (void*)&darrayC0, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j3=0;
					}
					i3++;
				}
			}
			
			while ( i2<(p1+2*p0) ) {
# ifdef NEVER
				(*array2)[j3] = (*array1)[j2]; j3++; j2++;
# else
# ifdef NEVER
				phase21C(array1,array2,&j2,&j3,bsize);
# else
				phase21(array1,array2,&j2,&j3,bsize);
# endif
# endif
				if ( j2>=bsize ) {
					i2++;
					if ( i2<(p1+2*p0) ) {
						getlarge( (void*)&darrayB0, (unsigned long)(arrayA)+(i2*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j2=0;
					}
				}
				if ( j3>=bsize ) {
					if ( i3<(p1+2*p0) ) {
						putlarge( (void*)&darrayC0, (unsigned long)(arrayB)+(i3*bsize*sizeof(record)), bsize*sizeof(record), 31 );
						waitfor_matrix_io  ( 31 );  j3=0;
					}
					i3++;
				}
			}

	}



	return 0;
}

# ifdef NEVER
	printf("darrayA0\n");
	{ int i;
	for (i=0;i<10;i++) {
		printf("%2d %3d \n",i,darrayA0[i].key);
	}
	}
# endif

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
