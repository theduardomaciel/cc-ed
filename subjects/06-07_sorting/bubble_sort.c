#include <stdio.h>

void bubble_sort_v1(int *v, int size)
{
    for (int j = 1; j <= size; j++) // Problema: "j" varia de 1 a 5 e os elementos já ordenados estão sendo comparados novamente
    {
        for (int i = 0; i < size - 1; i++)
        {
            if (v[i] > v[i + 1])
                swap(&v[i], &v[i + 1]);
        }
    }
}

void bubble_sort_v2(int *v, int size)
{
    for (int j = size - 1; j >= 0; j--) // Os elementos agora não estão mais sendo comparados com os elementos já ordenados
    {
        for (int i = 0; i < j; i++)
        {
            if (v[i] > v[i + 1])
                swap(&v[i], &v[i + 1]);
        }
    }
}

int main()
{
    int SIZE = 6;

    int v[] = {5, 2, 4, 6, 1, 3};

    for (int i = 0; i < SIZE; i++)
        printf("%d ", v[i]);

    bubble_sort_v3(v, SIZE);

    printf("\n");

    for (int i = 0; i < SIZE; i++)
        printf("%d ", v[i]);

    return 0;
}