	.set	noreorder
	.set	noat
	#	/usr/lib32/cmplrs/be
	#ident	"$Source: /hosts/bonnie.engr/depot/cmplrs.src/v7.2.1.3m/be/RCS/version.c,v $ $Revision: 3.0 $"
	#ism	1275237310

	#-----------------------------------------------------------
	# Compiling matmul2.c (/tmp/ctmB.BAAa02BGi)
	#-----------------------------------------------------------

	#-----------------------------------------------------------
	# Options:
	#-----------------------------------------------------------
	#  Target:R4000, ISA:mips3, Pointer Size:32
	#  -O3	(Optimization level)
	#  -g3	(Debug level)
	#  -m1	(Report warnings)
	#-----------------------------------------------------------

	.file	1	"/afs/umbc.edu/users/t/r/tri1/home/411/matmul2.c"

	.section .text, 1, 0x00000006, 4, 4
.text:

	.section .rodata, 1, 0x00000002, 0, 8
.rodata:

	.section .lit8, 1, 0x30000002, 8, 8
.lit8:
	.section .text

	# Program Unit: main
	.ent	main
	.globl	main
main: 	 # 0x0
	.frame	$30, 80, $31
	.mask	0x80000000, -24
.BB1.main: 	 # 0x0
 #<freq>
 #<freq> BB:1 frequency = 1.00000 (heuristic)
 #<freq>
	.loc	1 5 1
 #   1  /* matmul2.c  100*100 matrix element by element multiply */
 #   2  #include <stdio.h>
 #   3  
 #   4  int main()
 #   5  {
	or $7,$30,$0                  	# [0]  
	addiu $sp,$sp,-80             	# [1]  .frame.len.main
	addiu $30,$sp,80              	# [2]  .frame.len.main
	sd $7,-48($30)                	# [3]  .gra_spill_b006
	sd $31,-24($30)               	# [4]  .gra_spill_b003
	sd $16,-16($30)               	# [5]  .gra_spill_b002
	sd $17,-40($30)               	# [6]  .gra_spill_b005
	sd $18,-56($30)               	# [7]  .gra_spill_b007
	lui $5,-2                     	# [8]  
	ori $5,$5,51072               	# [9]  
	addu $sp,$5,$sp               	# [10]  
	.loc	1 7 10
 #   6    const int N = 100;
 #   7    double a[N][N]; /* input matrix */
	or $18,$sp,$0                 	# [11]  
	addu $sp,$5,$sp               	# [12]  
	.loc	1 8 10
 #   8    double b[N][N]; /* input matrix */
	or $17,$sp,$0                 	# [13]  
	addu $sp,$5,$sp               	# [14]  
	.loc	1 5 1
	lui $6,%hi(%neg(%gp_rel(main +0)))	# [15]  
	addiu $6,$6,%lo(%neg(%gp_rel(main +0)))	# [16]  
	sd $gp,-32($30)               	# [17]  .gra_spill_b004
	addu $gp,$25,$6               	# [18]  
	lw $25,%got_disp(printf)($gp) 	# [19]  
	.loc	1 12 3
 #   9    double c[N][N]; /* result matrix */
 #  10    int i,j;
 #  11  
 #  12    printf("starting multiply \n");
	lw $4,%got_page(.rodata)($gp) 	# [20]  
	.loc	1 9 10
	or $16,$sp,$0                 	# [21]  
	.loc	1 12 3
	jalr $25                      	# [22]  printf
	addiu $4,$4,%got_ofst(.rodata)	# [23]  
