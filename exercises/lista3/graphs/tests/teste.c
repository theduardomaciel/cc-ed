#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função de comparação para qsort
int compararStrings(const void *a, const void *b)
{
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    // Encontrar a primeira posição onde as strings diferem
    int k = 0;
    while (str1[k] != '\0' && str2[k] != '\0' && str1[k] == str2[k])
    {
        k++;
    }

    // Comparar os caracteres nessas posições
    return str1[k] - str2[k];
}

// Função para ordenar a lista de strings
void ordenarStrings(char **lista, int tamanho)
{
    qsort(lista, tamanho, sizeof(char *), compararStrings);
}

int main()
{
    // Lista de strings em ordem lexicográfica
    char *strings[] = {"bd", "ab", "abc", "a", "abd", "ac", "acd", "abcd", "ad", "b", "bc", "bcd", "cd", "d", "c"};
    int tamanho = sizeof(strings) / sizeof(strings[0]);

    // Chamada para ordenar as strings
    ordenarStrings(strings, tamanho);

    // Imprimir a lista ordenada
    printf("Lista Ordenada:\n");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%s\n", strings[i]);
    }

    return 0;
}
