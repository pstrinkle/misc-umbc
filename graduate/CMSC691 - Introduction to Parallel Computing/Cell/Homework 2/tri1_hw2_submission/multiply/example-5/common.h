#ifndef __common_h__
#define __common_h__

/* This union helps clarify calling parameters between the PPE and the SPE. */

typedef union
{
      unsigned long long ull;
      unsigned int ui[2];
      void *p;
} addr64;

#define stsize 32
#define tsize  2 * stsize

#define NUM_THREADS 2

struct arguments
{
      float (*Amat) [tsize][tsize] ;
      float (*Bmat) [tsize][tsize] ;
      float (*Cmat) [tsize][tsize] ;
      int i_initial ;
      int i_final ;
};


#endif /* __common_h__ */
