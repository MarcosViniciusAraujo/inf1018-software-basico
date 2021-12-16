

.text
.globl pack1
pack1:
	
	pushq %rbp
	movq  %rsp, %rbp
	subq  $32, %rsp
	movq  %rdi, -32(%rbp)
	movl  %esi, -24(%rbp) 
	movq  $0, -16(%rbp) /* acc = 0 */
	movl  $0, -8(%rbp) /* i = 0 */ 
	
For:
	movl -8(%rbp), %ecx
	movl %ecx, -24(%rbp)
	jge saiFora
	
	imull $8, %ecx
	addq -32(%rbp), %rcx
	cvtss2sd 4(%rcx), %xmm0
	movl (%rcx), $edi
	call foo
	
	addsd -16(%rbp), %xmm0
	movsd %xmm0, -16(%rbp)
	
	jmp For
	
saiFora:
	
	movsd -16(%rbp), %xmm0 
	leave
	ret
	