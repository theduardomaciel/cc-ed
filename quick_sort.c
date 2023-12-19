#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void quick_sort(int *array, int size)
{
    if (size <= 1)
    {
        return;
    }
    else
    {
        int begin = 0;
        int end = size - 1;
        int pivot = array[size / 2];

        while (begin < end)
        {
            while (array[begin] < pivot)
            {
                begin++;
            }

            while (array[end] > pivot)
            {
                end--;
            }

            if (begin <= end)
            {
                swap(&array[begin], &array[end]);
            }
        }

        quick_sort(array, end);
        quick_sort(array + begin, size - begin);
    }
}

int main()
{
    int array[5] = {2, 9, 13, 4, 1};

    quick_sort(array, 5);

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", array[i]);
    }

    printf("\n");

    return 0;
}