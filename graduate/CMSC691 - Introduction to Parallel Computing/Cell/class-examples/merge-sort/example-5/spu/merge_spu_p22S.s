	.file	"merge_spu_p22S.s"
.text
	.align	3
	.global	phase22
	.type	phase22, @function
phase22:
	stqd	$sp,-192($sp)
	ai	$sp,$sp,-192
	lqd	$2,80($sp)	# A0/array0
	hbrp	# 1
	cwd	$10,0($sp)
	shufb	$2,$3,$2,$10
	stqd	$2,80($sp)	# A0/array0
	lqd	$2,96($sp)	# A1/array1
	cwd	$3,0($sp)
	shufb	$2,$4,$2,$3
	stqd	$2,96($sp)	# A1/array1
	lqd	$2,112($sp)	# A2/array2
	cwd	$3,0($sp)
	shufb	$2,$5,$2,$3
	stqd	$2,112($sp)	# A2/array2
	lqd	$2,128($sp)	# xj1
	hbrp	# 2
	cwd	$3,0($sp)
	shufb	$2,$6,$2,$3
	stqd	$2,128($sp)	# xj1
	lqd	$2,144($sp)	# xj2
	cwd	$3,0($sp)
	shufb	$2,$7,$2,$3
	stqd	$2,144($sp)	# xj2
	lqd	$2,160($sp)	# xj3
	cwd	$3,0($sp)
	shufb	$2,$8,$2,$3
	stqd	$2,160($sp)	# xj3
	lqd	$2,176($sp)	# maxsz
	cwd	$3,0($sp)
	shufb	$2,$9,$2,$3
	ori	$16,$2,0	# maxsz --> $16

	lqd	$2,128($sp)	# xj1
	ori	$3,$2,0
	lqd	$2,0($3)	# *xj1
	rotqby	$2,$2,$3
	ori	$4,$2,0
	lqd	$2,64($sp)	# j1
	cwd	$3,0($sp)
	shufb	$2,$4,$2,$3
	ori	$10,$2,0	# j1 --> $10

	lqd	$2,144($sp)	# xj2
	ori	$3,$2,0
	lqd	$2,0($3)	# *xj2
	rotqby	$2,$2,$3
	ori	$4,$2,0
	lqd	$2,48($sp)	# j2
	cwd	$3,0($sp)
	shufb	$2,$4,$2,$3
	ori	$11,$2,0	# j2 --> $11

	lqd	$2,160($sp)	# xj3
	ori	$3,$2,0
	lqd	$2,0($3)	# *xj3
	rotqby	$2,$2,$3
	ori	$4,$2,0
	lqd	$2,32($sp)	# j3
	cwd	$3,0($sp)
	shufb	$2,$4,$2,$3
	ori	$12,$2,0	# j3 --> $12

	lqd	$13,80($sp)	# A0/array0 --> $13
	lqd	$14,96($sp)	# A1/array1 --> $14
	lqd	$15,112($sp)	# A2/array2 --> $15
	shli	$3,$10,4	# j1*16
	shli	$4,$11,4	# j2*16
	shli	$5,$12,4	# j3*16
	a	$13,$13,$3
	a	$14,$14,$4
	a	$15,$15,$5
	
#  j1 --> $10
#  j2 --> $11
#  j3 --> $12
#  array0 --> $13
#  array1 --> $14
#  array2 --> $15
#  maxsz  --> $16
#  [array0,j1] --> $17
#  [array1,j2] --> $18
	
	lqd	$17,0($13)	# [array0,j1] --> $17
	lqd	$18,0($14)	# [array1,j2] --> $18
	
.L3:
	ceq	$2,$10,$16	# j1 == maxsz
	brnz	$2,.L4
	ceq	$2,$11,$16	# j3 == maxsz
	brnz	$2,.L4
	ceq	$2,$12,$16	# j3 == maxsz
	brnz	$2,.L4

	cgt	$2,$17,$18
	brz	$2,.L5
	
	ai	$10,$10,1	# j1++
	ai	$13,$13,16	# array0+=16
	stqd	$17,0($15)	# [array2,j3]
	lqd	$17,0($13)	# [array0,j1]
	ai	$12,$12,1	# j3++
	ai	$15,$15,16	# array2+=16

	br	.L6
.L5:

	ai	$11,$11,1	# j2++
	ai	$14,$14,16	# array1+=16
	stqd	$18,0($15)	# [array2,j3]
	lqd	$18,0($14)	# [array1,j2]
	ai	$12,$12,1	# j3++
	ai	$15,$15,16	# array2+=16

.L6:
	

	br	.L3
.L4:

	lqd	$2,128($sp)	# xj1
	ori	$4,$2,0
	ori	$5,$10,0	# j1
	lqd	$2,0($4)	# *xj1
	cwd	$3,0($4)
	shufb	$2,$5,$2,$3
	stqd	$2,0($4)	# *xj1

	lqd	$2,144($sp)	# xj2
	ori	$4,$2,0
	ori	$5,$11,0	# j2
	lqd	$2,0($4)	# *xj2
	cwd	$3,0($4)
	shufb	$2,$5,$2,$3
	stqd	$2,0($4)	# *xj2

	lqd	$2,160($sp)	# xj3
	ori	$4,$2,0
	ori	$5,$12,0	# j3
	lqd	$2,0($4)	# *xj3
	cwd	$3,0($4)
	shufb	$2,$5,$2,$3
	stqd	$2,0($4)	# *xj3

	ai	$sp,$sp,192
	bi	$lr
	.size	phase22, .-phase22
	.comm	array0,4,128
	.comm	array1,4,128
	.comm	array2,4,128
	.ident	"GCC: (GNU) 4.1.1"
