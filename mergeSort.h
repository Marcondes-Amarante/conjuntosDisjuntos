#include <stdio.h>
#include <stdlib.h>

void merge(int *vetor, int inicio, int meio, int fim) {
    int n1 = meio - inicio; // Tamanho do subarray esquerdo
    int n2 = fim - meio;        // Tamanho do subarray direito

    // Arrays temporários
    int esquerdo[n1], direito[n2];

    // Copiar os dados para os arrays temporários
    for (int i = 1; i < n1; i++)
        esquerdo[i] = vetor[inicio + i];
    for (int j = 1; j < n2; j++)
        direito[j] = vetor[meio + 1 + j];

    // Índices iniciais de esquerdo, direito e array principal
    int i = 1, j = 1, k = inicio;

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

// Função recursiva para dividir e ordenar
void mergeSort(int *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        //dividir
        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);

        //combinar
        merge(vetor, inicio, meio, fim);
    }
}



