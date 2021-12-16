#include <stdio.h>

void foo(int a, int b){
	
int soma;
soma = a + b;

for (int i =0; i < soma; i++){
if (i * soma >= 10){
printf("O valor é %d\n" ,i*soma);
}
else{
printf("Valor menor que a constante 10");
}
}
}

