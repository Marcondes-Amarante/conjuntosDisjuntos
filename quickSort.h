#include <stdio.h>
#include <stdlib.h>


int particionarVetor(int vetor[], int inicio, int fim) {
    int pivo = vetor[fim-1]; // Escolhendo o �ltimo elemento como piv�
    int i = inicio-1;    // �ndice do menor elemento

    for (int j = inicio; j < fim-1; j++) { 
        if (vetor[j] <= pivo) {
            i++; // Incrementa o �ndice do menor elemento
            int aux = vetor[j];
            vetor[j] = vetor[i];
            vetor[i] = aux;
        }
    }

    // Coloca o piv� na posi��o correta
    int aux = vetor[i + 1];
    vetor[i + 1] = vetor[fim-1];
    vetor[fim-1] = aux;

    return i + 1; // Retorna o �ndice do piv�
}

void ordenarQuickSort(int vetor[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particionarVetor(vetor, inicio, fim);

        // Ordenando os elementos antes e depois do piv�
        ordenarQuickSort(vetor, inicio, pivo-1);
        ordenarQuickSort(vetor, pivo+1, fim);
    }
}
