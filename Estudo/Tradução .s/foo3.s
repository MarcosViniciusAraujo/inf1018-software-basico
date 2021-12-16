

.text 
.globl foo3
foo3:

	pushq %rbp
	movq  %rsp, %rbp
	subq  $32, %rsp
	movq  %rdi, -32(%rbp) /* a*/
	movsd  $0, -24(%rbp) /* r = 0 */
	movl  $0, -16(%rbp) /*i =0 */
	
For:
	cmpl -16(%rbp), %edi
	jge saiFora
	
	movq -32(%rbp), %rdi
	call sin
	
	addsd %xmm0, -24(%rbp)
	addq  $1, -32(%rbp)
	addl  $1, -16(%rbp)
saiFora:
	movsd -24(%rbp), %xmm0
	leave
	ret
	