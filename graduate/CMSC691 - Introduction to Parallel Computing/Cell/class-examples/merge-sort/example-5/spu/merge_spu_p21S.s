	.file	"merge_spu_p21S.s"
.text
	.align	3
	.global	phase21
	.type	phase21, @function
phase21:
	stqd	$sp,-144($sp)
	ai	$sp,$sp,-144

	lqd	$2,64($sp)	# A0
	hbrp	# 1
	cwd	$8,0($sp)
	shufb	$2,$3,$2,$8
	stqd	$2,64($sp)	# A0
	lqd	$2,80($sp)	# A2
	cwd	$3,0($sp)
	shufb	$2,$4,$2,$3
	stqd	$2,80($sp)	# A2
	lqd	$2,96($sp)	# *xj1
	cwd	$3,0($sp)
	shufb	$2,$5,$2,$3
	stqd	$2,96($sp)	# *xj1
	lqd	$2,112($sp)	# *xj3
	hbrp	# 2
	cwd	$3,0($sp)
	shufb	$2,$6,$2,$3
	stqd	$2,112($sp)	# *xj3
	lqd	$2,128($sp)	# maxsz
	cwd	$3,0($sp)
	shufb	$2,$7,$2,$3
	stqd	$2,128($sp)	# maxsz
	
#  j1 --> $10
#  j3 --> $11
#  array0 --> $12
#  array2 --> $13
#  maxsz  --> $14

	lqd	$2,96($sp)	# *xj1
	ori	$3,$2,0
	lqd	$2,0($3)
	rotqby	$2,$2,$3
	ori	$4,$2,0
	lqd	$2,48($sp)	# j1
	cwd	$3,0($sp)
	shufb	$10,$4,$2,$3	# j1 --> $10
	
	lqd	$2,112($sp)	# *xj3
	ori	$3,$2,0
	lqd	$2,0($3)
	rotqby	$2,$2,$3
	ori	$4,$2,0
	lqd	$2,32($sp)	# j3
	cwd	$3,0($sp)
	shufb	$11,$4,$2,$3	# j3 --> $11
	
	lqd	$14,128($sp)	# maxsz --> $14
	
	lqd	$12,64($sp)	# A0/array0
	lqd	$13,80($sp)	# A2/array2
	shli	$3,$10,4	# j1*16
	shli	$4,$11,4	# j3*16
	a	$12,$10,$3
	a	$13,$11,$4
	
	
.L3:
	ceq	$2,$10,$14	# j1 == maxsz
	brnz	$2,.L4
	ceq	$2,$11,$14	# j3 == maxsz
	brnz	$2,.L4
	
	lqd	$2,0($12)
	stqd	$2,0($13)
	

	ai	$12,$12,16	# array0+=16
	ai	$13,$13,16	# array2+=16
	ai	$10,$10,1	# j1++
	ai	$11,$11,1	# j3++
	br	.L3
.L4:


	ori	$4,$10,0	# j1
	lqd	$2,48($sp)	# j1
	cwd	$3,0($sp)
	shufb	$2,$4,$2,$3
	stqd	$2,48($sp)	# j1
	
	lqd	$2,96($sp)	# *xj1
	ori	$4,$2,0
	lqd	$2,48($sp)	# j1
	ori	$5,$2,0
	lqd	$2,0($4)
	cwd	$3,0($4)
	shufb	$2,$5,$2,$3
	stqd	$2,0($4)	# *xj1

	ori	$4,$11,0	# j3
	lqd	$2,32($sp)	# j3
	cwd	$3,0($sp)
	shufb	$2,$4,$2,$3
	stqd	$2,32($sp)	# j3
		
	lqd	$2,112($sp)	# *xj3
	ori	$4,$2,0
	lqd	$2,32($sp)	# j3
	ori	$5,$2,0
	lqd	$2,0($4)
	cwd	$3,0($4)
	shufb	$2,$5,$2,$3
	stqd	$2,0($4)	# *xj3
	
	ai	$sp,$sp,144
	bi	$lr
	.size	phase21, .-phase21
	.comm	array0,4,128
	.comm	array2,4,128
	.ident	"GCC: (GNU) 4.1.1"
