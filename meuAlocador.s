.section .data
    topoInicialHeap: .quad 0
    ponteiroAtual: .quad 0
.globl topoInicialHeap
.globl ponteiroAtual
	maisChar:      	.byte 43
    menosChar:     	.byte 45
    newlineChar:	.byte 10 

    str1:       .string "################"

.section .text

.globl iniciaAlocador
iniciaAlocador:
	pushq %rbp
	movq %rsp,%rbp		#empilha rbp, move rsp

	movq $12, %rax		#syscall para pegar o topo da brk
	movq $0 ,%rdi 
	syscall

	movq %rax , topoInicialHeap		#colocar o topo da brk em topoInicialHeap
	movq %rax , ponteiroAtual		#inicia o ponteiro do next fit no inicio da brk

	popq %rbp           # desempilha rbp
	ret					#retorna 

.globl finalizaAlocador
finalizaAlocador:
    pushq %rbp          #empilha rbp
    movq %rsp, %rbp     # move rsp

    movq topoInicialHeap, %rdi  # enreco inicial da brk em rdi
    movq $12, %rax     
    syscall             # syscall sbrk(topo antigo da pilha)

    popq %rbp           # desempilha rbp
	ret      	        # retorna


.globl alocaMem
alocaMem:
	pushq %rbp                  
  	movq %rsp, %rbp

  	subq $24 ,%rsp		#abres espaco na pilha

  	movq %rdi, %r12		#num_bytes em r12

  	movq ponteiroAtual, %rbx # long int *a = ponteiroAtual;
  	movq %rbx, -8(%rbp)

  	movq $0, %rdi  		#
    movq $12, %rax     	#
    syscall             # void *topoAtual = sbrk(0);
    movq %rax, -16(%rbp)#

    movq $0, -24(%rbp) # int flag = 0;
	movq -8(%rbp) , %rax  #rax = a*

    while1:		 				
    	cmpq $2, -24(%rbp)
    	je fimwhile1		#while(flag != 2)
    	
    	while2:
    		movq -8(%rbp) ,%r8 
    		cmpq %r8, -16(%rbp)
    		je fimwhile2	#while(a != topoAtual)

    		if1:
    		movq -8(%rbp), %r8
    		cmpq $0,  (%r8)
    		jne fimif1		#if(a[0] == 0)

    			if2:
    				movq -8(%rbp),%r8	#rax = a* 
    				addq $8, %r8		#rbx = a* + 8 
    				movq %r12 , %r10	#r10 = num_bytes 
	    			addq $16 , %r10		#r10 = numbaytes +16 
	    			cmpq (%r8), %r10 		
	    			jg elseif2			#if(a[1] > num_bytes + 16)
	    			#compra o segundo com o primeiro	
	    			movq (%r8), %r9	#num_bytes_old 

	    			movq -8(%rbp), %r8	#rax = a* 
	    			movq $1, (%r8)		#a[0] = 1

	    			addq $8, %r8		
	    			movq %r12,(%r8)		#a[1] = num_bytes 

	    			movq -8(%rbp), %r10 #*b = *a
	    			addq $16, %r10		#*b = *a + 16
	    			addq (%r8), %r10 	#*b = *a + 16 + a[1]
	    								#long int *b = (void*)a + 16 + a[1];

	    			movq $0 , (%r10)	# b[0] = 0;

	    			movq %r10 , %r11	
	    			addq $8 , %r11
	    			movq %r9 , (%r11)	#b[1] = num_bytes_old
	    			subq $16 , (%r11)	#b[1] -= 16
	    			subq %r12, (%r11)	#b[1] -= num_bytes

	    			movq %r10, ponteiroAtual

	    			addq $8 , %r8

	  				movq %r8 , %rax 

	  				addq $24, %rsp
	    			popq %rbp           # desempilha rbp
					ret 				#return ((char*)&a[2]);

				elseif2:

					movq -8(%rbp), %r8
					addq $8 ,%r8
					cmpq (%r8), %r12
					jge fimif2			#else if(a[1] >= num_bytes)

					movq -8(%rbp), %r9
					movq $1 , (%r9)		 #a[0] = 1;

					movq %r9, ponteiroAtual

					addq $16 , %r9
					movq %r9 , %rax

					addq $24, %rsp
	    			popq %rbp           # desempilha rbp
					ret 				#return ((char*)&a[2]);

				fimif2:
			fimif1:

			movq -8(%rbp), %r8
			movq %r8 , %r9 
			addq $8 ,%r9
			addq $16 , %r8
			addq (%r9), %r8
			movq %r8, -8(%rbp) 

			jmp while2

			fimwhile2:

		movq topoInicialHeap, %r8
		movq %r8, -8(%rbp)
		addq $1 , -24(%rbp)	
		
		jmp while1

		fimwhile1:

    movq -16(%rbp), %r13	#r13 = sbrk(0)
    addq $16, %r13			#r13 += 16  
    addq %r12, %r13 		#r13 = r13 + 16 + num_bytes

    movq %r13, %rdi  	#
    movq $12, %rax     	#
    syscall             # sbrk += 16 + num_bytes

    movq -16(%rbp), %r13 #r13 = antigo tamanho da brk
    movq $1 ,(%r13)		# r13[0] = 1 
    addq $8 , %r13 		#r13 + 8 		(r13)[1]
    movq %r12 ,(%r13)	# r13[1] = num_bytes 
    addq  $8 ,%r13 
    movq %r13, %rax		#r13[2]

    addq %r12 ,%r13		#r13 +=num_bytes 
    movq %r13, ponteiroAtual

    addq $24, %rsp 
  	popq %rbp           # desempilha rbp
	ret      	        # retorna


