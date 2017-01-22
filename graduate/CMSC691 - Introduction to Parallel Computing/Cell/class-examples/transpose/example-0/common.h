#ifndef __common_h__
#define __common_h__

/* This union helps clarify calling parameters between the PPE and the SPE. */

typedef union
{
  unsigned long long ull;
  unsigned int ui[2];
  void *p;
} addr64;


#endif /* __common_h__ */
