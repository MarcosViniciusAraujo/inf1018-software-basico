/*int mult(int x, int y)
{
    return x * y;
}
*/


.text
.globl foo
foo:

    pushq %rbp
    movq  %rsp, %rbp
    imul  %edi, %
    leave
    ret
