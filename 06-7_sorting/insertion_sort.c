#include <stdio.h>

void insertion_sort(int v[], int size)
{
    int i, j, key;
    for (i = 1; i < size; i++)
    {
        key = v[i];
        j = i - 1;
        while ((j >= 0) && (v[j] > key))
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
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

    return 0;
}