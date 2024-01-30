#include <stdio.h>
#include <stdbool.h>

size_t filter(int *arr, int size, bool (*external_function)(int))
{
    // Removemos os valores -1, 0 e 1 do array
    size_t i_write = 0;

    // Percorremos o array, e para cada elemento que satisfaz a condição, o escrevemos na posição i_write
    for (int i_read = 0; i_read < size; i_read++)
    {
        if (external_function(arr[i_read]) == true)
        {
            arr[i_write] = arr[i_read]; // Escrevemos o elemento da posição i_read, na posição i_write
            i_write++;                  // Incrementamos o índice de escrita
        }
    }

    // Retornamos o novo tamanho do array
    return i_write;
}

bool isEven(int n)
{
    return n % 2 == 0;
}

void print(int *v, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    int v[] = {1, 2, 3, 4, 5, 12, 8, 3};

    size_t new_size = filter(v, 8, isEven); // Chamamos a função filter, passando o array v, seu tamanho e a função isEven
    print(v, new_size);                     // Somente os valores pares foram mantidos

    return 0;
}