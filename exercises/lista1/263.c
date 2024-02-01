#include <stdio.h>
#include <stdlib.h>

/*
    Descrição:
        Faça um programa que recebe números de dois arrays inteiros com 20 posições cada e apresente a intersecção dos arrays ordenado de forma crescente.
        Lembrando que a intersecção são os elementos repetidos em ambos os arrays, mas sem repetição (cada número pode aparecer uma única vez no resultado).

    Formato de Entrada:
        Você receberá 40 números inteiros, um por linha, sendo 20 correspondendo ao primeiro array e 20 ao segundo.

    Formato de Saída:
        Você deve imprimir a intersecção entre os dois arrays, um número por linha, ordenado de forma crescente.
        Caso a intersecção seja vazia, imprima a string "VAZIO".
*/

void insertion_sort(int v[], int size)
{
    int i, j, key;
    for (i = 1; i < size; i++) // O primeiro elemento é considerado ordenado
    {
        key = v[i]; // Elemento a ser inserido na sub-array ordenada
        j = i - 1;  // Índice do último elemento da sub-array ordenada

        // Enquanto o elemento da sub-array ordenada for maior que o elemento a ser inserido
        while ((j >= 0) && (v[j] > key))
        {
            v[j + 1] = v[j]; // Desloca o elemento para a direita
            j--;             // Avança para o próximo elemento da sub-array ordenada
        }

        v[j + 1] = key; // Insere o elemento na posição correta
    }
}

// Função para remover elementos duplicados em um array
int remove_duplicates(int arr[], int n)
{
    int k = n;

    // Procuramos por duplicatas a partir de cada elemento
    for (int i = 0; i < k - 1; i++)
    {
        for (int j = i + 1; j < k; j++)
        {
            // Se encontrarmos elementos iguais, removemos o duplicado
            if (arr[i] == arr[j])
            {
                // Deslocamos os elementos à direita do elemento repetido
                for (int l = j; l < k - 1; l++)
                {
                    arr[l] = arr[l + 1];
                }
                k--; // Reduzimos a quantidade de elementos no array
                j--; // Decrementamos j para verificar novamente com o próximo elemento
            }
        }
    }

    return k; // Retorna o novo tamanho do array
}

int main()
{
    int arrayA[20], arrayB[20];

    for (int i = 0; i < 20; i++)
    {
        scanf("%d", &arrayA[i]);
    }

    for (int i = 0; i < 20; i++)
    {
        scanf("%d", &arrayB[i]);
    }

    int intersection[20];
    int k = 0; // Contador para a quantidade de elementos na intersecção

    // Itera pelos elementos de A
    for (int i = 0; i < 20; i++)
    {
        // Itera pelos elementos de B
        for (int j = 0; j < 20; j++)
        {
            // Se o elemento de A for igual ao elemento de B, adicionamos o elemento à intersecção
            if (arrayA[i] == arrayB[j])
            {
                intersection[k] = arrayA[i]; // Adicionamos o elemento à intersecção
                k++;                         // Incrementamos a quantidade de elementos na intersecção
                                             // (dá pra fazer também um: intersection[k++] = arrayA[i]; também)
                break;                       // Uma vez que um elemento é encontrado, não precisamos continuar procurando no arrayB
            }
        }
    }

    // Remove elementos duplicados da interseção e obtém o novo tamanho
    k = remove_duplicates(intersection, k);

    if (k == 0)
    {
        printf("VAZIO\n");
    }
    else
    {
        insertion_sort(intersection, k);

        // printf("Interseção:\n");
        for (int i = 0; i < k; i++)
        {
            printf("%d\n", intersection[i]);
        }
    }

    return 0;
}