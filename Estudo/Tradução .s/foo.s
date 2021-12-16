
.text
.globl foo
foo:
   pushq  %rbp
   movq   %rsp, %rbp
   
   cvtsd2ss %xmm0, %xmm0
   mulss  %xmm0, %xmm0
   mulss  %xmm1, %xmm1
   subss  %xmm1, %xmm0
   
   leave
   ret
   