#include <stdio.h>
#include <math.h>

float foo(double a, float b);

int main()
{
    printf("%f", foo(2.0, 3.0));
    return 0;
}