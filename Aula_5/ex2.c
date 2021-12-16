#include <stdio.h>

struct X
{
    int a;
    short b;
    int c;
} x = {0xa1a2a3a4, 0xb1b2, 0xc1c2c3c4};

void dump(void *p, int n)
{
    unsigned char *p1 = p;
    while (n--)
    {
        printf("%p - %02x\n", p1, *p1);
        p1++;
    }
}

int main()
{

    printf("dump de int a:\n");
    dump(&x.a, sizeof(x.a));
    printf("\n");

    printf("dump de int b:\n");
    dump(&x.b, sizeof(x.b));
    printf("\n");

    printf("dump de int c:\n");
    dump(&x.c, sizeof(x.c));
    printf("\n");

    printf("Tamanho da estrutra: %d", sizeof(x.a) + sizeof(x.b) + sizeof(x.c));

    return 0;
}