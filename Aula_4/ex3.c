#include <stdio.h>

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

    signed char sc = -1;
    unsigned int ui = sc;

    printf("dump para ui:\n");
    dump(&ui, sizeof(ui));

    return 0;
}