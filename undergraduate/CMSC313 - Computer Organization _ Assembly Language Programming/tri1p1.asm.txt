;;;  Filename:	       tri1p1.asm
;;;  Name:	           Patrick Trinkle
;;;  Email:	          tri1@umbc.edu
;;;  Date:	            7 Oct 2005
;;;  Course:	         CMSC-313
;;;  Description:	    (Your psuedocode goes here.  Must be detailed)
;;;  Notes:	          (As needed, such has how to assemble)
;;;
;;;
;;;   tri1p1.asm  a first program for nasm for Linux, Intel, gcc
;;;
;;;  assemble:		nasm -f elf -l tri1p1.lst  tri1p1.asm
;;;  link:			gcc -o tri1p1  tri1p1.o
;;;  run:		        tri1p1
;;;  output is:		mpg calculator kind of, and does other random math


section .data

	msgmi	db	'Enter miles driven: ', 0
	msggal	db	'Enter the gallons of gasoline used (integer): ', 0
	msgout	db	'Your miles per gallon was %d', 10, 10, 0
	msgi	db	10, 'i = %d', 10, 0
	msgj	db	'j = %d', 10, 10, 0
	msglp	db	10, 'Starting FOR loop:', 10, 0
	msgk	db	'k = %d', 10, 0

	number1	dd	801
	number2	dd	15
	number3	dd	75

	inmi	db	'%d', 0

	
section .bss


i:	resd	1
j:	resd	1
k:	resd	1
	
miles:	resd	1
gallons:	resd	1
mpg:	resd	1


	
section .text

	global main
	extern printf
	extern scanf

main:

	push	msgmi
	call	printf
	add	esp, 4

input1:

	mov	[miles], dword 0
	mov	[gallons], dword 0
	mov	[mpg], dword 0

	push	miles
	push	inmi
	call	scanf
	add	esp, 8

	push	msggal
	call	printf
	add	esp, 4

input2:

	push	gallons
	push	inmi
	call	scanf
	add	esp, 8

gas_calculation:

	mov	eax, dword 0
	mov	ebx, dword 0
	mov	edx, dword 0
	
	mov	eax, [miles]
	mov	ebx, [gallons]
	div	ebx
	mov	[mpg], eax

printmiles:

	push	dword [mpg]
	push	msgout
	call	printf
	add	esp, 8

randommathi:

	mov	eax, dword 0
	mov	ebx, dword 0
	mov	edx, dword 0
	
	mov	eax, [number1]	; i = number1 % 12
	mov	ebx, 12
	div	ebx
	mov	[i], edx

	inc	dword [i]

	push	dword [i]
	push	msgi
	call	printf
	add	esp, 8
	
randommathj:
	
	mov	eax, dword 0
	mov	ebx, dword 0
	mov	edx, dword 0
	mov	ecx, dword 0

	mov	eax, dword [number1] ; j = number1 + 4
	mov	[j], eax
	add	[j], dword 4

	mov	eax, dword 0
	mov	ebx, dword 0
	mov	edx, dword 0
	
	mov	eax, dword [number2] ; number2 * i
	mov	ebx, dword [i]
	mul	ebx

	mov	ebx, dword [number3]
	div	ebx
	;; eax = (num2 * i) / number3

	mov	ebx, dword 3
	mul	ebx
	;; eax = ((num2 * i) / num3) * 3

	add	dword [j], eax	; j += (num2 * i)/(num3 * 3)

	push	dword [j]
	push	msgj
	call	printf
	add	esp, 8

	mov	[k], dword 0	
	mov	ecx, -28
	mov	eax, dword 0
theFORLoop:

	mov	[k], ecx
	mov	eax, dword [k]
	sub	eax, dword 5
	
	push	eax
	push	msgk
	call	printf
	add	esp, 8
	
	add	[k], dword 8
	mov	ecx, dword [k]
	
	cmp	ecx, 25
	jl theFORLoop	

termination_protocol:	
	
	mov	ebx, 0	;  exit code, 0=normal
	mov	eax, 1	;  exit command to kernel
	int	0x80	;  interrupt 80 hex, call kernel