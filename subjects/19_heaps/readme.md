# Heap

## Introdução

Um heap é uma árvore binária que possui a propriedade de heap, propriedade esta que garante que o valor de um nó é maior (ou menor) que os valores de seus filhos.  
Um heap pode ser representado por um vetor (array), onde o nó `i` possui os filhos `2i` e `2i + 1`.

### Definição

- Para todo nó `i` diferente da raiz, `pai(i) >= i` (max-heap) ou `pai(i) <= i` (min-heap).
- A altura de um heap de `n` elementos é `O(log n)`.
- Deve estar completamente preenchido, exceto talvez pelo último nível, que deve ser preenchido da esquerda para a direita.

## Operações

- **Inserir (insert)**: Adiciona um elemento no heap.
- **Remover (remove)**: Remove um elemento do heap.
- **Construir (build)**: Constrói um heap a partir de um vetor (array).
- **Imprimir (print)**: Imprime os elementos do heap.

| Operação  | Complexidade |
| --------- | ------------ |
| Inserir   | O(log n)     |
| Remover   | O(log n)     |
| Construir | O(n)         |
| Imprimir  | O(n)         |

## Implementação

A implementação de um heap pode ser feita de diversas formas, como por exemplo, utilizando um vetor (array). A escolha da estrutura de dados a ser utilizada depende do problema a ser resolvido.

### Exemplo

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int size;
} Heap;

void init(Heap *h) {
    h->size = 0;
}

void insert(Heap *h, int x) {
    if (h->size == MAX) {
        printf("Heap overflow\n");
        exit(1);
    }
    int i = h->size++;
    while (i > 0 && x > h->data[(i - 1) / 2]) {
        h->data[i] = h->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->data[i] = x;
}

int remove(Heap *h) {
    if (h->size == 0) {
        printf("Heap underflow\n");
        exit(1);
    }
    int x = h->data[0];
    int i = 0;
    while (2 * i + 1 < h->size) {
        int max = 2 * i + 1;
        if (2 * i + 2 < h->size && h->data[2 * i + 2] > h->data[2 * i + 1]) {
            max = 2 * i + 2;
        }
        if (h->data[max] <= h->data[h->size - 1]) {
            break;
        }
        h->data[i] = h->data[max];
        i = max;
    }
    h->data[i] = h->data[--h->size];
    return x;
}

void build(Heap *h, int arr[], int n) {
    for (int i = 0; i < n; i++) {
        insert(h, arr[i]);
    }
}

void print(Heap *h) {
    for (int i = 0; i < h->size; i++) {
        printf("%d ", h->data[i]);
    }
    printf("\n");
}

int main() {
    Heap h;
    init(&h);
    insert(&h, 1);
    insert(&h, 2);
    insert(&h, 3);
    print(&h); // 3 1 2
    remove(&h);
    print(&h); // 2 1
    int arr[] = {3, 2, 1};
    build(&h, arr, 3);
    print(&h); // 3 2 1
    return 0;
}
```

## Referências

- [Heap - Wikipedia](<https://en.wikipedia.org/wiki/Heap_(data_structure)>)
- [Heap - GeeksforGeeks](https://www.geeksforgeeks.org/heap-data-structure/)
- [Heap - CP-Algorithms](https://cp-algorithms.com/data_structures/heap.html)
