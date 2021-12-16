#include <stdio.h>

typedef int (*funcp)(int x);

unsigned char codigo[] = {0x55, 0x48, 0x89, 0xe5, 0xff, 0xc7, 0x89, 0xf8, 0xc9, 0xc3};

int main()
{

    int i;
    funcp f = (funcp)codigo;
    i = (*f)(10);
    printf("O valor de i é: %d", i);
    return 0;
}