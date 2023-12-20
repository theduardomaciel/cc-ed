#include <stdio.h>

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void selection_sort(int s[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++) // O array é percorrido n vezes
    {
        min = i;                    // Índice do menor elemento
        for (j = i + 1; j < n; j++) // Percorre o array a partir da posição i + 1
            if (s[j] < s[min])      // Se o elemento for menor que o elemento da posição min
                min = j;            // Atualiza o índice do menor elemento
        swap(&s[i], &s[min]);       // E troca o elemento da posição i com o elemento da posição min
    }
}

#define SIZE 6

int main()
{
    int v[] = {5, 2, 4, 6, 1, 3};

    for (int i = 0; i < SIZE; i++)
        printf("%d ", v[i]);

    selection_sort(v, SIZE);

    printf("\n");

    for (int i = 0; i < SIZE; i++)
        printf("%d ", v[i]);

    printf("\n");

    return 0;
}