.BB2.main: 	 # 0x60
 #<freq>
 #<freq> BB:2 frequency = 1.00000 (heuristic)
 #<freq>
	lw $14,%got_disp(printf)($gp) 	# [0]  
	.loc	1 16 3
 #  13    a[1][1] = 3.5;
 #  14    b[1][1] =1.2; /* not a valid benchmark, most elements zero */
 #  15  
 #  16    for(i=0; i<N; i++){
	addiu $10,$18,800             	# [1]  
	or $11,$18,$0                 	# [2]  
	or $9,$0,$0                   	# [3]  
	or $13,$0,$0                  	# [4]  
	.loc	1 14 3
	ldc1 $f1,%gp_rel(.lit8-30712)($gp)	# [5]  
	.loc	1 13 3
	ldc1 $f0,%gp_rel(.lit8-30720)($gp)	# [6]  
	.loc	1 16 3
	or $12,$17,$0                 	# [7]  
	.loc	1 14 3
	sdc1 $f1,808($17)             	# [8]  
	.loc	1 13 3
	sdc1 $f0,808($18)             	# [9]  
.L.1.9.temp: 	 # 0x88
 #<loop> Loop body line 16, nesting depth: 1, iterations: 14
 #<swp> 
 #<swp> Pipelined loop line 16 windup (fill)
 #<swp> 
 #<sched> 
 #<sched> Loop schedule length: 87 cycles (ignoring nested loops)
 #<sched> 
 #<sched>    17 flops        ( 19% of peak)
 #<sched>    14 fmuls        ( 62% of peak)
 #<sched>     0 fadds        (  0% of peak)
 #<sched>    46 mem refs     ( 52% of peak)
 #<sched>    15 integer ops  ( 17% of peak)
 #<sched>    78 instructions ( 89% of peak)
 #<sched> 
 #<freq>
 #<freq> BB:3 frequency = 14.00000 (heuristic)
 #<freq>
	.loc	1 19 9
 #  17      for(j=0; j<N; j++){
 #  18  front:
 #  19          c[i][j] = a[i][j]*b[i][j]; /* most time spent here! */
	ldc1 $f3,3200($12)            	# [0]  
	ldc1 $f0,4000($11)            	# [1]  
	ldc1 $f5,4000($12)            	# [2]  
	ldc1 $f9,4808($12)            	# [3]  
	.loc	1 16 3
	addu $1,$9,$16                	# [4]  
	or $2,$12,$0                  	# [5]  
	addiu $12,$12,5600            	# [6]  
	.loc	1 19 9
	ldc1 $f7,-4800($12)           	# [7]  
	ldc1 $f6,800($11)             	# [8]  
	or $3,$11,$0                  	# [9]  
	ldc1 $f8,-800($12)            	# [10]  
	mul.d $f6,$f6,$f7             	# [11]  
	ldc1 $f7,4800($11)            	# [12]  
	addiu $4,$10,-16              	# [13]  
	.loc	1 16 3
	addiu $10,$10,5600            	# [14]  
	.loc	1 19 9
	mul.d $f7,$f7,$f8             	# [15]  
	b .BB12.main                  	# [16]  
	addiu $4,$4,-16               	# [17]  
.BB11.main: 	 # 0xd0
 #<loop> Part of loop body line 16, head labeled .BB12.main
 #<swp> 
 #<swp> Pipelined loop line 16 replication 2
 #<swp> 
 #<freq>
 #<freq> BB:11 frequency = 457.33334 (heuristic)
 #<freq>
	mul.d $f8,$f3,$f6             	# [0]  
	ldc1 $f3,3216($3)             	# [1]  
	ldc1 $f7,2416($2)             	# [2]  
	ldc1 $f1,2416($3)             	# [3]  
	mul.d $f6,$f3,$f2             	# [4]  
	sdc1 $f0,816($1)              	# [5]  
	sdc1 $f5,4816($1)             	# [6]  
	ldc1 $f3,1616($2)             	# [7]  
	mul.d $f2,$f1,$f7             	# [8]  
	ldc1 $f1,1616($3)             	# [9]  
	sdc1 $f8,4016($1)             	# [10]  
	ldc1 $f0,4824($3)             	# [11]  
	mul.d $f3,$f1,$f3             	# [12]  
	sdc1 $f6,3216($1)             	# [13]  
	ldc1 $f9,4832($2)             	# [14]  
	ldc1 $f1,16($2)               	# [15]  
	mul.d $f7,$f0,$f4             	# [16]  
	ldc1 $f0,16($3)               	# [17]  
	sdc1 $f2,2416($1)             	# [18]  
	ldc1 $f5,4024($2)             	# [19]  
	mul.d $f4,$f0,$f1             	# [20]  
	ldc1 $f2,824($2)              	# [21]  
	ldc1 $f1,824($3)              	# [22]  
	sdc1 $f3,1616($1)             	# [23]  
	ldc1 $f0,4024($3)             	# [24]  
	mul.d $f6,$f1,$f2             	# [25]  
	ldc1 $f3,3224($2)             	# [26]  
	.loc	1 17 5
	addiu $1,$1,24                	# [27]  
	addiu $2,$2,24                	# [28]  
	addiu $3,$3,24                	# [29]  
	.loc	1 19 9
	sdc1 $f4,-8($1)               	# [31]  
