#ifndef __common_h__
#define __common_h__

/* This union helps clarify calling parameters between the PPE and the SPE. */

typedef union
{
  unsigned long long ull;
  unsigned int ui[2];
  void *p;
} addr64;

/*
	This sort only supports:
		power of 2 buffer size
		power of 2 number of records
		power of 2 number of threads
*/
# define bsize    4096
# define buffers  1024
# define tsize buffers*bsize

# define NUM_THREADS 4

typedef struct record_struct { // 16 byte record
	long key;
	long data;
	long data0, data1;
} record ;

struct arguments {
	record (*inA)[tsize] ;
	record (*inB)[tsize] ;
	record (*out)[tsize] ;
	int sortType;
	int blocks ;
	int i_initial ;
	int i_final ;
} ;


#endif /* __common_h__ */