.globl liberaMem
liberaMem:

	pushq %rbp
    movq  %rsp, %rbp

	subq $32 ,%rsp

	movq %rdi, -8(%rbp)			#long int *trata = endereco;

    movq topoInicialHeap, %r10
    movq %r10, -16(%rbp)			#long int *a = topoInicialHeap;

    movq $0, %rdi
    movq $12 ,%rax
    syscall
	movq %rax, -24(%rbp)		#void *topoAtual = sbrk(0);

	movq -8(%rbp), %r10
	subq $16, %r10
	movq $0, (%r10)				#trata[-2] = 0;

	movq -16(%rbp), %rax
	movq %rax, %rbx
	addq $8, %rbx
	addq $16,%rax 
	addq (%rbx),%rax 
	movq %rax, -32(%rbp)		#long int *b = (void*)a + 16 + a[1];

	while3:
		movq  -32(%rbp), %r10
		cmpq  %r10, -24(%rbp)
		je fimwhile3

		movq  -16(%rbp), %r10
		cmpq  %r10, -24(%rbp)
		je fimwhile3			#while(b != topoAtual && a != topoAtual)

		if3:
			movq  -32(%rbp), %r10
			cmpq  $0 ,(%r10)
			jne fimif3

			movq  -16(%rbp), %r10
			cmpq  $0 ,(%r10)
			jne fimif3			#if(a[0] == 0 && b[0] == 0)

			movq -16(%rbp),%r8
			addq $8 ,%r8 
			movq -32(%rbp),%r9
			addq $8 ,%r9
			movq (%r9), %r10 
			addq $16 , %r10
			addq %r10 , (%r8)	#a[1] += b[1] + 16;

			movq -32(%rbp),%r10
			addq (%r9), %r10
			addq $16, %r10
			movq %r10, -32(%rbp) #b = (void*)b + 16 + b[1];

			if4:
				movq  -32(%rbp), %r10
				cmpq  $0 ,(%r10)
				jne fimif3

				movq  -16(%rbp), %r10
				cmpq  $0 ,(%r10)
				jne fimif3			#if(a[0] == 0 && b[0] == 0 && b != topoAtual)

				movq  -32(%rbp), %r10
				cmpq  %r10, -24(%rbp)
				je fimwhile3

				movq -16(%rbp),%r8
				addq $8 ,%r8 
				movq -32(%rbp),%r9
				addq $8 ,%r9
				movq (%r9), %r10 
				addq $16 , %r10
				addq %r10 , (%r8)	#a[1] += b[1] + 16;

				movq -32(%rbp),%r10
				addq (%r9), %r10
				addq $16, %r10
				movq %r10, -32(%rbp) #b = (void*)b + 16 + b[1];

			fimif4:	
		fimif3:

		movq -32(%rbp),%r10
		movq %r10, %r9
		addq $8, %r9
		addq (%r9), %r10
		addq $16, %r10
		movq %r10, -32(%rbp) #b = (void*)b + 16 + b[1];

		movq -16(%rbp),%r10
		movq %r10, %r9
		addq $8, %r9
		addq (%r9), %r10
		addq $16, %r10
		movq %r10, -16(%rbp) #a = (void*)a + 16 + a[1];

		jmp while3	

	fimwhile3:

	movq -8(%rbp), %r10
	movq $0 , %r10

	addq $32 ,%rsp

	movq $1 ,%rax 
	
	popq %rbp
	ret


.globl imprimeMapa
imprimeMapa:

    pushq %rbp
    movq  %rsp, %rbp

    subq $16, %rsp

    movq topoInicialHeap, %r8
    movq %r8 , -8(%rbp)			#long int *a = topoInicialHeap;

    movq $0, %rdi
    movq $12 ,%rax		
    syscall					
    movq %rax, -16(%rbp)	#void *topoAtual = sbrk(0);

    while4:
    	movq -8(%rbp) , %r8	
    	cmpq %r8 , -16(%rbp)
    	je fimwhile4		#while(a != topoAtual)

    	movq $str1 , %rdi	# coloca a string em rdi
	   	call printf			#printf("################");

    	ifposs:
    		movq -8(%rbp) , %r8 # a[0]
    		cmpq $1 , (%r8)
    		jne ifposselse	#if(a[0] == 1)
 
    		mov maisChar, %rdi 	# c = '+'
    		jmp fimifposs		#pula pro final do if

    	ifposselse:					#a[0] == 0 

    		mov menosChar, %rdi 	# c = '-'

    	fimifposs:
    						
    	movq $0 , %r15			#i = 0
    	movq -8(%rbp) , %r8			
    	addq $8 ,%r8			#r8 = a + 1
    	movq (%r8), %r14		#r14 = a[1]
    	mov %rdi , %r13			#r13  = c  # eu fiz isso para evitar perder rdi na call de putchar
    	for1:					
    		cmpq %r14 ,%r15
    		jge fimfor1			#for(int i = 0; i < a[1]; i++)

    		mov %r13 , %rdi		# rdi = c 
    		call putchar		#putchar(c);

    		addq $1 , %r15		# i++
    		jmp for1 			# reinicia o for

    	fimfor1:

    	movq -8(%rbp),%r10  #r10 = *a 
		movq %r10, %r9		#r9 = *a
		addq $8, %r9		#r9 = *a + 8 
		addq (%r9), %r10	#r10 += a[1]
		addq $16, %r10		# r10 += 16
		movq %r10, -8(%rbp) #a = (void*)a + 16 + a[1];

    	jmp while4

    fimwhile4:	

    movq newlineChar, %rdi	# c = '\n'
    call putchar			#putchar('\n')

    addq $16, %rsp			#desaloca a pilha
    popq %rbp			
	ret 					#retorna
