
all:
	as meuAlocador.s -o meuAlocador.o -g
	#gcc -c meuAlocador.c -g 
	gcc -c meuMalloc.c -g
	gcc -static meuMalloc.o meuAlocador.o -o teste -g 


clear:
	rm  *.o

purge: clear
	rm prog