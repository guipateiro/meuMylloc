#include <stdio.h>
#include <unistd.h>
#include "meuAlocador.h"
//#include "meuAlocador2.h"

extern void *topoInicialHeap;
extern void *ponteiroAtual;
 
int main(){
    printf("meu malloc totalmente original 100 por cento, confia\n");
    fflush(stdout);
    iniciaAlocador();
    void *a,*b ,*c, *d, *e;

    iniciaAlocador();
    imprimeMapa();
    a=alocaMem(240);
    imprimeMapa();
    b=alocaMem(240);
    imprimeMapa();
    liberaMem(a);
    imprimeMapa();
    c=alocaMem(50);
    imprimeMapa();
    //liberaMem(a);
    //imprimeMapa();
    a=alocaMem(50);
    imprimeMapa();
    d=alocaMem(300);
    imprimeMapa();
    liberaMem(b);
    imprimeMapa();
    e=alocaMem(50);
    imprimeMapa();
    liberaMem(c);
    imprimeMapa();
    c=alocaMem(50);
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