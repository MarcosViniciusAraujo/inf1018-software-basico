/*
float foo (double a, float b) {
  return (a+b)*(a-b);
}
*/

/*

%xmm0 --> a
%xmm1 --> b

a + b --> b // converter para double
a - b --> a // converter para double

a * b --> %xmm0 // converter para float


*/
.text
.globl foo
foo:
    cvtss2sd %xmm1, %xmm1
    addsd    %xmm0, %xmm1 

    subsd    %xmm1, %xmm0
    
    mulsd    %xmm1, %xmm0

    cvtsd2ss %xmm0, %xmm0

    leave
    ret

