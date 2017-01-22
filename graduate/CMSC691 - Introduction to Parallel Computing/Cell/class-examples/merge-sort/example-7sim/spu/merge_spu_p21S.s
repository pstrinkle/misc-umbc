	.file	"merge_spu_p21S.s"
.text
	.align	3
	.global	phase21
	.type	phase21, @function
phase21:
	stqd	$sp,-144($sp)
	ai	$sp,$sp,-144

	cwd	$20,0($sp)

	lqd	$2,64($sp)	# A0
	shufb	$12,$7,$2,$20
	
	lqd	$2,80($sp)	# A2
	shufb	$13,$7,$2,$20
	
	lqd	$2,96($sp)	# xj1
	shufb	$21,$5,$2,$20
	lqd	$2,0($21)
	rotqby	$2,$2,$21
	shufb	$10,$2,$2,$20	# j1 --> $10
	
	lqd	$2,112($sp)	# xj3
	shufb	$22,$6,$2,$20
	lqd	$2,0($22)
	rotqby	$2,$2,$22
	shufb	$11,$2,$2,$20	# j3 --> $11
	
	lqd	$2,128($sp)	# maxsz
	shufb	$14,$7,$2,$20
	
#  j1 --> $10
#  j3 --> $11
#  array0 --> $12
#  array2 --> $13
#  maxsz  --> $14
	
	shli	$3,$10,4	# j1*16
	shli	$4,$11,4	# j3*16
	a	$12,$10,$3
	a	$13,$11,$4

.L3:
	ceq	$3,$10,$14	# j1 == maxsz
	brnz	$3,.L4
	ceq	$2,$11,$14	# j3 == maxsz
	brnz	$2,.L4
	
	lqd	$2,0($12)
	ai	$10,$10,1	# j1++
	ai	$11,$11,1	# j3++
	ai	$12,$12,16	# array0+=16
	stqd	$2,0($13)
	ai	$13,$13,16	# array2+=16

	br	.L3
.L4:


	stqd	$10,0($21)	# j1
	stqd	$11,0($22)	# j3
	
	ai	$sp,$sp,144
	bi	$lr
	.size	phase21, .-phase21
	.comm	array0,4,128
	.comm	array2,4,128
	.ident	"GCC: (GNU) 4.1.1"
