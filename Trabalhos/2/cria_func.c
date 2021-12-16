/********************************************************************/
/*                    INF108                                        */
/* Marcos Vinicius Araujo Almeida - 1910869 */
/* Eduardo Sardenberg Tavares - 1911328 */
/********************************************************************/

#include <stdio.h>
#include "cria_func.h"
#include <stdlib.h>

#define MAX_PARAM 3
#define MOVQ 0x48
#define AUX_32 0x89

#define VARIAVEL 1
#define FIXO 0

int adicionaPrologo(unsigned char *codigo, int tamanho_atual){
    /*
        Essa função adiciona o prólogo no código de máquina 
        e retorna a proxima posição livre do vetor

        pushq %rbp
        movq  %rsp, %rbp

    */

    codigo[tamanho_atual] = 0x55;
    tamanho_atual++;
    codigo[tamanho_atual] = 0x48;
    tamanho_atual++;
    codigo[tamanho_atual] = 0x89;
    tamanho_atual++;
    codigo[tamanho_atual] = 0xe5;
    tamanho_atual++;

    return tamanho_atual;
}


void exibeVetor(unsigned char *codigo, int tamanho_atual){
    //Exibe o vetor
    // Função para teste
    for (int i = 0; i < tamanho_atual; i++){
        printf("%x\n", codigo[i]);
    }

}

int posicionaParametros(unsigned char *codigo, DescParam params[], int num_param, int tamanho_codigo){

    /*  
        Essa função tem o papel de mover os parêmetros para o lugar certo (já que serão alterados na 
        hora da passagem de argumentos na função na main)
        
        Para 32 bits:
        --> movl %edi, %esi
        --> movl %edi, %edx
        --> movl %esi, %edx

        Para 64 bits:
        --> movl %rdi, %rsi
        --> movl %rdi, %rdx
        --> movl %rsi, %rdx

        retorna a próxima posição livre do vetor
        
    */


    // vetor que será utilizado para mapeando de fixos e variaveis
    int paramVariavel[] = {FIXO, FIXO , FIXO}; 


    if (num_param == 2){
        // caso mais simples: o primeiros é fixo ou ind e o segundo é um param
        // não precisamos alterar mais nenhuma posição
        if (params[0].orig_val != PARAM && params[1].orig_val == PARAM){


            if (params[1].tipo_val == PTR_PAR){
                codigo[tamanho_codigo] = MOVQ;
                tamanho_codigo++;
            }

            
            codigo[tamanho_codigo] = AUX_32;
            tamanho_codigo++;
            codigo[tamanho_codigo] = 0xfe;
            tamanho_codigo++;
        
        }
    }

    else if(num_param == 3){
        //mapeamento das variaveis que são fixos ou não 

        for (int i = 0; i < MAX_PARAM; i++){
            /*
            if (params[i].tipo_val == PARAM){
                paramVariavel[i] = FIXO;
            }
            */
            

            if (params[i].orig_val == PARAM){
                paramVariavel[i] = VARIAVEL;
            }

            else
            {
                paramVariavel[i] = FIXO;
            }
            
        }

        /*
         -- TODAS AS COMBINÇÕES POSSÍVEIS --

            FIX PARAM PARAM 
            FIX PARAM FIX 
            FIX FIX PARAM 
            PARAM FIX PARAM 

        */
        // passando por todos os casos!
        if (paramVariavel[0] == FIXO && paramVariavel[1] == VARIAVEL && paramVariavel[2] == VARIAVEL){
            /*
                Precisamos mover o primeiro parametro para o segundo 
                e o segundo para o terceiro, já que o primeiro é fixo

                mov[s][q] %[e][r]di, %[e][r]si
                mov[s][q] %[e][r]si, %[e][r]dx
                
            */
            if (params[2].tipo_val == PTR_PAR) {
                codigo[tamanho_codigo] = MOVQ;
                tamanho_codigo++;
            }

            codigo[tamanho_codigo] = AUX_32;
            tamanho_codigo++;
            codigo[tamanho_codigo] = 0xf2;
            tamanho_codigo++;

            if (params[1].tipo_val == PTR_PAR){ 
                codigo[tamanho_codigo] = MOVQ;
                tamanho_codigo++;
            }
            codigo[tamanho_codigo] = AUX_32;
            tamanho_codigo++;
            codigo[tamanho_codigo] = 0xfe;
            tamanho_codigo++;
        }

        else if (paramVariavel[0] == FIXO && paramVariavel[1] == VARIAVEL && paramVariavel[2] == FIXO){
            /*
                Nessa precisamos mover o primeiro parametro para o segundo

                mov[l][q] %[e][r]di, %[e][r]si
            */
            if (params[1].tipo_val == PTR_PAR){ 
                codigo[tamanho_codigo] = MOVQ;
                tamanho_codigo++;
            }
            codigo[tamanho_codigo] = AUX_32;
            tamanho_codigo++;
            codigo[tamanho_codigo] = 0xfe;
            tamanho_codigo++;
        }

        else if (paramVariavel[0] == FIXO && paramVariavel[1] == FIXO && paramVariavel[2] == VARIAVEL){

            /*
               mover o primeiro parametro para o terceiro

               mov[l][q] %[e][r]edi, %[e][r]dx
            */
            if (params[2].tipo_val == PTR_PAR) {
                codigo[tamanho_codigo] = MOVQ;
                tamanho_codigo++;
            }
            codigo[tamanho_codigo] = AUX_32;
            tamanho_codigo++;
            codigo[tamanho_codigo] = 0xfa;
            tamanho_codigo++;
        }

        else if (paramVariavel[0] == VARIAVEL && paramVariavel[1] == FIXO && paramVariavel[2] == VARIAVEL){
            /*
                A primeira variavel se mantem no lugar onde está e a segunda vai para terceira posição 
                mov[l][q] %[e][r]si, %[e][r]dx
            */
            if (params[2].tipo_val == PTR_PAR){ 
                codigo[tamanho_codigo] = MOVQ;
                tamanho_codigo++;
            }

            codigo[tamanho_codigo] = AUX_32;
            tamanho_codigo++;
            codigo[tamanho_codigo] = 0xf2;
            tamanho_codigo++;
        }

    }

    return tamanho_codigo;
}

