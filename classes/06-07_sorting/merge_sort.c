#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Função para mesclar (realizar o merge de) duas sub-arrays de arr[].
// A primeira sub-array é arr[l..m]
// A segunda sub-array é arr[m + 1..r]
void merge(int arr[], int l, int m, int r, bool isDescending)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Arrays temporárias
    int L[n1], R[n2];

    // Copia os dados para as arrays temporárias L[] e R[]
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }

    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    // Mescla (merge) as arrays temporárias de volta em arr[l..r]

    // Index inicial da primeira sub-array
    i = 0;

    // Index inicial da segunda sub-array
    j = 0;

    // Index inicial da sub-array mesclada (merged sub-array)
    k = l;
    while (i < n1 && j < n2)
    {
        if (isDescending)
        {
            if (L[i] >= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
        }
        else
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                i++;
            }
            else
            {
                arr[k] = R[j];
                j++;
            }
        }

        k++;
    }

    // Copia os elementos restantes de L[], se houver algum
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver algum
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// 1 é utilizado para o index da esquerda e r é utilizado para o index da direita da sub-array de arr que será ordenada

// Função principal que ordena arr[l..r] usando
// merge()
void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        // A mesma coisa que (left + right) / 2, mas evita o overflow para left e right grandes
        int middle = left + (right - left) / 2;

        // Ordena a primeira e a segunda metade
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Junta as metades ordenadas
        merge(arr, left, middle, right, true);
    }
}

void print(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        printf("%d ", A[i]);
    }

    printf("\n");
}

int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("A array dada era \n");
    print(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nA array ordenada é \n");
    print(arr, arr_size);
    return 0;
}