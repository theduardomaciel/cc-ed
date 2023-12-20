#include <stdio.h>

void insertion_sort(int v[], int size)
{
    int i, j, key;
    for (i = 1; i < size; i++) // O primeiro elemento é considerado ordenado
    {
        key = v[i]; // Elemento a ser inserido na sub-array ordenada
        j = i - 1;  // Índice do último elemento da sub-array ordenada

        // Enquanto o elemento da sub-array ordenada for maior que o elemento a ser inserido
        while ((j >= 0) && (v[j] > key))
        {
            v[j + 1] = v[j]; // Desloca o elemento para a direita
            j--;             // Avança para o próximo elemento da sub-array ordenada
        }

        v[j + 1] = key; // Insere o elemento na posição correta
    }
}

#define SIZE 6

int main()
{
    int v[] = {5, 2, 4, 6, 1, 3};

    for (int i = 0; i < SIZE; i++)
        printf("%d ", v[i]);

    insertion_sort(v, SIZE);

    printf("\n");

    for (int i = 0; i < SIZE; i++)
        printf("%d ", v[i]);

    printf("\n");

    return 0;
}