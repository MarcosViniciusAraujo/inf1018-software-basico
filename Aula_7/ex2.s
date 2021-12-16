/*
#include <stdio.h>

int main(){

    int i;
    for(i = 1; i=<10 ; i++){
        printf("%d\n", i * i);
    }

    return 0;
}
*/

.data
Sf:  .string "%d\n"

.text
.globl main
main:
/********************************************************/
/* mantenha este trecho aqui e nao mexa - prologo !!!   */
  pushq   %rbp
  movq    %rsp, %rbp
  subq    $16, %rsp
  movq    %rbx, -8(%rbp)  /* guarda rbx */
  movq    %r12, -16(%rbp)  /* guarda r12 */
/********************************************************/
  movl $1, %eax /* i = 1 */

For:
  cmpl $10, %eax
  jge L2
  movl %eax, %ebx

  imull %ebx, %ebx

/*************************************************************/
/* este trecho imprime o valor de %ebx (estraga %ebx)  */
  movq    $Sf, %rdi    /* primeiro parametro (ponteiro)*/
  movl    %ebx, %esi   /* segundo parametro  (inteiro) */
  movl  $0, %ebx
  call  printf       /* chama a funcao da biblioteca */
/*************************************************************/

  addl $1, %eax
  jmp For

L2:
/***************************************************************/
/* mantenha este trecho aqui e nao mexa - finalizacao!!!!      */
  movq  $0, %rax  /* rax = 0  (valor de retorno) */
  movq    -16(%rbp), %r12 /* recupera r12 */
  movq    -8(%rbp), %rbx  /* recupera rbx */
  leave
  ret      
/***************************************************************/
