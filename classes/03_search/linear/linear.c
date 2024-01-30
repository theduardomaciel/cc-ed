#include <stdio.h>

int linear_search(int *v, int size, int element)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (v[i] == element)
        {
            return i;
        }
    }
    return -1;
}

#define SIZE 8

int main()
{
    int v[SIZE] = {1, 2, 3, 4, 5, 12, 8, 3};

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");

    int index = linear_search(v, 8, 12);
    printf("O elemento %d está no index: %d\n", v[index], index);

    return 0;
}