.BB12.main: 	 # 0x14c
 #<loop> Loop body line 16, nesting depth: 2, estimated iterations: 33
 #<swps> 
 #<swps> Pipelined loop line 16 steady state
 #<swps> 
 #<swps>   100 iterations before pipelining
 #<swps>       Not unrolled before pipelining
 #<swps>    29 cycles per iteration
 #<swps>     7 flops        ( 24% of peak)
 #<swps>     7 fmuls        ( 87% of peak)
 #<swps>     0 fadds        (  0% of peak)
 #<swps>    21 mem refs     ( 72% of peak)
 #<swps>     1 integer op   (  3% of peak)
 #<swps>    29 instructions (100% of peak)
 #<swps>     2 short trip threshold
 #<swps>     6 integer registers used.
 #<swps>    11 float registers used.
 #<swps> 

 #<swp> 
 #<swp> Pipelined loop line 16 replication 0
 #<swp> 
 #<freq>
 #<freq> BB:12 frequency = 471.33334 (heuristic)
 #<freq>
	mul.d $f5,$f0,$f5             	# [0]  
	ldc1 $f2,3200($3)             	# [1]  
	ldc1 $f1,2400($2)             	# [2]  
	ldc1 $f0,2400($3)             	# [3]  
	mul.d $f4,$f2,$f3             	# [4]  
	sdc1 $f6,800($1)              	# [5]  
	sdc1 $f7,4800($1)             	# [6]  
	ldc1 $f3,1600($2)             	# [7]  
	mul.d $f2,$f0,$f1             	# [8]  
	ldc1 $f1,1600($3)             	# [9]  
	sdc1 $f5,4000($1)             	# [10]  
	ldc1 $f0,4808($3)             	# [11]  
	mul.d $f3,$f1,$f3             	# [12]  
	sdc1 $f4,3200($1)             	# [13]  
	ldc1 $f8,4816($2)             	# [14]  
	ldc1 $f1,0($2)                	# [15]  
	mul.d $f7,$f0,$f9             	# [16]  
	ldc1 $f0,0($3)                	# [17]  
	sdc1 $f2,2400($1)             	# [18]  
	ldc1 $f5,4008($2)             	# [19]  
	mul.d $f4,$f0,$f1             	# [20]  
	ldc1 $f2,808($2)              	# [21]  
	ldc1 $f1,808($3)              	# [22]  
	sdc1 $f3,1600($1)             	# [23]  
	ldc1 $f0,4008($3)             	# [24]  
	mul.d $f6,$f1,$f2             	# [25]  
	ldc1 $f3,3208($2)             	# [26]  
	sdc1 $f4,0($1)                	# [28]  
