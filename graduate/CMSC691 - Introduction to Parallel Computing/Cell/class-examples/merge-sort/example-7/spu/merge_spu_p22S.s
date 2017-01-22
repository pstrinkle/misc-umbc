	.file	"merge_spu_p22S.s"
.text
	.align	3
	.global	phase22
	.type	phase22, @function
phase22:
	stqd	$sp,-192($sp)
	ai	$sp,$sp,-192

	cwd	$20,0($sp)

	lqd	$2,80($sp)	# A0/array0
	shufb	$13,$3,$2,$20
	lqd	$2,96($sp)	# A1/array1
	shufb	$14,$4,$2,$20
	lqd	$2,112($sp)	# A2/array2
	shufb	$15,$5,$2,$20
	lqd	$2,128($sp)	# xj1
	shufb	$21,$6,$2,$20
	lqd	$2,144($sp)	# xj2
	shufb	$22,$7,$2,$20
	lqd	$2,160($sp)	# xj3
	shufb	$23,$8,$2,$20
	lqd	$2,176($sp)	# maxsz
	shufb	$16,$9,$2,$20	# maxsz --> $16

	lqd	$2,0($21)	# *xj1
	rotqby	$2,$2,$21
	shufb	$10,$2,$2,$20	# j1 --> $10

	lqd	$2,0($22)	# *xj2
	rotqby	$2,$2,$22
	shufb	$11,$2,$2,$20	# j2 --> $11

	lqd	$2,0($23)	# *xj3
	rotqby	$2,$2,$23
	shufb	$12,$2,$2,$20	# j3 --> $12

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

	stqd	$10,0($21)	# *xj1
	stqd	$11,0($22)	# *xj2
	stqd	$12,0($23)	# *xj3

	ai	$sp,$sp,192
	bi	$lr
	.size	phase22, .-phase22
	.comm	array0,4,128
	.comm	array1,4,128
	.comm	array2,4,128
	.ident	"GCC: (GNU) 4.1.1"
