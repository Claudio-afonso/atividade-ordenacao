#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM1 100
#define TAM2 1000
#define TAM3 10000

void preencherDecrescente(int v[], int n) {
    for (int i = 0; i < n; i++) {
        v[i] = n - i;
    }
}

void copiarVetor(int origem[], int destino[], int n) {
    for (int i = 0; i < n; i++) {
        destino[i] = origem[i];
    }
}

void bubbleSort(int v[], int n, long long *comparacoes, long long *movimentacoes) {
    *comparacoes = 0;
    *movimentacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                *movimentacoes += 3;
            }
        }
    }
}

void selectionSort(int v[], int n, long long *comparacoes, long long *movimentacoes) {
    *comparacoes = 0;
    *movimentacoes = 0;

    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            (*comparacoes)++;
            if (v[j] < v[min]) {
                min = j;
            }
        }
        if (min != i) {
            int temp = v[i];
            v[i] = v[min];
            v[min] = temp;
            *movimentacoes += 3;
        }
    }
}

void testarAlgoritmo(void (*sort)(int[], int, long long*, long long*),
                     char nome[], int tamanho) {

    int *vetor = malloc(tamanho * sizeof(int));
    int *aux = malloc(tamanho * sizeof(int));

    long long comparacoes, movimentacoes;
    clock_t inicio, fim;

    preencherDecrescente(vetor, tamanho);
    copiarVetor(vetor, aux, tamanho);

    inicio = clock();
    sort(aux, tamanho, &comparacoes, &movimentacoes);
    fim = clock();

    double tempo = ((double)(fim - inicio)) * 1000.0 / CLOCKS_PER_SEC;

    printf("%-15s %-10d %-12.2f %-15lld %-15lld\n",
           nome, tamanho, tempo, comparacoes, movimentacoes);

    free(vetor);
    free(aux);
}

int main() {

    printf("\n%-15s %-10s %-12s %-15s %-15s\n",
           "Algoritmo", "Tamanho", "Tempo(ms)", "Comparações", "Movimentações");
    printf("-------------------------------------------------------------------------------\n");

    testarAlgoritmo(bubbleSort, "Bubble Sort", TAM1);
    testarAlgoritmo(bubbleSort, "Bubble Sort", TAM2);
    testarAlgoritmo(bubbleSort, "Bubble Sort", TAM3);

    testarAlgoritmo(selectionSort, "Selection Sort", TAM1);
    testarAlgoritmo(selectionSort, "Selection Sort", TAM2);
    testarAlgoritmo(selectionSort, "Selection Sort", TAM3);

    printf("\nANÁLISE:\n");
    printf("Ambos possuem complexidade O(n²).\n");
    printf("O Selection Sort geralmente realiza menos movimentações que o Bubble Sort.\n");
    printf("Para vetores grandes (10000), ambos apresentam tempo elevado.\n");

    return 0;
}
