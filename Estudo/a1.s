/*
for(i = 0; i < 10; i++) printf("%d\n", i);
*/
#-8(%rbp) == i

.data 
sf1: .string "%d\n"

.text
.globl main
main:

    pushq %rbp
    movq %rsp, %rbp
    subq $16 , %rbp

    movl $0, %ebx #i = 0
For:
    cmpl $10, %ebx
    je saida

    movq $sf1, %rdi
    movl %ebx, %esi
    movl $0, %eax
    call printf

    addl $1, %ebx
    jmp For
saida:
    movq %rbp, %rsp
    popq %rbp
    leave
    ret
