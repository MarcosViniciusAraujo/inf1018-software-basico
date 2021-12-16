#include <stdio.h>

unsigned somaInteiros(unsigned n);

int main()
{
    int n, res;

    printf("Entre com o valor de n: ");
    scanf("%u", &n);
    res = somaInteiros(n);
    printf("A soma de 1 a %u = %u\n", n, res);
    return 0;
}
