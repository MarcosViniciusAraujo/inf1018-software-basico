/*
unsigned somaInteiros(unsigned n)
{

    int i = 0;
    int soma = 0;
    for (i = 1; i <= n; i++)
        soma += i;

    return soma;
}

i --> -8(%rbp)

*/

.text 
.globl somaInteiros
somaInteiros:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp

começa:
    movl $1, -8(%rbp) /*i = 1*/
    movl $0, %eax
Repeticao:
    cmpl %edi, -8(%rbp)
    jg fora
    addl -8(%rbp), %eax  
    addl $1, -8(%rbp)
    jmp Repeticao
    /*%eax é o valor de retorno*/
fora:
    leave
    ret
