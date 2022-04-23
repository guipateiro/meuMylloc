#include <stdio.h>
#include <unistd.h>
#include "meuAlocador.h"
//#include "meuAlocador2.h"

extern void *topoInicialHeap;
extern void *ponteiroAtual;
 
/* void imprimeMapa(){
    char c;
    long int *a = topoInicialHeap;
    void *topoAtual = achabrk();
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
}*/

int main(){
    printf("meu malloc totalmente original 100 por cento, confia\n");
    fflush(stdout);
    iniciaAlocador();
    void *a,*b ,*c;

    iniciaAlocador();
    imprimeMapa();
    a=alocaMem(240);
    imprimeMapa();
    b=alocaMem(50);
    imprimeMapa();
    liberaMem(a);
    imprimeMapa();
    a=alocaMem(50);
    imprimeMapa();
    liberaMem(b);
    imprimeMapa();
    finalizaAlocador();
    /*printf("%p\n", topoInicialHeap);
    fflush(stdout);
    int* primeiro = alocaMem(10);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    int* segundo = alocaMem(15);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    int* terceiro = alocaMem(7);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    liberaMem(primeiro);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    int* novo = alocaMem(30);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    int* novo2 = alocaMem(40);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    int* aloca = alocaMem(300);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    liberaMem(segundo);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    liberaMem(terceiro);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    liberaMem(novo2);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    int* mem = alocaMem(3);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    liberaMem(aloca);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    liberaMem(novo);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);
    liberaMem(mem);
    imprimeMapa();
    printf("\n\n");
    fflush(stdout);*/

}