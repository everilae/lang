	.globl	msg_send
	.type	msg_send, @function
msg_send:
	/* Object* this == NULL? */
	cmpq	$0, %rdi
	je	.NOTIMPLEMENTED
	/* Save arguments */
	pushq	%rdi
	pushq	%rsi
	pushq	%rdx
	pushq	%rcx
	pushq	%r8
	pushq	%r9
	pushq	%rax
	/* Save stack pointer, pray to god no functions touch r12 */
	movq	%rsp, %r12
	/* Clear bottom 4 bits, moves stack up and aligns */
	andq	$-0x10, %rsp
	/* %rdi = Object* this
	 * %rdi = this->class */
	movq	(%rdi), %rdi
	call	get_implementation
	/* Restore stack pointer */
	movq	%r12, %rsp
	/* IMP is in %rax, move to safety (%rax has to be restored) */
	movq	%rax, %r11
	/* Restore args */
	popq	%rax
	popq	%r9
	popq	%r8
	popq	%rcx
	popq	%rdx
	popq	%rsi
	popq	%rdi
	/* Do we have an implementation? */
	cmpq	$0, %r11
	je 	.NOTIMPLEMENTED
	/* Trampoline! */
	jmp	*%r11
.NOTIMPLEMENTED:
	movl	$.ERRORMSG, %edi
	call	puts
	movq	$0, %rax
	leave
	ret
.size	msg_send, .-msg_send
	.section	.rodata
.ERRORMSG:
	.string	"msg_send((nil), ...)"