.BB13.main: 	 # 0x1bc
 #<loop> Part of loop body line 16, head labeled .BB12.main
 #<swp> 
 #<swp> Pipelined loop line 16 replication 1
 #<swp> 
 #<freq>
 #<freq> BB:13 frequency = 471.33334 (heuristic)
 #<freq> BB:13 => BB:11 probability = 0.97030
 #<freq> BB:13 => BB:15 probability = 0.02970
 #<freq>
	mul.d $f5,$f0,$f5             	# [0]  
	ldc1 $f2,3208($3)             	# [1]  
	ldc1 $f1,2408($2)             	# [2]  
	ldc1 $f0,2408($3)             	# [3]  
	mul.d $f4,$f2,$f3             	# [4]  
	sdc1 $f6,808($1)              	# [5]  
	sdc1 $f7,4808($1)             	# [6]  
	ldc1 $f2,1608($2)             	# [7]  
	mul.d $f3,$f0,$f1             	# [8]  
	ldc1 $f1,1608($3)             	# [9]  
	sdc1 $f5,4008($1)             	# [10]  
	ldc1 $f0,4816($3)             	# [11]  
	mul.d $f2,$f1,$f2             	# [12]  
	sdc1 $f4,3208($1)             	# [13]  
	ldc1 $f4,4824($2)             	# [14]  
	ldc1 $f1,8($2)                	# [15]  
	mul.d $f5,$f0,$f8             	# [16]  
	ldc1 $f0,8($3)                	# [17]  
	sdc1 $f3,2408($1)             	# [18]  
	ldc1 $f6,4016($2)             	# [19]  
	mul.d $f1,$f0,$f1             	# [20]  
	ldc1 $f0,816($2)              	# [21]  
	ldc1 $f7,816($3)              	# [22]  
	sdc1 $f2,1608($1)             	# [23]  
	ldc1 $f3,4016($3)             	# [24]  
	mul.d $f0,$f7,$f0             	# [25]  
	ldc1 $f2,3216($2)             	# [26]  
	.loc	1 17 5
	bne $3,$4,.BB11.main          	# [27]  
	.loc	1 19 9
	sdc1 $f1,8($1)                	# [28]  
