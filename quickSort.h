#include <stdio.h>
#include <stdlib.h>


int particionarVetor(int *vetor, int inicio, int fim) {
    int pivo = vetor[fim]; // Escolhendo o �ltimo elemento como piv�
    int i = inicio-1;    // �ndice do menor elemento

    for (int j = inicio; j < fim; j++) { 
        if (vetor[j] <= pivo) {
            i++; // Incrementa o �ndice do menor elemento
            int aux = vetor[j];
            vetor[j] = vetor[i];
            vetor[i] = aux;
        }
    }

    // Coloca o piv� na posi��o correta
    int aux = vetor[i + 1];
    vetor[i + 1] = vetor[fim];
    vetor[fim] = aux;

    return i + 1; // Retorna o �ndice do piv�
}

// Fun��o para ordenar usando QuickSort
void ordenarQuickSort(int *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particionarVetor(vetor, inicio, fim);

        // Ordenando os elementos antes e depois do piv�
        ordenarQuickSort(vetor, inicio, pivo-1);
        ordenarQuickSort(vetor, pivo + 1, fim);
    }
}
