#include <stdio.h>

void quick_sort(int *v, int a, int b)
{
    if (a > b)
    {
        return;
    }

    int left = a;
    int right = b;
    int pivot = v[a + (b - a) / 2]; // Seleciona o elemento do meio como pivô

    // Enquanto a posição da esquerda for menor ou igual a posição da direita
    while (left <= right)
    {
        // Enquanto o elemento da esquerda for menor que o pivô, avança para a direita
        while (v[left] < pivot)
            left++;

        // Enquanto o elemento da direita for maior que o pivô, avança para a esquerda
        while (v[right] > pivot)
            right--;

        // Se o elemento da esquerda for maior que o pivô E o elemento da direita for menor que o pivô, troca os elementos
        if (left <= right)
        {
            int aux = v[left];
            v[left] = v[right];
            v[right] = aux;
            left++;
            right--;
        }
    }

    quick_sort(v, a, right);
    quick_sort(v, left, b);
}

int main()
{
    int SIZE = 6;

    int v[] = {5, 2, 4, 6, 1, 3};

    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", v[i]);
    }

    quick_sort(v, 0, SIZE - 1);

    printf("\n");

    for (int i = 0; i < SIZE; i++)
        printf("%d ", v[i]);

    printf("\n");

    return 0;
}

/*
    CODE WITH SWAP FUNCTION:

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
 */