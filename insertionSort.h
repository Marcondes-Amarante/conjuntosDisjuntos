#include <stdio.h>
#include <stdlib.h>

void ordenarInsertionSort(int *vetor){
	
	int elemChave;
	int j;
	
	for(int i=2; i<vetor[0]; i++){
		elemChave = vetor[i];
		
		//itera por todas as posições anteriores a i verificando se a mesma é maior que elemChave
		//caso positivo, empurra elemento, ou seja, copia elemento de j para próxima posição
		j = i-1;
		while(j>=1 && elemChave<vetor[j]){
			vetor[j+1] = vetor[j];
			
			j= j-1;
		}
		
		//copia elemento chave para última posição de j
		vetor[j+1] = elemChave;
	}
	
	printf("\nvetor ordenado com sucesso\n");
}
