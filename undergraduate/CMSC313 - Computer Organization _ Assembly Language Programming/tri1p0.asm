;; Filename:       tri1p0.asm
;; Name:           Patrick Trinkle
;; Email:          tri1@umbc.edu
;; Date:           22 Sep 2005
;; Course:         CMSC-313
;; Description:    (Your psuedocode goes here.  Must be detailed)
;; Notes:          (As needed, such has how to assemble)
;;
;;
;;  tri1p0.asm  a first program for nasm for Linux, Intel, gcc
;;
;; assemble:	nasm -f elf -l tri1p0.lst  tri1p0.asm
;; link:		gcc -o tri1p0  tri1p0.o
;; run:	        tri1p0 
;; output is:	Hello World 

	SECTION .data		; data section
msg:	db "Hello World",10	; the string to print, 10=cr
len:	equ $-msg		; "$" means "here"
				; len is a value, not an address

	SECTION .text		; code section
        global main		; make label available to linker 
main:				; standard  gcc  entry point
	
	mov	edx,len		; arg3, length of string to print
	mov	ecx,msg		; arg2, pointer to string
	mov	ebx,1		; arg1, where to write, screen
	mov	eax,4		; write command to int 80 hex
	int	0x80		; interrupt 80 hex, call kernel
	
	mov	ebx,0		; exit code, 0=normal
	mov	eax,1		; exit command to kernel
	int	0x80		; interrupt 80 hex, call kernel