.BB15.main: 	 # 0x230
 #<loop> Part of loop body line 16, head labeled .L.1.9.temp
 #<swp> 
 #<swp> Pipelined loop line 16 exit compensation for replication 1
 #<swp> 
 #<swp> 
 #<swp> Pipelined loop line 16 winddown (drain)
 #<swp> 
 #<freq>
 #<freq> BB:15 frequency = 14.00000 (heuristic)
 #<freq> BB:15 => BB:3 probability = 0.92857
 #<freq> BB:15 => BB:6 probability = 0.07143
 #<freq>
	.loc	1 16 3
	addiu $13,$13,7               	# [15]  
	or $6,$1,$0                   	# [0]  
	or $7,$3,$0                   	# [1]  
	.loc	1 19 9
	ldc1 $f1,3216($7)             	# [2]  
	sdc1 $f11,-72($30)            	# [3]  .gra_spill_b009
	mov.d $f11,$f5                	# [4]  
	mul.d $f1,$f1,$f2             	# [5]  
	or $4,$2,$0                   	# [6]  
	ldc1 $f9,2416($4)             	# [7]  
	mov.d $f7,$f6                 	# [8]  
	mul.d $f2,$f3,$f7             	# [9]  
	ldc1 $f8,2416($7)             	# [10]  
	sdc1 $f11,4816($6)            	# [11]  
	sdc1 $f0,816($6)              	# [12]  
	ldc1 $f0,1616($4)             	# [14]  
	ldc1 $f11,1616($7)            	# [15]  
	mul.d $f8,$f8,$f9             	# [16]  
	sdc1 $f2,4016($6)             	# [17]  
	ldc1 $f9,4824($7)             	# [19]  
	sdc1 $f1,3216($6)             	# [20]  
	mul.d $f11,$f11,$f0           	# [21]  
	ldc1 $f7,16($4)               	# [22]  
	ldc1 $f3,16($7)               	# [23]  
	sdc1 $f8,2416($6)             	# [24]  
	ldc1 $f1,824($4)              	# [26]  
	mul.d $f3,$f3,$f7             	# [27]  
	ldc1 $f0,824($7)              	# [28]  
	sdc1 $f10,-64($30)            	# [30]  .gra_spill_b008
	mul.d $f0,$f0,$f1             	# [31]  
	mov.d $f10,$f4                	# [32]  
	ldc1 $f1,4024($4)             	# [33]  
	sdc1 $f11,1616($6)            	# [34]  
	mul.d $f9,$f9,$f10            	# [35]  
	ldc1 $f11,4024($7)            	# [36]  
	ldc1 $f2,3224($4)             	# [37]  
	sdc1 $f3,16($6)               	# [38]  
	ldc1 $f8,2424($4)             	# [40]  
	ldc1 $f7,2424($7)             	# [41]  
	mul.d $f11,$f11,$f1           	# [42]  
	ldc1 $f10,3224($7)            	# [43]  
	sdc1 $f0,824($6)              	# [44]  
	sdc1 $f9,4824($6)             	# [45]  
	mul.d $f10,$f10,$f2           	# [46]  
	ldc1 $f9,1624($4)             	# [47]  
	ldc1 $f3,1624($7)             	# [48]  
	mul.d $f3,$f3,$f9             	# [51]  
	sdc1 $f11,4024($6)            	# [53]  
	sdc1 $f10,3224($6)            	# [54]  
	mul.d $f7,$f7,$f8             	# [55]  
	ldc1 $f8,24($4)               	# [56]  
	ldc1 $f2,24($7)               	# [57]  
	.loc	1 16 3
	addiu $11,$11,5600            	# [59]  
	.loc	1 19 9
	mul.d $f2,$f2,$f8             	# [60]  
	.loc	1 16 3
	addiu $9,$9,5600              	# [61]  
	slti $5,$13,94                	# [62]  
	ldc1 $f11,-72($30)            	# [63]  .gra_spill_b009
	ldc1 $f10,-64($30)            	# [64]  .gra_spill_b008
	.loc	1 19 9
	sdc1 $f7,2424($6)             	# [65]  
	sdc1 $f3,1624($6)             	# [66]  
	.loc	1 16 3
	bne $5,$0,.L.1.9.temp         	# [67]  
	.loc	1 19 9
	sdc1 $f2,24($6)               	# [68]  
.L.1.14.temp: 	 # 0x324
.L.1.7.temp: 	 # 0x324
 #<swp> 
 #<swp> Pipelined loop line 16 windup (fill)
 #<swp> 
 #<freq>
 #<freq> BB:6 frequency = 1.00000 (heuristic)
 #<freq>
	.loc	1 16 3
	lui $4,1                      	# [0]  
	addu $2,$4,$17                	# [1]  
	ld $17,-40($30)               	# [2]  .gra_spill_b005
	addiu $5,$18,800              	# [3]  
	addu $3,$4,$18                	# [4]  
	ld $18,-56($30)               	# [5]  .gra_spill_b007
	.loc	1 19 9
	ldc1 $f4,13680($2)            	# [6]  
	ldc1 $f0,12888($3)            	# [7]  
	ldc1 $f5,12888($2)            	# [8]  
	ldc1 $f8,13720($2)            	# [9]  
	ldc1 $f7,13664($2)            	# [10]  
	ldc1 $f6,13664($3)            	# [11]  
	.loc	1 16 3
	addu $1,$4,$16                	# [12]  
	.loc	1 19 9
	ldc1 $f9,13688($2)            	# [13]  
	mul.d $f6,$f6,$f7             	# [14]  
	ldc1 $f7,13688($3)            	# [15]  
	.loc	1 16 3
	addu $4,$4,$5                 	# [16]  
	addiu $4,$4,-64               	# [17]  
	.loc	1 19 9
	mul.d $f7,$f7,$f9             	# [18]  
	b .BB19.main                  	# [19]  
	addiu $4,$4,-32               	# [20]  
