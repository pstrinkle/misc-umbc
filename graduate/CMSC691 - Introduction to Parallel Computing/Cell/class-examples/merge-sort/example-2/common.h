#ifndef __common_h__
#define __common_h__

/* This union helps clarify calling parameters between the PPE and the SPE. */

typedef union
{
  unsigned long long ull;
  unsigned int ui[2];
  void *p;
} addr64;

// total 1000*1000 = 4,000,000 B
// total 4000*4000 = 64,000,000 B
# define stsize 4096
# define tsize 1*stsize
# define loops 1
# define NUM_THREADS 1

typedef struct record_struct {
	long key;
	long data;
} record ;

struct arguments {
	record (*initial)[tsize] ;
	record (*final)  [tsize] ;
	int i_initial ;
	int i_final ;
} ;


#endif /* __common_h__ */
