#ifndef __MEUALOCADOR2__
#define __MEUALOCADOR2__

extern void *topoInicialHeap;
extern void *ponteiroAtual;

void iniciaAlocador();
void finalizaAlocador();
void *alocaMem(long int);
int liberaMem(void *);
void imprimeMapa();

#endif
