.text
.globl pack1

pack1:
   pushq %rbp
   movq  %rsp, %rbp
   subq  $32, %rsp
   movq  %rdi, -32(%rbp)
   movl  %esi, -24(%rbp)
   movq  $0, -16(%rbp)
   movl  $0, -8(%rbp)
   
L1:
   movl  -8(%rbp), %ecx
   cmpl  %ecx, -24(%rbp)
   jle   saifora
   
   imull $8, %ecx /* ponteiro ou tamanho da struct? */
   addq  -32(%rbp), %rcx
   cvtss2sd 4(%rcx), %xmm0
   movl  (%rcx), %edi
   call  foo
   addsd -16(%rbp), %xmm0
   movsd %xmm0, -16(%rbp)
   incl  -8(%rbp)
   jmp   L1
   
saifora:
   movsd -16(%rbp), %xmm0
   leave
   ret
   