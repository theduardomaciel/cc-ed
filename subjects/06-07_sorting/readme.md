# Ordenação

## Introdução

Ordenação é o processo de reorganizar um conjunto de itens em uma ordem específica. A ordenação é uma operação fundamental em computação e é utilizada em diversas aplicações, como por exemplo, em sistemas de banco de dados, sistemas de arquivos, sistemas de busca, entre outros.

## Algoritmos de Ordenação

Existem diversos algoritmos de ordenação, cada um com suas vantagens e desvantagens. A escolha do algoritmo de ordenação a ser utilizado depende do tamanho do conjunto de dados, da distribuição dos dados, da memória disponível, entre outros fatores.

### Algoritmos de Ordenação Simples

- [Bubble Sort](https://en.wikipedia.org/wiki/Bubble_sort)
- [Insertion Sort](https://en.wikipedia.org/wiki/Insertion_sort)
- [Selection Sort](https://en.wikipedia.org/wiki/Selection_sort)

### Algoritmos de Ordenação Eficientes

- [Merge Sort](https://en.wikipedia.org/wiki/Merge_sort)
- [Quick Sort](https://en.wikipedia.org/wiki/Quicksort)
- [Heap Sort](https://en.wikipedia.org/wiki/Heapsort)

## Complexidade

A complexidade de um algoritmo de ordenação é uma medida do tempo e/ou espaço necessário para executar o algoritmo. A complexidade de um algoritmo de ordenação depende do tamanho do conjunto de dados, da distribuição dos dados, da memória disponível, entre outros fatores.

| Algoritmo      | Melhor caso | Caso médio | Pior caso  | Estável |
| -------------- | ----------- | ---------- | ---------- | ------- |
| Bubble Sort    | O(n)        | O(n^2)     | O(n^2)     | Sim     |
| Insertion Sort | O(n)        | O(n^2)     | O(n^2)     | Sim     |
| Selection Sort | O(n^2)      | O(n^2)     | O(n^2)     | Não     |
| Merge Sort     | O(n log n)  | O(n log n) | O(n log n) | Sim     |
| Quick Sort     | O(n log n)  | O(n log n) | O(n^2)     | Não     |
| Heap Sort      | O(n log n)  | O(n log n) | O(n log n) | Não     |

> [!TIP]
> **Legenda**:  
> O(n) = Tempo linear  
> O(n^2) = Tempo quadrático  
> O(n log n) = Tempo log-linear  
> Estabilidade = se refere à capacidade de manter a ordem de elementos iguais.

## Exemplo

```c
#include <stdio.h>

void bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    bubble_sort(arr, n);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
```

## Referências

- [Ordenação - Wikipedia](https://en.wikipedia.org/wiki/Sorting_algorithm)
- [Algoritmos de Ordenação - Wikipédia](https://pt.wikipedia.org/wiki/Algoritmo_de_ordenacao)
- [Algoritmos de Ordenação - GeeksforGeeks](https://www.geeksforgeeks.org/sorting-algorithms/)
- [Algoritmos de Ordenação - Programiz](https://www.programiz.com/dsa/sorting-algorithm)
