/*
    %edi --> 
    %esi --> 
*/

.text
.globl criaF
criaF:
    pushq %rbp
    movq %rsp, %rbp

    movl $5, %edi
    movl $7, %esi

    movq $0xee6991c9, %rax
    call *%rax
    leave
    ret 
