/*
int novonum(void) {
  int minhalocal;
  printf("numero: ");
  scanf("%d",&minhalocal);
  return minhalocal;
}
*/

/*
-8(%rbp) --> minhalocal
*/

.data
sf1: .string "numero: "
sf2: .string "%d"

.text
.globl novonum
novonum:
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp
    
    movq $sf1, %rdi
    movl $0, %eax
    call printf

    movq $sf2, %rdi
    movl $0, %eax
    leaq -8(%rbp), %rsi
    call scanf

    movl -8(%rbp), %eax
    leave
    ret
    