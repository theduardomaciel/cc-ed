# Lista Duplamente Encadeada

## Introdução

Uma lista duplamente encadeada é uma lista encadeada na qual cada nó possui um ponteiro para o próximo e para o anterior. Isso permite que a lista seja percorrida em ambas as direções.

## Operações

- **Inserir (insert)**: Adiciona um elemento na lista.
- **Remover (remove)**: Remove um elemento da lista.
- **Buscar (search)**: Busca um elemento na lista.
- **Imprimir (print)**: Imprime os elementos da lista.

| Operação | Complexidade |
| -------- | ------------ |
| Inserir  | O(1)         |
| Remover  | O(n)         |
| Buscar   | O(n)         |
| Imprimir | O(n)         |

## Implementação

A implementação de uma lista duplamente encadeada pode ser feita de diversas formas, como por exemplo, utilizando um vetor ou uma lista encadeada. A escolha da estrutura de dados a ser utilizada depende do problema a ser resolvido.

### Exemplo

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int item;
    struct Node *next;
    struct Node *previous;
} node;

node *create_linked_list()
{
    return NULL;
}

node *insert(node *head, int item)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = item;
    new_node->next = head;
    new_node->previous = NULL;

    if (head != NULL)
    {
        head->previous = new_node;
    }

    return new_node;
}

node *search(node *head, int item)
{
    while (head != NULL)
    {
        if (head->item == item)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

node *remove_item(node *head, int item)
{
    node *current = head;
    while (current != NULL && current->item != item)
    {
        current = current->next;
    }

    if (current == NULL)
    {
        return head;
    }

    if (current->previous != NULL)
    {
        current->previous->next = current->next;
    }
    else
    {
        head = current->next;
    }

    if (current->next != NULL)
    {
        current->next->previous = current->previous;
    }

    free(current);
    return head;
}

void print_linked_list(node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    node *head = create_linked_list();
    head = insert(head, 1);
    head = insert(head, 2);
    head = insert(head, 3);
    print_linked_list(head);
    head = remove_item(head, 2);
    print_linked_list(head);
    return 0;
}
```

## Referências

- [Lista Duplamente Encadeada - Wikipedia](https://en.wikipedia.org/wiki/Doubly_linked_list)
- [Lista Duplamente Encadeada - GeeksforGeeks](https://www.geeksforgeeks.org/doubly-linked-list/)
