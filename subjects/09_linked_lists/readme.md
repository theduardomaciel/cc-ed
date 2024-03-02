# Lista Encadeada

## Introdução

Uma lista encadeada é uma estrutura de dados composta por células que apontam para a próxima célula da lista. A célula inicial é chamada de cabeça e a última célula aponta para `NULL`. Cada célula possui um campo de dados e um ponteiro para a próxima célula.

| Cabeça | -> | Célula 1 | -> | Célula 2 | -> | Célula 3 | -> | NULL |

## Vantagens e Desvantagens

### Vantagens

- Inserção e remoção de elementos em tempo constante.
- Tamanho dinâmico.

### Desvantagens

- Acesso sequencial.
- Necessidade de percorrer a lista para encontrar um elemento.

| Operação           | Complexidade |
| ------------------ | ------------ |
| Inserção no início | O(1)         |
| Inserção no final  | O(n)         |
| Remoção no início  | O(1)         |
| Remoção no final   | O(n)         |
| Acesso             | O(n)         |
| Busca              | O(n)         |

## Exemplo

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node *create(int data) {
    Node *new = malloc(sizeof(Node));
    new->data = data;
    new->next = NULL;
    return new;
}

void insert(Node **head, int data) {
    Node *new = create(data);
    new->next = *head;
    *head = new;
}

void print(Node *head) {
    for (Node *current = head; current != NULL; current = current->next) {
        printf("%d ", current->data);
    }
    printf("\n");
}

int main() {
    Node *head = NULL;
    insert(&head, 3);
    insert(&head, 2);
    insert(&head, 1);
    print(head);
    return 0;
}
```

## Referências

- [Lista Encadeada - Wikipedia](https://en.wikipedia.org/wiki/Linked_list)
- [Lista Encadeada - GeeksforGeeks](https://www.geeksforgeeks.org/data-structures/linked-list/)
