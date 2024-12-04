#include <stdio.h>
#include <stdlib.h>


int particionarVetor(int vetor[], int inicio, int fim) {
    int pivo = vetor[fim-1]; // Escolhendo o último elemento como pivô
    int i = inicio-1;    // Índice do menor elemento

    for (int j = inicio; j < fim-1; j++) { 
        if (vetor[j] <= pivo) {
            i++; // Incrementa o índice do menor elemento
            int aux = vetor[j];
            vetor[j] = vetor[i];
            vetor[i] = aux;
        }
    }

    // Coloca o pivô na posição correta
    int aux = vetor[i + 1];
    vetor[i + 1] = vetor[fim-1];
    vetor[fim-1] = aux;

    return i + 1; // Retorna o índice do pivô
}

void ordenarQuickSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particionarVetor(vetor, inicio, fim);

        // Ordenando os elementos antes e depois do pivô
        ordenarQuickSort(vetor, inicio, pivo-1);
        ordenarQuickSort(vetor, pivo+1, fim);
    }
}