.BB18.main: 	 # 0x378
 #<loop> Part of loop body line 16, head labeled .BB19.main
 #<loop> Unrolled 4 times
 #<swp> 
 #<swp> Pipelined loop line 16 replication 1
 #<swp> 
 #<freq>
 #<freq> BB:18 frequency = 12.00000 (heuristic)
 #<freq>
	mul.d $f8,$f3,$f6             	# [0]  
	ldc1 $f1,13712($3)            	# [1]  
	ldc1 $f7,12912($2)            	# [2]  
	ldc1 $f3,12912($3)            	# [3]  
	mul.d $f6,$f1,$f2             	# [4]  
	sdc1 $f0,13696($1)            	# [5]  
	sdc1 $f5,13720($1)            	# [6]  
	ldc1 $f1,13704($2)            	# [7]  
	mul.d $f5,$f3,$f7             	# [8]  
	ldc1 $f0,13704($3)            	# [9]  
	sdc1 $f8,12920($1)            	# [10]  
	ldc1 $f3,12904($2)            	# [11]  
	mul.d $f2,$f0,$f1             	# [12]  
	ldc1 $f1,12904($3)            	# [13]  
	sdc1 $f6,13712($1)            	# [14]  
	ldc1 $f0,13752($3)            	# [15]  
	mul.d $f6,$f1,$f3             	# [16]  
	sdc1 $f5,12912($1)            	# [17]  
	ldc1 $f8,13784($2)            	# [18]  
	ldc1 $f1,12896($2)            	# [19]  
	mul.d $f7,$f0,$f4             	# [20]  
	ldc1 $f0,12896($3)            	# [21]  
	sdc1 $f2,13704($1)            	# [22]  
	ldc1 $f5,12952($2)            	# [23]  
	mul.d $f3,$f0,$f1             	# [24]  
	ldc1 $f2,13728($2)            	# [25]  
	ldc1 $f1,13728($3)            	# [26]  
	sdc1 $f6,12904($1)            	# [27]  
	ldc1 $f0,12952($3)            	# [28]  
	mul.d $f6,$f1,$f2             	# [29]  
	ldc1 $f4,13744($2)            	# [30]  
	.loc	1 17 5
	addiu $1,$1,64                	# [31]  
	addiu $2,$2,64                	# [32]  
	addiu $3,$3,64                	# [33]  
	.loc	1 19 9
	sdc1 $f3,12832($1)            	# [35]  
