#include <stdio.h>
#include <stdlib.h>

int binary_search(int *v, int size, int element)
{
    int begin = 0;
    int end = size - 1;
    int middle;

    while (begin <= end) // Enquanto o inicio for menor ou igual ao fim
    {
        middle = (begin + end) / 2; // Pega o meio do vetor
        if (v[middle] < element)    // Se o meio for menor que o elemento
        {
            begin = middle + 1; // O inicio passa a ser o meio + 1
        }
        else if (v[middle] > element) // Se o meio for maior que o elemento
        {
            end = middle - 1; // O fim passa a ser o meio - 1
        }
        else
        {
            return middle; // Se não, retorna o meio
        }
    }
    return -1; // Se não encontrar, retorna -1
}

#define SIZE 10

int main()
{
    int v[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < SIZE; i++)
    {
        scanf("%d", &v[i]);
    }

    int value = binary_search(v, SIZE, 5); // Procura o valor 5 no vetor
    printf("%d\n", value);                 // Retorna o índice do valor 5
}