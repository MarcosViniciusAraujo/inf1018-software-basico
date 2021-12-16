

.text
.globl foo1
foo1:
   
   pushq %rbp
   movq  %rsp, %rbp
   subq  $16, %rbp
   
   cvtss2sd %xmm0, %xmm0
   call sin
   
   movsd  %xmm0, -16(%rbp)
   cvtss2sd %xmm1, %xmm0
   call cos
   
   addsd -16(%rbp), %xmm0
   cvtsd2ss %xmm0, %xmm0

   leave
   ret

 