.BB19.main: 	 # 0x404
 #<loop> Loop body line 16, nesting depth: 1, estimated iterations: 12
 #<loop> Unrolled 4 times
 #<swps> 
 #<swps> Pipelined loop line 16 steady state
 #<swps> 
 #<swps>    25 iterations before pipelining
 #<swps>     4 unrollings before pipelining
 #<swps>    33 cycles per 4 iterations
 #<swps>     8 flops        ( 24% of peak)
 #<swps>     8 fmuls        ( 88% of peak)
 #<swps>     0 fadds        (  0% of peak)
 #<swps>    24 mem refs     ( 72% of peak)
 #<swps>     1 integer op   (  3% of peak)
 #<swps>    33 instructions (100% of peak)
 #<swps>     2 short trip threshold
 #<swps>     5 integer registers used.
 #<swps>    11 float registers used.
 #<swps> 

 #<swp> 
 #<swp> Pipelined loop line 16 replication 0
 #<swp> 
 #<freq>
 #<freq> BB:19 frequency = 13.00000 (heuristic)
 #<freq> BB:19 => BB:18 probability = 0.92308
 #<freq> BB:19 => BB:21 probability = 0.07692
 #<freq>
	mul.d $f3,$f0,$f5             	# [0]  
	ldc1 $f1,13680($3)            	# [1]  
	ldc1 $f2,12880($2)            	# [2]  
	ldc1 $f0,12880($3)            	# [3]  
	mul.d $f5,$f1,$f4             	# [4]  
	sdc1 $f6,13664($1)            	# [5]  
	sdc1 $f7,13688($1)            	# [6]  
	ldc1 $f1,13672($2)            	# [7]  
	mul.d $f4,$f0,$f2             	# [8]  
	ldc1 $f0,13672($3)            	# [9]  
	sdc1 $f3,12888($1)            	# [10]  
	ldc1 $f2,12872($2)            	# [11]  
	mul.d $f3,$f0,$f1             	# [12]  
	ldc1 $f1,12872($3)            	# [13]  
	sdc1 $f5,13680($1)            	# [14]  
	ldc1 $f0,13720($3)            	# [15]  
	mul.d $f2,$f1,$f2             	# [16]  
	sdc1 $f4,12880($1)            	# [17]  
	ldc1 $f4,13752($2)            	# [18]  
	ldc1 $f1,12864($2)            	# [19]  
	mul.d $f5,$f0,$f8             	# [20]  
	ldc1 $f0,12864($3)            	# [21]  
	sdc1 $f3,13672($1)            	# [22]  
	ldc1 $f6,12920($2)            	# [23]  
	mul.d $f1,$f0,$f1             	# [24]  
	ldc1 $f0,13696($2)            	# [25]  
	ldc1 $f7,13696($3)            	# [26]  
	sdc1 $f2,12872($1)            	# [27]  
	ldc1 $f3,12920($3)            	# [28]  
	mul.d $f0,$f7,$f0             	# [29]  
	ldc1 $f2,13712($2)            	# [30]  
	.loc	1 17 5
	bne $3,$4,.BB18.main          	# [31]  
	.loc	1 19 9
	sdc1 $f1,12864($1)            	# [32]  
