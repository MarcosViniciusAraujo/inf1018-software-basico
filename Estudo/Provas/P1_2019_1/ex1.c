#include <stdio.h>
void dump(void *p, int n)
{
    unsigned char *p1 = (unsigned char *)p;
    while (n--)
    {
        printf("%p - %02x\n", p1, *p1);
        p1++;
    }
}
struct S1
{
    short val_short;
    int val_int;
    char *val_string;
};
struct S2
{
    void *p;
    int i;
    char c;
};
char minha_string[] = "turma 3wb";
struct S1 s1 = {12, 34, minha_string};
struct S2 s2[2] = {{&s1.val_int, -129, 'E' << 4},
                   {&s1.val_string, 1026, 0x55 & 0x0f}};
int main(void)
{
    dump(s2, sizeof(s2));
    return 0;
}
