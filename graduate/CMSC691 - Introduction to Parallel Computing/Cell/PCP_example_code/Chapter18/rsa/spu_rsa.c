#include <stdio.h>
#include <libmpm.h>
#include <spu_intrinsics.h>

int main(int argc, char **argv) {

   vector unsigned int plain_text[12], cipher_text[12], result_text[12];
   vector unsigned int one_vec = {0, 0, 0, 1};
   int i, j; 

   /* These prime numbers were patented by Roger Schafly, who seems like a thoughtful person
      and not at all like the kind of guy who'd sue a poor author for infringement */
   vector unsigned int p_vec[4], q_vec[8];      
   p_vec[0] = (vector unsigned int) {0x98a3df52, 0xaeae9799, 0x325cb258, 0xd767ebd1};
   p_vec[1] = (vector unsigned int) {0xf4630e9b, 0x9e21732a, 0x4afb1624, 0xba6df911};
   p_vec[2] = (vector unsigned int) {0x466ad8da, 0x960586f4, 0xa0d5e3c3, 0x6af09966};
   p_vec[3] = (vector unsigned int) {0x0bddc157, 0x7e54a9f4, 0x02334433, 0xacb14bcb};

   q_vec[0] = (vector unsigned int) {0x93e8965d, 0xafd9dfec, 0xfd00b466, 0xb68f90ea};
   q_vec[1] = (vector unsigned int) {0x68af5dc9, 0xfed91527, 0x8d1b3a13, 0x7471e655};
   q_vec[2] = (vector unsigned int) {0x96c37fed, 0x0c7829ff, 0x8f8331f8, 0x1a270043};
   q_vec[3] = (vector unsigned int) {0x8ecdcc09, 0x447dc397, 0xc685f397, 0x294f722b};
   q_vec[4] = (vector unsigned int) {0xcc484aed, 0xf28bed25, 0xaaab35d3, 0x5a65db1f};
   q_vec[5] = (vector unsigned int) {0xd62c9d7b, 0xa55844fe, 0xb1f9401e, 0x67134093};
   q_vec[6] = (vector unsigned int) {0x3ee43c54, 0xe4dc4594, 0x00d7ad61, 0x248b83a2};
   q_vec[7] = (vector unsigned int) {0x624835b3, 0x1fff2d95, 0x95a5b90b, 0x276e44f9};

   /* Initialize the arrays */
   for(i=0; i<12; i++) {
      plain_text[i] = (vector unsigned int) {0, 0, 0, 0};
      cipher_text[i] = (vector unsigned int) {0, 0, 0, 0};
      result_text[i] = (vector unsigned int) {0, 0, 0, 0};
   }
   
   /* Set the message */
   plain_text[0] = (vector unsigned int) 
      {0x01234567, 0, 0, 0x89abcdef};
      
   /* Step 1: Calculate the product of the primes */
   vector unsigned int n[12];
   mpm_mul(n, p_vec, 4, q_vec, 8);

   /* Step 2: Compute m = (p-1)(q-1) */
   vector unsigned int m[12];
   mpm_sub2(p_vec, p_vec, 4, &one_vec, 1);
   mpm_sub2(q_vec, q_vec, 8, &one_vec, 1);   
   mpm_mul(m, p_vec, 4, q_vec, 8);
   
   /* Step 3: Find an integer e<m such that gcd(e, m) = 1 */
   vector unsigned int e = (vector unsigned int)
      {0, 0, 0, 0x10001};
   
   /* Step 4: Compute d such that de mod m = 1 */
   vector unsigned int d[12];
   mpm_mul_inv2(d, m, 12, &e, 1);
   
   /* Step 5: Encrypt the message */
   mpm_mod_exp(cipher_text, plain_text, &e, 1, n, 12, 2); 
   
   /* Step 6: Decrypt the message */
   mpm_mod_exp(result_text, cipher_text, d, 12, n, 12, 2);
   
   /* Display results */
   printf("Result text:\n");
   for(i=0; i<12; i++) {
      for(j=0; j<4; j++) {
         printf("%#08x ", spu_extract(result_text[i], j));
      }
      printf("\n");
   }
   return 0;
}