int adicionaFixosInd(unsigned char *codigo, DescParam params[], int n, int tamanho_codigo){
    
    /*
        Essa função adiciona todos os parâmetros fixos e INDs no código de máquina
        (Tanto INT_PAR quanto PTR_PAR)

        retorna a próxima posição livre do vetor
    */

    unsigned char registradores32bits[3] = {0xbf, 0xbe, 0xba}; 
    unsigned char registradores64bits[3] = {0xb9, 0xba, 0xbb}; 
    unsigned char moverRegistradores64bits[3] = {0x39, 0x32, 0x13}; // comandos para 
    // mover registradores de 64 bits
    int i,j, k, l, m;
    long valor;

    for (i = 0; i < n; i++){

        if (params[i].tipo_val == INT_PAR){
            
            
            if (params[i].orig_val == FIX){

                codigo[tamanho_codigo] = registradores32bits[i]; // de acordo com o num de seu param
                tamanho_codigo++;
                // fazer uma bit mask, para sempre pegar o primeiro byte
                int num = params[i].valor.v_int;

                for (j = 0; j < 4; j++) {
                    codigo[tamanho_codigo] = ( num ) & 0xff;
                    tamanho_codigo++;
                    num = num >> 8;
                }
            }

            else if(params[i].orig_val == IND){

                codigo[tamanho_codigo] = 0x49;
                tamanho_codigo++;
                codigo[tamanho_codigo] = registradores64bits[i]; // 64 bits por se tratar de um endereço
                tamanho_codigo++;

                valor = (unsigned long) params[i].valor.v_ptr;
                // adicionando o endereço em little endian
                for (k = 0; k < 8; k++){
                    codigo[tamanho_codigo] = (valor) & 0xff;
                    tamanho_codigo++;
                    valor = valor >> 8;
                }
                codigo[tamanho_codigo] = 0x41;
                tamanho_codigo++;
                codigo[tamanho_codigo] = 0x8b;
                tamanho_codigo++;
                codigo[tamanho_codigo] = moverRegistradores64bits[i];
                tamanho_codigo++;
            }

        }
        
        else if(params[i].tipo_val == PTR_PAR){

            if(params[i].orig_val == FIX){
                codigo[tamanho_codigo] = MOVQ;
                tamanho_codigo++;
                codigo[tamanho_codigo] = registradores32bits[i];
                tamanho_codigo++;

                unsigned long ponteiro = (unsigned long) params[i].valor.v_ptr;
                // adicionando o endereço em little endian
                // a situação muda muito pouco, por se tratar de 64 bits
                for (j = 0; j < 8; j++){
                    codigo[tamanho_codigo] = ponteiro & 0xff;
                    tamanho_codigo++;
                    ponteiro = ponteiro >> 8;
                }
            }

            else if (params[i].orig_val == IND){
                codigo[tamanho_codigo] = 0x49;
                tamanho_codigo++;
                codigo[tamanho_codigo] = registradores64bits[i];
                tamanho_codigo++;

                unsigned long ponteiro = (unsigned long)params[i].valor.v_ptr;
                // adicionando o endereço em little endian
                for (m = 0; m < 8; m++){
                    codigo[tamanho_codigo] = (ponteiro) & 0xff;
                    tamanho_codigo++;
                    ponteiro = ponteiro >> 8;
                }

                codigo[tamanho_codigo] = 0x49;
                tamanho_codigo++;
                codigo[tamanho_codigo] = 0x8b;
                tamanho_codigo++;
                codigo[tamanho_codigo] = moverRegistradores64bits[i];
                tamanho_codigo++;
            }
        }
    }

    return tamanho_codigo;

}

