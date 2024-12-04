#include <stdio.h>
#include <stdlib.h>

void merge(int *vetor, int inicio, int meio, int fim) {
	
    int n1 = meio - inicio+1; // Tamanho do subarray esquerdo
    int n2 = fim - meio;        // Tamanho do subarray direito

    // Arrays temporários
    int esquerdo[n1], direito[n2];

    // Copiar os dados para os arrays temporários
    for (int i = 0; i < n1; i++)
        esquerdo[i] = vetor[inicio + i];
    for (int j = 0; j < n2; j++)
        direito[j] = vetor[meio + 1 + j];

    // Índices iniciais de esquerdo, direito e array principal
    int i = 0, j = 0, k = inicio;

    // Mesclar os subarrays de volta em vetor[inicio...fim]
    while (i < n1 && j < n2) {
        if (esquerdo[i] <= direito[j]) {
            vetor[k] = esquerdo[i];
            i++;
        } else {
            vetor[k] = direito[j];
            j++;
        }
        k++;
    }

    // Copiar os elementos restantes de esquerdo, se houver
    while (i < n1) {
        vetor[k] = esquerdo[i];
        i++;
        k++;
    }

    // Copiar os elementos restantes de direito, se houver
    while (j < n2) {
        vetor[k] = direito[j];
        j++;
        k++;
    }
}

void mergeSort(int *vetor, int inicio, int fim) {
	
	fim = fim-1;
	
    if (inicio < fim) {
    	
    	
        int meio = inicio + (fim - inicio) / 2;
		printf("\nmeio: %d\n", meio);
		
        //dividir vetor ao meio
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio+1, fim);

        //combinar de maneira ordenada partes divididas
        merge(vetor, inicio, meio, fim);
    }
}



