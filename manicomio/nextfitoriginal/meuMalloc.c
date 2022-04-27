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
    void *a,*b ,*c, *d, *e, *f;

    //Teste noia
    int *coisa[50];

    for (int j = 0; j < 5; ++j){
        //coisa = (int**) alocaMem(50*sizeof(int*));
        for (int i = 0; i < 50; ++i){
            coisa[i] = (int*) alocaMem(i*sizeof(int));   
            printf("aqui tem %i \n" ,i);
            fflush(stdout);  
            imprimeMapa();
        }

        for (int i = 0; i < 50; i+= 2){
            liberaMem(coisa[i]);   
            printf("aqui liberamos %i \n" ,i);
            fflush(stdout);  
            imprimeMapa();
        }

        for (int i = 1; i < 50; i+= 2){
            liberaMem(coisa[i]);   
            printf("aqui liberamos %i \n" ,i);
            fflush(stdout);  
            imprimeMapa();
        }
    }
    //Teste fácil (teoricamente)
    /*a=alocaMem(50);   
    printf("Ponteiro Atual: %p\n", ponteiroAtual);
    printf("aqui tem 50 \n");
    fflush(stdout);  
    imprimeMapa();

    b=alocaMem(60);
    printf("Ponteiro Atual: %p\n", ponteiroAtual);     
    printf("aqui tem 60 \n");
    fflush(stdout); 
    imprimeMapa();

    c=alocaMem(70);
    printf("Ponteiro Atual: %p\n", ponteiroAtual);     
    printf("aqui tem 70 \n");
    fflush(stdout); 
    imprimeMapa();

    printf("aqui liberamos 50 \n");
    liberaMem(a);
    printf("Ponteiro Atual: %p\n", ponteiroAtual);
    fflush(stdout); 
    imprimeMapa();

    a=alocaMem(39);
    printf("Ponteiro Atual: %p\n", ponteiroAtual); 
    printf("aqui tem 39 \n");
    fflush(stdout);  
    imprimeMapa();


    printf("aqui liberamos 60 \n");
    liberaMem(b);
    printf("Ponteiro Atual: %p\n", ponteiroAtual);
    fflush(stdout); 
    imprimeMapa();



    d=alocaMem(30);
    printf("Ponteiro Atual: %p\n", ponteiroAtual); 
    printf("aqui tem 30 \n");
    fflush(stdout);  
    imprimeMapa();

    b=alocaMem(100);
    printf("Ponteiro Atual: %p\n", ponteiroAtual);     
    printf("aqui tem 60 \n");
    fflush(stdout); 
    imprimeMapa();

    e=alocaMem(14);
    printf("Ponteiro Atual: %p\n", ponteiroAtual);     
    printf("aqui tem 15 \n");
    fflush(stdout); 
    imprimeMapa();*/
    
    /*iniciaAlocador();
    imprimeMapa();
    a=alocaMem(50);   
    printf("aqui tem 50 \n");
    fflush(stdout);  
    imprimeMapa();     
    b=alocaMem(240);
    printf("aqui tem 240 \n");
    fflush(stdout); 
    imprimeMapa();
    //liberaMem(a);
    //imprimeMapa();
    c=alocaMem(50);
    printf("aqui tem 50 \n");
    fflush(stdout); 
    imprimeMapa();
    liberaMem(b);
    printf("aqui liberamos 240 \n");
    fflush(stdout); 
    imprimeMapa();
    d=alocaMem(100);
    printf("aqui tem 100 \n");
    fflush(stdout); 
    imprimeMapa();
    f=alocaMem(20);
    printf("aqui alocamos 50 \n");
    fflush(stdout);
    //d=alocaMem(300);
    //imprimeMapa();
    liberaMem(c);
    printf("aqui liberamos 50 \n");
    fflush(stdout); 
    imprimeMapa();
    //e=alocaMem(50);
    //imprimeMapa();
    printf("aqui liberamos 100 \n");
    fflush(stdout); 
    liberaMem(d);
    imprimeMapa();
    //c=alocaMem(50);
    //imprimeMapa();

    e=alocaMem(50);
    printf("aqui alocamos 50 \n");
    fflush(stdout);
    imprimeMapa();*/
    finalizaAlocador();

}