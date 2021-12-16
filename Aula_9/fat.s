fat:

    cmpl $1, %edi
    je final
else:
    movl %edi, %ebx
    subl $1, %edi
    call fat
    mull %ebx, %eax

final:
    ret