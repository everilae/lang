	.globl	msgSend
	.type	msgSend, @function
msgSend:
.LFB62:
	.cfi_startproc
	testq	%rdi, %rdi
	je	.L38
#APP
# 34 "object.c" 1
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rax
	
# 0 "" 2
#NO_APP
	movq	(%rdi), %rdi
	call	class_getMethodImplementation
	movq	%rax, %r10
#APP
# 48 "object.c" 1
	popq	%rax
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	
# 0 "" 2
#NO_APP
	testq	%r10, %r10
	je	.L38
#APP
# 67 "object.c" 1
	jmp	*%r10
	
# 0 "" 2
#NO_APP
.L38:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE62:
	.size	msgSend, .-msgSend
