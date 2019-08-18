# Name: 			Shashi Ranjan
# Roll. No.: 		80
# Reg. No.: 		278


	.file	"what.c"								# file name
	.text											# text section
	.globl	what									# make 'what' global
	.type	what, @function 						# declaring what as a function
what:												# function starts
.LFB0:												# initialising variables
	pushq	%rbp									# base pointer
	movq	%rsp, %rbp								# pointing stack pointer to the base pointer
	movq	%rdi, -24(%rbp) 						# data-->M[rbp-24]
	movl	%esi, -28(%rbp) 						# n-->M[rbp-28]
	movl	$1, -12(%rbp)   						# 1-->i
	jmp	.L2											# jump to .L2 section
.L8:												
	movl	-12(%rbp), %eax							# i-->eax
	cltq											# eax-->rax
	leaq	0(,%rax,4), %rdx						# loads address of 0+(i*4) into rdx 
	movq	-24(%rbp), %rax 						# &(data[0])-->rax
	addq	%rdx, %rax								# rax+rdx-->rax
	movl	(%rax), %eax							# i-->eax
	movl	%eax, -4(%rbp) 							# eax-->temp
	movl	-12(%rbp), %eax 						# i-->eax
	subl	$1, %eax								# (eax-1)-->eax
	movl	%eax, -8(%rbp)							# eax-->j
	jmp	.L3											# jump to .L3
.L7:										
	movl	-8(%rbp), %eax							# j-->eax
	cltq											# 
	leaq	0(,%rax,4), %rdx						# loads address of 0+(j*4) into rdx 
	movq	-24(%rbp), %rax 						# data[0]-->rax
	addq	%rdx, %rax								# (rdx+rax)-->rax
	movl	(%rax), %eax							# data[j]-->eax(temp)
	cmpl	%eax, -4(%rbp)							# if temp<data[j]
	jle	.L9											# jump to .L9
	movl	-8(%rbp), %eax							# j-->eax
	cltq											#
	leaq	0(,%rax,4), %rdx						# loads address of 0+(j*4) into rdx 
	movq	-24(%rbp), %rax							# data[0]-->rax
	addq	%rdx, %rax								# (rdx+rax)-->rax
	movl	-8(%rbp), %edx							# j-->edx
	movslq	%edx, %rdx								# move sign extended edx(32 bit)-->rdx(64bit)
	addq	$1, %rdx								# (rdx+1)-->rdx
	leaq	0(,%rdx,4), %rcx						# loads address of 0+(rdx*4) into rcx 
	movq	-24(%rbp), %rdx 						# data[0]-->rdx
	addq	%rcx, %rdx								# (rdx+rcx)-->rdx i.e. rdx=data[j+1]
	movl	(%rax), %eax							# data[j]-->eax
	movl	%eax, (%rdx)							# data[j]-->data[j+1]
	subl	$1, -8(%rbp)							# j-1-->j
.L3:					
	cmpl	$0, -8(%rbp)							# if j<0
	jns	.L7											# jump to L7
	jmp	.L6											# else jump to L6
.L9:												
	nop												#do nothing
.L6:												
	movl	-8(%rbp), %eax							# j-->eax
	cltq											# 
	addq	$1, %rax								# (rax+1)-->rax
	leaq	0(,%rax,4), %rdx						# loads address of 0+(rax*4) into rdx
	movq	-24(%rbp), %rax 						# &data[0]-->rax
	addq	%rax, %rdx								# (rdx+rax)-->rdx i.e. rdx=data[j+1]
	movl	-4(%rbp), %eax							# temp-->eax
	movl	%eax, (%rdx)							# temp-->data[j+1]
	addl	$1, -12(%rbp)							# (i+1)-->i
.L2:												
	movl	-12(%rbp), %eax 						# i-->eax
	cmpl	-28(%rbp), %eax	 						# if i<n
	jl	.L8											# jump to L8
	nop												# else do nothing
	popq	%rbp									# retrieve base pointer
	ret												# return
.LFE0:
	.size	what, .-what
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
