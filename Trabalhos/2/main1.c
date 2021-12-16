#include <stdio.h>
#include <stdlib.h>
#include "cria_func.h"

#define MAX 10
#define NUM_PARAM 2

/******************* Três casos de testes *******************/
typedef int (*func_ptr)(int x);
typedef int (*func_ptr2)();
typedef int (*func_ptr3)(int x, int y);

/*********************** Função testada ********************/
int mult(int x, int y)
{
    return x * y;
}

int main()
{
    func_ptr f_mult;
    func_ptr2 f_mult2;
    func_ptr3 f_mult3;

    /******************** Test case 1 *********************/
    DescParam FixVariavel[NUM_PARAM];

    FixVariavel[0].tipo_val = INT_PAR;
    FixVariavel[0].orig_val = FIX;
    FixVariavel[0].valor.v_int = 10;

    FixVariavel[1].tipo_val = INT_PAR;
    FixVariavel[1].orig_val = PARAM;
    

    f_mult = (func_ptr)cria_func(mult, FixVariavel, NUM_PARAM);
    
    for (int i = 1; i <= MAX; i++)
    {
        printf("#%d = %d\n", i, f_mult(i));
    }
    
    /******************** Test case 2 *********************/
    DescParam FixFix[NUM_PARAM];

    FixFix[0].tipo_val = INT_PAR;
    FixFix[0].orig_val = FIX;
    FixFix[0].valor.v_int = 5;

    FixFix[1].tipo_val = INT_PAR;
    FixFix[1].orig_val = FIX;
    FixFix[1].valor.v_int = 7;

    f_mult2 = (func_ptr2)cria_func(mult, FixFix, NUM_PARAM);
    
    printf("%d\n", f_mult2());
    
    /******************** Test case 3 *********************/
    DescParam VariaVaria[NUM_PARAM];

    VariaVaria[0].tipo_val = INT_PAR;
    VariaVaria[0].orig_val = PARAM;

    VariaVaria[1].tipo_val = INT_PAR;
    VariaVaria[1].orig_val = PARAM;

    f_mult3 = (func_ptr3)cria_func(mult, VariaVaria, NUM_PARAM);

    printf("%d\n", f_mult3(3, 2));
    
    /******************** Liberar funções *******************/
    
    libera_func(f_mult);

    libera_func(f_mult2);

    libera_func(f_mult3);
    
    /********************************************************/
    return 0;
}