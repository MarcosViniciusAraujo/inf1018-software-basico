/*void foo (int a[], int n) {
  int i;
  int s = 0;
  for (i=0; i<n; i++) {
    s += a[i];
    if (a[i] == 0) {
      a[i] = s;
      s = 0;
    }
  }
}
*/
/*
%rdi -- a[]
%esi -- n

*/
.text
.globl foo
foo:
    pushq %rbp
    movq  %rsp, %rbp
    subq  $16, %rsp

incio:
    movl $0, %ebx
    movl $0, %ecx
