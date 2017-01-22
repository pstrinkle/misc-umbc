	.file	"merge_spu_p1.c"
.text
	.align	3
	.global	phase1
	.type	phase1, @function
phase1:
# setup of subroutine
	stqd	$sp,-192($sp)
	ai	$sp,$sp,-192

	lqd	$2,32($sp)
	cwd	$5,0($sp)
	shufb	$2,$3,$2,$5
	stqd	$2,32($sp)

	lqd	$2,48($sp)
	cwd	$3,0($sp)
	shufb	$2,$4,$2,$3
	stqd	$2,48($sp)
	
#  j --> $10
#  k --> $11

#  k2 --> $12
#  j1 --> $13
#  j2 --> $14
#  j3 --> $15

#  bsize --> $16

#  j+k   --> $17
#  j+k2  --> $18

#  array0 --> $19
#  array1 --> $20
#  array2 --> $21

#  array0,j1 --> $22
#  array0,j2 --> $23
#  array1,j3 --> $24
	
#  [array0,j1] --> $25
#  [array0,j2] --> $26




#				array0 = A0;  array1 = A1;
	lqd	$19,32($sp)
	lqd	$20,48($sp)
	il	$16,2048	# bsize
	il	$27,16

#				for(k=2; k<=bsize; k<<=1 )
	il	$11,2	# k
	il	$12,1	# k2
.L3:
	cgt	$2,$11,$16
	brnz	$2,.L4
#					array2 = array0 ;  array0 = array1 ;  array1 = array2 ;
	ori	$21,$19,0
	ori	$19,$20,0
	ori	$20,$21,0
	
#					for(j=0; j<bsize; j+=k )
	il	$10,0
.L5:
	cgt	$2,$16,$10
	brz	$2,.L6
#						j1=j; j2=j+k2;  j3=j;
	ori	$13,$10,0	# j1
	a	$14,$10,$12	# j2 = j+k2
	ori	$15,$10,0	# j3
	a	$17,$10,$11	# j+k
	ori	$18,$14,0	# j+k2

#	mpya	$22,$13,$27,$19	# array0,j1
#	mpya	$23,$14,$27,$19	# array0,j1
#	mpya	$24,$15,$27,$20	# array0,j1
#	lqd	$25,0($22)	# [array0,j1]
#	lqd	$26,0($23)	# [array0,j2]
	
	shli	$3,$13,4
	shli	$4,$13,4
	shli	$5,$13,4
	a	$22,$3,$19
	a	$23,$4,$19
	lqd	$25,0($22)	# [array0,j1]
	a	$24,$5,$20
	lqd	$26,0($23)	# [array0,j2]


#						while ( j1<j+k2 && j2<j+k )
.L7:
	cgt	$2,$18,$13
	cgt	$3,$17,$14
	and	$2,$3,$2
	brz	$2,.L8
#							if ( (*array0)[j1].key > (*array0)[j2].key )
	cgt	$2,$25,$26
	brz	$2,.L9
#								(*array1)[j3] = (*array0)[j1]; j3++; j1++;
	ai	$22,$22,16
	ai	$13,$13,1
	stqd	$25,0($24)	# [array1,j3]
	ai	$24,$24,16
	ai	$15,$15,1
	lqd	$25,0($22)	# [array0,j1]
	br	.L10
	nop
.L9:
#								(*array1)[j3] = (*array0)[j2]; j3++; j2++;
	ai	$23,$23,16
	ai	$14,$14,1
	stqd	$26,0($24)	# [array1,j3]
	ai	$24,$24,16
	ai	$15,$15,1
	lqd	$26,0($23)	# [array0,j2]
.L10:
	br	.L7
.L8:

#						while ( j1<j+k2 )
.L7a:
	cgt	$2,$18,$13
	brz	$2,.L8a
#							(*array1)[j3] = (*array0)[j1]; j3++; j1++;
	ai	$22,$22,16
	ai	$13,$13,1
	stqd	$25,0($24)	# [array1,j3]
	ai	$24,$24,16
	ai	$15,$15,1
	lqd	$25,0($22)	# [array0,j1]
	
	br	.L7a
.L8a:

#						while ( j2<j+k  )
.L7b:
	cgt	$2,$17,$14
	brz	$2,.L8b
#							(*array1)[j3] = (*array0)[j2]; j3++; j2++;
	ai	$23,$23,16
	ai	$14,$14,1
	stqd	$26,0($24)	# [array1,j3]
	ai	$24,$24,16
	ai	$15,$15,1
	lqd	$26,0($23)	# [array0,j2]
	br	.L7b
.L8b:
	
	
	a	$10,$10,$11
	br	.L5
.L6:

	a	$11,$11,$11	# k<<=1
	a	$12,$12,$12	# k2<<=1
	br	.L3
.L4:
	

# end of subroutine
	lr	$2,$20
	ori	$3,$2,0
	ai	$sp,$sp,192
	bi	$lr

	.size	phase1, .-phase1
	.comm	array0,4,128
	.comm	array1,4,128
	.comm	array2,4,128
	.ident	"GCC: (GNU) 4.1.1"
