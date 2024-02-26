#include <stdio.h>

// Criamos uma função que recebe um array, seu tamanho e uma função externa
void map(int *arr, int size, int (*external_function)(int))
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = external_function(arr[i]); // Chamamos a função externa para cada elemento do array, e substituímos o valor do elemento pelo valor retornado pela função externa
    }
}

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    return n * factorial(n - 1);
}

int square(int n)
{
    return n * n;
}

void print(int *v, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

#define SIZE 5

int main()
{
    int v[SIZE] = {5, 2, 3, 4, 8};

    map(v, SIZE, factorial); // Chamamos a função map, passando o array v, seu tamanho e a função factorial
    print(v, SIZE);          // Os valores do array foram substituídos pelos fatoriais dos valores originais

    int v2[SIZE] = {8, 18, 6, 3, 15};

    map(v2, SIZE, square); // Chamamos a função map, passando o array v2, seu tamanho e a função square
    print(v2, SIZE);       // Os valores do array foram substituídos pelos quadrados dos valores originais

    // É importante criar outra array para utilizar a função "map" novamente, pois a função altera os valores do array original

    return 0;
}