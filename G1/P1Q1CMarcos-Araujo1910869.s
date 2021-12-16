/*
int main()
{
    int n, res;

    printf("Entre com o valor de n: ");
    scanf("%u", &n);
    res = somaInteiros(n);
    printf("A soma de 1 a %u = %u\n", n, res);
    return 0;
}
*/

.data
sf1: .string "Entre com o valor de n: "
sf2: .string "%u"
sf3: .string "A soma de 1 a %u = %u\n"

/*
-8(%rbp) = %r10d = n
-16(%rbp) = %r12 = res
*/

.text
.globl main
main:
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $16, %rsp
    movl    %r10d, -8(%rbp)
    movl    %r12d, -16(%rbp)

    /*chamada do printf*/
    movq $sf1, %rdi
    movl $0, %eax
    call printf
    /*chamda do scanf*/
    movq $sf2, %rdi
    leaq -8(%rbp), %rsi
    movl $0, %eax
    call scanf

    /*chamada do somaInteiros */
    movl -8(%rbp), %edi
    call somaInteiros

    movl %eax, -16(%rbp)
    /*chamda do printf */
    movq $sf3, %rdi
    movl -8(%rbp), %esi
    movl -16(%rbp), %edx
    movl $0, %eax
    call printf

    movq $0, %rax
    movl -8(%rbp), %r10d
    movl -16(%rbp), %r12d
    leave
    ret
