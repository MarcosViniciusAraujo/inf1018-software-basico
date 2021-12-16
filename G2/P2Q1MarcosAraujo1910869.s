.text
.globl valfoo
valfoo:
	pushq %rbp
	movq %rsp, %rbp
	subq  $16, %rsp
	cvtsi2sd %edi, -8(%rbp)
	mulsd %xmm2, -8(%rbp) 
	cvtss2sd %xmm1, %xmm1
	mulsd %xmm1, %xmm0 
	subsd %xmm0, -8(%rbp)
	cvtsd2ss -8(%rbp), %xmm1 
	ucomiss -8(%rbp), %xmm3
	jbe False
True:
	movss -8(%rbp), %xmm2
False:
	movss %xmm2, %xmm0
	leave
	ret