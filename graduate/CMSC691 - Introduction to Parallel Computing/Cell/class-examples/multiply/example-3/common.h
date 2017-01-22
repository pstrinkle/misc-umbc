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
//# define tsize 128*32

# define stsize 32
# define tsize 64*stsize
# define loops 1

struct arguments {
	float (*Amat) [tsize][tsize] ;
	float (*Bmat) [tsize][tsize] ;
	float (*Cmat) [tsize][tsize] ;
	int i_initial ;
	int i_final ;
} ;


#endif /* __common_h__ */
