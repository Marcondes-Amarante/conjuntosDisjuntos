#include <stdio.h>
#include <stdlib.h>

void ordenarBubbleSort(int *vetor){
	
	//variável de controle para verificar se houve troca durante o loop interno
	//se 0, não houve trocas logo o vetor já está ordenado e os laços podem ser interrompidos
	int troca;
	
	for(int i=2; i<=vetor[0]; i++){
		troca = 0;
		for(int j=1; j<=vetor[0]-i; j++){
			if(vetor[j]>vetor[j+1]){
				int aux = vetor[j+1];
				vetor[j+1] = vetor[j];
				vetor[j] = aux;
				
				troca=1;
			}
		}
		
		if(troca==0){
			break;
		}
	}
	
	printf("\nvetor ordenado com sucesso\n");
}
