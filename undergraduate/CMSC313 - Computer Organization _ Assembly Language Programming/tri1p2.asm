;;; ;  Filename:	tri1p2.asm
;;; ;  Name:		Patrick Trinkle
;;; ;  Email:		tri1@umbc.edu
;;; ;  Date:		20 Oct 2005
;;; ;  Course:		CMSC-313
;;; ;  Description:
;;; ;			Program asks for a filename from user and then opens file
;;; ;			the program then reads in 8k at a time and calculates how many of each letter
;;; ;			appeared in the text.  The program then displays this information for the user
;;; ;			in descending order
;;; ;
;;; ;  Notes:		This is the working version of this program.  I made this one so I could show something
;;; ;			which works and basically does everything.  I was working on a version which did the print
;;; ;			as you sort functionality, but I did not get it working 100% in time.  Some math errors in my
;;; ;			logic, probably something simple.
;;; ;
;;; ;
;;; ;   tri1p2.asm  a program for nasm for Linux, Intel, gcc
;;; ;
;;; ;  assemble:		nasm -f elf -l tri1p2.lst  tri1p2.asm
;;; ;  link:			gcc -o tri1p2  tri1p2.o
;;; ;  run:		        tri1p2
;;; ;  output is:		reads in a file and calculates how frequent a letter occurs


%define OPEN		5
%define READ		3
%define	CLOSE		6
%define O_RDONLY	00
%define O_WRONLY	01
%define O_RDWR		02
%define BUFSZE		8192
%define FLNMSZE		128
%define ASCIISZE	256


section .data

	msgflnm	db	'Enter Filename: ',0
	flnmin	db	'%s',0
	msgftbl	db	10,'Letter Table',10,0		
	msgtbl	db	' %c      %d',10,0
	msgbadfile	db	'Enter a new filename when asked',10,0

			
section .bss

filenm:		resb	FLNMSZE
rdbuff:		resb	BUFSZE
counts:		resd	ASCIISZE
fdRead:		resd	1
bRead:		resd	1
buffoff:	resd	1
alpha:		resd	1	
nextoffset:	resd	1
i:		resd	1
				
section .text

	global main
	extern printf
	extern scanf
	
main:
				; print message
	push	msgflnm
	call	printf
	add	esp, 4

				;  get filename
	push	filenm
	push	flnmin
	call	scanf
	add	esp, 8
		
OpenFile:
	mov	eax, dword OPEN
	mov	ebx, filenm
	mov	ecx, O_RDONLY
	mov	edx, 0
	int	80h
	mov	dword [ fdRead ], eax

	cmp	eax, 0
	jl	BadFile
	jmp	ReadFile
BadFile:
	push	msgbadfile
	call	printf
	add	esp, 4
	jmp	main	

	;; Read Loop { Process Loop }
ReadFile:	
	mov	eax, READ
	mov	ebx, dword [ fdRead ]
	mov	ecx, dword rdbuff
	mov	edx, dword BUFSZE
	int	80h
	mov	dword [ bRead ], eax

	;; Process Loop
	mov	edi, dword 0	
	mov	ecx, dword 0
Process:

	cmp	dword [ rdbuff + edi ], 96
	jg	Toupper
	jmp	Both
Toupper:
	sub	dword [ rdbuff + edi ], 32
Both:	
	mov	eax, 0
	mov	al, byte [ rdbuff + edi ]
	mov	bl, 4
	mul	bl
	add	eax, counts
	inc	dword [ eax ]
		

	inc	edi
	inc	ecx
	cmp	ecx, dword [ bRead ]
	jl	Process
	
	cmp	dword [ bRead ], BUFSZE
	je	ReadFile
				
CloseFile:
	mov	eax, CLOSE
	mov	ebx, dword [ fdRead ]
	int	80h


	;; Print table title
	push	msgftbl
	call	printf
	add	esp, 4
	


	mov	dword [ i ], 0
	mov	dword [ alpha ], 65 ; set to 'A'
PrintLoop:
	mov	eax, dword 0
	mov	edx, dword 0
	mov	edi, dword 260
	mov	dword [ nextoffset ], dword 260

Step0:
	mov	eax, dword [ counts + edi ] ; current high value

	add	dword [ nextoffset ], 4
	mov	edx, dword [ nextoffset ]
	mov	ebx, dword [ counts + edx ] ; next guy
		
	cmp	eax, ebx	; cmp current, next
	jl	NewBig

	cmp	edx, 364
	jl	Step0
	jmp	End
	
NewBig:
	mov	edi, dword [ nextoffset ]

	mov	eax, dword 0
	mov	ebx, dword 0
	mov	edx, dword 0
	mov	ecx, dword 0

	mov	eax, dword [ nextoffset ]
	mov	ebx, dword 4
	div	ebx
	mov	dword [ alpha ], eax
	
	cmp	edi, 364
	jl	Step0
	jmp	End
		
End:
	;; nothing
	push	dword [ counts + edi ]
	mov	dword [ counts + edi ], -1
	push	dword [ alpha ]
	push	msgtbl
	call	printf
	add	esp, 12

	inc	dword [ i ]
	cmp	dword [ i ], 26
	jl	PrintLoop
	
		
		
termination_protocol:

	mov	ebx, 0	;   exit code, 0=normal
	mov	eax, 1	;   exit command to kernel
	int	0x80	;   interrupt 80 hex, call kernel