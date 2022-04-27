#include <stdio.h>
#include <unistd.h>
#include "meuAlocador.h"


/*void iniciaAlocador(){
    topoInicialHeap = sbrk(0);
    ponteiroAtual = topoInicialHeap;
}*/

void *alocaMem(long int num_bytes){
    long int *a = ponteiroAtual;
    void *topoAtual = sbrk(0);
    int flag = 0;

    while(1){
        while(a != topoAtual){
            if (flag == 1 && a == ponteiroAtual)
                break;
            if(a[0] == 0){
                printf("n ");
                if(a[1] > num_bytes + 16){
                    long int num_bytes_old = a[1];
                    a[0] = 1;               //espaco ocupado
                    a[1] = num_bytes; 
                    long int *b = (void*)a + 16 + a[1]; //cria novo espaco b 
                    b[0] = 0;               
                    b[1] = num_bytes_old - num_bytes - 16;
                    ponteiroAtual = b;
                    return ((char*)&a[2]);
                }    
                else if(a[1] >= num_bytes){
                    a[0] = 1;
                    ponteiroAtual = a;
                    return ((char*)&a[2]);
                }
            }
            a = (void*)a + 16 + a[1];
        }
        a = topoInicialHeap;
        flag++;
    }
    long int *info;
    info = (long int *)sbrk(8);
    *info = 1;
    info = (long int *)sbrk(8);
    *info = num_bytes;
    void *endereco = sbrk(num_bytes);
    ponteiroAtual = (void*)endereco + num_bytes;
    return ((char*)endereco);
}

int liberaMem(void *endereco){
    long int *a = topoInicialHeap;
    void *topoAtual = sbrk(0);
    long int *trata;
    trata = endereco;
    trata[-2] = 0;
    long int *b = (void*)a + 16 + a[1];
    while(b != topoAtual && a != topoAtual){
        if(a[0] == 0 && b[0] == 0){
            a[1] += b[1] + 16;
            if(ponteiroAtual == b)
                ponteiroAtual = a;
            b = (void*)b + 16 + b[1];
            if(a[0] == 0 && b[0] == 0 && b != topoAtual){
                a[1] += b[1] + 16;
                b = (void*)b + 16 + b[1];
            } 
        } 
        b = (void*)b + 16 + b[1];   
        a = (void*)a + 16 + a[1];
    }
    endereco = NULL;
    return 1;
}

/*void finalizaAlocador(){
    brk(topoInicialHeap);
}*/

void imprimeMapa(){
    char c;
    long int *a = topoInicialHeap;
    void *topoAtual = sbrk(0);
    //printf("imprimindo...\n");
    //fflush(stdout);
    while(a != topoAtual){
        printf("################");
        if(a[0] == 1)
            c = '+';
        else
            c = '-';
        for(int i = 0; i < a[1]; i++)
            putchar(c);

        a = (void*)a + 16 + (a[1]);
    }
    putchar('\n');
}
