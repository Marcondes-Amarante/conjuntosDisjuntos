#include <stdio.h>
#include <stdlib.h>

void ordenarInsertionSort(int *vetor){
	
	int elemChave;
	int j;
	
	for(int i=2; i<vetor[0]; i++){
		elemChave = vetor[i];
		
		//itera por todas as posi��es anteriores a i verificando se a mesma � maior que elemChave
		//caso positivo, empurra elemento, ou seja, copia elemento de j para pr�xima posi��o
		j = i-1;
		while(j>=1 && elemChave<vetor[j]){
			vetor[j+1] = vetor[j];
			
			j= j-1;
		}
		
		//copia elemento chave para �ltima posi��o de j
		vetor[j+1] = elemChave;
	}
	
	printf("\nvetor ordenado com sucesso\n");
}