int adicionaCallIndireto(unsigned char *codigo, int tamanho_atual, void *f){
    /*
        Função responsável por adicionar o call indireto no código de máquina

        retorna a próxima posição livre do vetor
    */
    codigo[tamanho_atual] = MOVQ;
    tamanho_atual++;
    codigo[tamanho_atual] = 0xb8;
    tamanho_atual++;

    unsigned long end_func = (unsigned long) f;
    // adicionando o endereço em little endian
    for (int i = 0; i < 8; i++){
        //bit mask

        long primeiro_byte = end_func & 0xff; // pega apenas o primeiro byte

        codigo[tamanho_atual] = primeiro_byte;
        tamanho_atual++;

        end_func = end_func >> 8;

    }

    codigo[tamanho_atual] = 0xff; /*call *%rax*/
    tamanho_atual++;
    codigo[tamanho_atual] = 0xd0;
    tamanho_atual++;

    return tamanho_atual;
}

int adicionaFinalizacao(unsigned char* codigo, int tamanho_codigo)
{

    /*
        Adiciona a finalização

        leave 
        ret
    */
    codigo[tamanho_codigo] = 0xc9; //leave
    tamanho_codigo++;
    codigo[tamanho_codigo] = 0xc3; // ret
    tamanho_codigo++;
    return tamanho_codigo;
}

void *cria_func(void *f, DescParam params[], int n)
{
    
    unsigned char *codigo_maquina = (unsigned char*)malloc(2000*sizeof(unsigned char));
    int tamanho_atual_codigo = 0;

    // Adicionando o prólogo

    tamanho_atual_codigo = adicionaPrologo(codigo_maquina, tamanho_atual_codigo);

    // Posicionando e adicionando os parâmetros!

    tamanho_atual_codigo = posicionaParametros(codigo_maquina, params, n, tamanho_atual_codigo);
    tamanho_atual_codigo = adicionaFixosInd(codigo_maquina, params, n, tamanho_atual_codigo);

    // Adicionando o call indireto

    tamanho_atual_codigo = adicionaCallIndireto(codigo_maquina, tamanho_atual_codigo, f);

    // Adicionando a finalização

    tamanho_atual_codigo = adicionaFinalizacao(codigo_maquina, tamanho_atual_codigo);

    // realocando para o tamanho exato do vetor!

    codigo_maquina = (unsigned char *)realloc(codigo_maquina, tamanho_atual_codigo*sizeof(unsigned char));

    //exibeVetor(codigo_maquina, tamanho_atual_codigo);
    
    return codigo_maquina;

}

void libera_func(void *func)
{
    //libera a função
    free(func);
}