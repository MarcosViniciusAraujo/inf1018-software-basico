/*
int bemboba(int num)
{
    int local[4];
    int *a;
    int i;

    for (i = 0, a = local; i < 4; i++)
    {
        *a = num;
        a++;
    }
    return addl(local, 4);
}
*/

/*
local[4] --> 16 bytes         -32 
int *a -->    8 bytes         -16
int i -->     4 bytes +       -8
-----------------------
total ---->  28 bytes
*/
#Tem que dar 20

.text
.globl bemboba
bemboba:
    pushq %rbp
    movq  %rsp, %rbp
    subq  $32, %rsp

    movl $0, -8(%rbp)
    leaq -32(%rbp), %r15
    movq %r15, -16(%rbp)

for:
    cmpl $4, -8(%rbp)
    je saida

    movq -32(%rbp), %rbx
    movq %rbx, -16(%rbp) #não sei se está certo
    addl  $1, -16(%rbp)

    addl $1, -8(%rbp)
    jmp for
saida:

    leaq -32(%rbp), %rdi
    movl $4, %esi
    call addl

    leave
    ret

