	.file	"proccesses.c"
	.section	.rodata
.LC0:
	.string	"Fork error %d.\n"
	.align 8
.LC1:
	.string	" the wise son started working "
	.align 8
.LC2:
	.string	" the child is sleeping for 1 second and  then exiting with status 16 "
	.align 8
.LC3:
	.string	"child exited with status : %d\n"
	.align 8
.LC4:
	.string	"................................................................................................."
.LC5:
	.string	" foolish son started working "
	.align 8
.LC6:
	.string	" child : %d  : i am the foolish child \n"
.LC7:
	.string	" sigmentation fault occured "
.LC8:
	.string	"Signal: %s"
	.align 8
.LC9:
	.string	"................................................................................................"
.LC10:
	.string	" wicked son started working "
	.align 8
.LC11:
	.string	" the wicked son with pid : %d is sending a signal to itself for killing itself \n"
	.align 8
.LC12:
	.string	" the hardworking son started working "
.LC13:
	.string	"make systeminfo"
.LC14:
	.string	"./systeminfo"
.LC15:
	.string	"./systeminfo.c"
	.align 8
.LC16:
	.string	"\n the total time spent is : %d microseconds \n"
.LC17:
	.string	" closing main programme "
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$192, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -92(%rbp)
	call	fork
	movl	%eax, -88(%rbp)
	cmpl	$0, -88(%rbp)
	jns	.L2
	call	__errno_location
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %edi
	call	exit
.L2:
	cmpl	$0, -88(%rbp)
	jne	.L3
	movl	$.LC1, %edi
	call	puts
	movl	$.LC2, %edi
	call	puts
	movl	$1, %edi
	call	sleep
	movl	$16, %edi
	call	exit
.L3:
	movl	$0, -32(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	wait
	movl	%eax, -88(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -192(%rbp)
	movl	-192(%rbp), %eax
	andl	$127, %eax
	testl	%eax, %eax
	jne	.L4
	movl	-32(%rbp), %eax
	movl	%eax, -176(%rbp)
	movl	-176(%rbp), %eax
	andl	$65280, %eax
	sarl	$8, %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
.L4:
	movl	$.LC4, %edi
	call	puts
	call	fork
	movl	%eax, -84(%rbp)
	cmpl	$0, -84(%rbp)
	jns	.L5
	call	__errno_location
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %edi
	call	exit
.L5:
	cmpl	$0, -84(%rbp)
	jne	.L6
	movl	$.LC5, %edi
	call	puts
	call	getpid
	movl	%eax, -80(%rbp)
	movl	-80(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC6, %edi
	movl	$0, %eax
	call	printf
	movl	$.LC7, %edi
	call	puts
	movq	$0, -64(%rbp)
	movq	-64(%rbp), %rax
	movzbl	(%rax), %eax
	movsbl	%al, %eax
	movl	%eax, %edi
	call	putchar
	movl	$.LC7, %edi
	call	puts
	jmp	.L7
.L6:
	movl	$0, -32(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	wait
	movl	%eax, -88(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -160(%rbp)
	movl	-160(%rbp), %eax
	andl	$127, %eax
	testl	%eax, %eax
	jne	.L7
	movl	-32(%rbp), %eax
	movl	%eax, -144(%rbp)
	movl	-144(%rbp), %eax
	andl	$127, %eax
	movl	%eax, %edi
	call	strsignal
	movq	%rax, %rsi
	movl	$.LC8, %edi
	movl	$0, %eax
	call	printf
.L7:
	movl	$.LC9, %edi
	call	puts
	call	fork
	movl	%eax, -76(%rbp)
	cmpl	$0, -76(%rbp)
	jns	.L9
	call	__errno_location
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %edi
	call	exit
.L9:
	cmpl	$0, -76(%rbp)
	jne	.L10
	movl	$.LC10, %edi
	call	puts
	call	getpid
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC11, %edi
	movl	$0, %eax
	call	printf
	movl	-72(%rbp), %eax
	movl	$6, %esi
	movl	%eax, %edi
	call	kill
	jmp	.L11
.L10:
	movl	$0, -32(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	wait
	movl	%eax, -88(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -128(%rbp)
	movl	-128(%rbp), %eax
	andl	$127, %eax
	testl	%eax, %eax
	jne	.L11
	movl	-32(%rbp), %eax
	movl	%eax, -112(%rbp)
	movl	-112(%rbp), %eax
	andl	$65280, %eax
	sarl	$8, %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
.L11:
	movl	$.LC9, %edi
	call	puts
	call	fork
	movl	%eax, -68(%rbp)
	cmpl	$0, -68(%rbp)
	jns	.L13
	call	__errno_location
	movl	(%rax), %eax
	movl	%eax, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$1, %edi
	call	exit
.L13:
	cmpl	$0, -68(%rbp)
	jne	.L14
	movl	$.LC12, %edi
	call	puts
	leaq	-48(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday
	movl	$.LC13, %edi
	call	system
	movl	$.LC14, %edi
	call	system
	movl	$0, %edx
	movl	$0, %esi
	movl	$.LC15, %edi
	call	execve
	leaq	-32(%rbp), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	gettimeofday
	movq	-32(%rbp), %rdx
	movq	-48(%rbp), %rax
	subq	%rax, %rdx
	movq	%rdx, %rax
	imulq	$100000, %rax, %rax
	movq	-24(%rbp), %rcx
	movq	-40(%rbp), %rdx
	subq	%rdx, %rcx
	movq	%rcx, %rdx
	addq	%rdx, %rax
	movq	%rax, -56(%rbp)
	movq	-56(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC16, %edi
	movl	$0, %eax
	call	printf
	movl	$10, %edi
	call	exit
.L14:
	movl	$0, -32(%rbp)
	leaq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	wait
	movl	%eax, -88(%rbp)
	movl	-32(%rbp), %eax
	movl	%eax, -96(%rbp)
	movl	-96(%rbp), %eax
	andl	$127, %eax
	testl	%eax, %eax
	jne	.L15
	movl	-32(%rbp), %eax
	movl	%eax, -48(%rbp)
	movl	-48(%rbp), %eax
	andl	$65280, %eax
	sarl	$8, %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
.L15:
	movl	$.LC9, %edi
	call	puts
	movl	$.LC17, %edi
	call	puts
	movl	$0, %eax
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L17
	call	__stack_chk_fail
.L17:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.9.2-10ubuntu13) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