.BB21.main: 	 # 0x488
 #<swp> 
 #<swp> Pipelined loop line 16 exit compensation for replication 0
 #<swp> 
 #<swp> 
 #<swp> Pipelined loop line 16 winddown (drain)
 #<swp> 
 #<freq>
 #<freq> BB:21 frequency = 1.00000 (heuristic)
 #<freq>
	mov.d $f1,$f2                 	# [0]  
	mov.d $f7,$f6                 	# [1]  
	mov.d $f6,$f3                 	# [2]  
	mul.d $f2,$f6,$f7             	# [3]  
	mov.d $f3,$f0                 	# [4]  
	ldc1 $f0,12912($2)            	# [5]  
	ldc1 $f31,12912($3)           	# [6]  
	mul.d $f31,$f31,$f0           	# [9]  
	ldc1 $f0,13712($3)            	# [10]  
	sdc1 $f5,13720($1)            	# [11]  
	sdc1 $f3,13696($1)            	# [12]  
	mul.d $f0,$f0,$f1             	# [13]  
	ldc1 $f29,13704($3)           	# [15]  
	ldc1 $f1,13704($2)            	# [16]  
	sdc1 $f2,12920($1)            	# [17]  
	ldc1 $f25,12904($3)           	# [19]  
	ldc1 $f27,12904($2)           	# [20]  
	sdc1 $f0,13712($1)            	# [21]  
	ldc1 $f17,13752($3)           	# [23]  
	mul.d $f17,$f17,$f4           	# [26]  
	mul.d $f29,$f29,$f1           	# [30]  
	sdc1 $f31,12912($1)           	# [33]  
	mul.d $f25,$f25,$f27          	# [34]  
	ldc1 $f23,12896($3)           	# [35]  
	ldc1 $f27,12896($2)           	# [36]  
	sdc1 $f29,13704($1)           	# [38]  
	mul.d $f23,$f23,$f27          	# [39]  
	ldc1 $f18,13728($3)           	# [40]  
	ldc1 $f19,13728($2)           	# [41]  
	ldc1 $f16,12952($2)           	# [42]  
	sdc1 $f25,12904($1)           	# [43]  
	mul.d $f18,$f18,$f19          	# [44]  
	ldc1 $f15,12952($3)           	# [45]  
	ldc1 $f21,13744($2)           	# [46]  
	sdc1 $f23,12896($1)           	# [47]  
	mul.d $f15,$f15,$f16          	# [48]  
	ldc1 $f13,12944($3)           	# [49]  
	ldc1 $f16,12944($2)           	# [50]  
	ldc1 $f14,13744($3)           	# [51]  
	sdc1 $f17,13752($1)           	# [52]  
	mul.d $f13,$f13,$f16          	# [53]  
	sdc1 $f18,13728($1)           	# [54]  
	ldc1 $f11,13736($3)           	# [56]  
	mul.d $f14,$f14,$f21          	# [57]  
	ldc1 $f12,13736($2)           	# [58]  
	sdc1 $f15,12952($1)           	# [60]  
	mul.d $f11,$f11,$f12          	# [61]  
	ldc1 $f10,12936($3)           	# [62]  
	ldc1 $f12,12936($2)           	# [63]  
	sdc1 $f13,12944($1)           	# [64]  
	sdc1 $f14,13744($1)           	# [65]  
	mul.d $f10,$f10,$f12          	# [66]  
	ldc1 $f12,12928($2)           	# [67]  
	ldc1 $f9,12928($3)            	# [68]  
	mul.d $f9,$f9,$f12            	# [71]  
	sdc1 $f11,13736($1)           	# [77]  
	sdc1 $f10,12936($1)           	# [78]  
	sdc1 $f9,12928($1)            	# [79]  
	.loc	1 23 3
 #  20  back:;
 #  21      }
 #  22    }
 #  23    printf("a result %g \n", c[1][1]); /* prevent dead code elimination */
	ldc1 $f8,808($16)             	# [81]  
	or $25,$14,$0                 	# [82]  
	lw $4,%got_page(.rodata+24)($gp)	# [83]  
	dmfc1 $5,$f8                  	# [84]  
	jalr $14                      	# [85]  printf
	addiu $4,$4,%got_ofst(.rodata+24)	# [86]  
.BB9.main: 	 # 0x588
 #<freq>
 #<freq> BB:9 frequency = 1.00000 (heuristic)
 #<freq>
	.loc	1 24 3
 #  24    return 0;
	or $2,$0,$0                   	# [0]  
	ld $gp,-32($30)               	# [1]  .gra_spill_b004
	ld $16,-16($30)               	# [2]  .gra_spill_b002
	ld $31,-24($30)               	# [3]  .gra_spill_b003
	ld $5,-48($30)                	# [4]  .gra_spill_b006
	or $sp,$30,$0                 	# [5]  
	jr $31                        	# [6]  
	or $30,$5,$0                  	# [7]  
	.end	main

	.section .lit8
	.origin 0x8
	.align	0
	# offset 8
	.dword	0x3ff3333333333333  	# double 1.20000
	.origin 0x0
	.align	0
	# offset 0
	.dword	0x400c000000000000  	# double 3.50000

	.section .rodata
	.origin 0x0
	.align	0
	# offset 0
	.byte	0x73, 0x74, 0x61, 0x72, 0x74, 0x69, 0x6e, 0x67 	# starting
	.byte	0x20, 0x6d, 0x75, 0x6c, 0x74, 0x69, 0x70, 0x6c 	#  multipl
	.byte	0x79, 0x20, 0xa, 0x0 	# y \n\000
	.origin 0x18
	.align	0
	# offset 24
	.byte	0x61, 0x20, 0x72, 0x65, 0x73, 0x75, 0x6c, 0x74 	# a result
	.byte	0x20, 0x25, 0x67, 0x20, 0xa, 0x0 	#  %g \n\000
	.section .text
	.align 2
	.section .rodata
	.align 3
	.section .lit8
	.align 3
	.gpvalue 30720
