# Algoritmo de Huffman

## Introdução

O algoritmo de Huffman é um algoritmo de compressão de dados que utiliza a codificação de Huffman para representar os dados de forma mais eficiente. A codificação de Huffman é um método de compressão que utiliza códigos de tamanho variável para representar os dados, de forma que os caracteres mais frequent

## Implementação

A implementação do algoritmo de Huffman pode ser feita de diversas formas, como por exemplo, utilizando uma árvore de Huffman ou uma fila de prioridade. A escolha da estrutura de dados a ser utilizada depende do problema a ser resolvido.

### Exemplo

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    int frequency;
    struct Node *left;
    struct Node *right;
} node;

typedef struct PriorityQueue {
    int size;
    int capacity;
    node **nodes;
} priority_queue;

priority_queue *create_priority_queue(int capacity) {
    priority_queue *queue = (priority_queue *)malloc(sizeof(priority_queue));
    queue->size = 0;
    queue->capacity = capacity;
    queue->nodes = (node **)malloc(capacity * sizeof(node *));
    return queue;
}

void enqueue(priority_queue *queue, node *new_node) {
    if (queue->size == queue->capacity) {
        return;
    }

    int i = queue->size;
    while (i > 0 && queue->nodes[(i - 1) / 2]->frequency > new_node->frequency) {
        queue->nodes[i] = queue->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->nodes[i] = new_node;
    queue->size++;
}

node *dequeue(priority_queue *queue) {
    if (queue->size == 0) {
        return NULL;
    }

    node *min_node = queue->nodes[0];
    queue->size--;
    node *last_node = queue->nodes[queue->size];
    queue->nodes[0] = last_node;

    int i = 0;
    while (2 * i + 1 < queue->size) {
        int left_child = 2 * i + 1;
        int right_child = 2 * i + 2;
        int min_child = left_child;
        if (right_child < queue->size && queue->nodes[right_child]->frequency < queue->nodes[left_child]->frequency) {
            min_child = right_child;
        }
        if (queue->nodes[min_child]->frequency < last_node->frequency) {
            queue->nodes[i] = queue->nodes[min_child];
            i = min_child;
        } else {
            break;
        }
    }
    queue->nodes[i] = last_node;

    return min_node;
}

node *create_node(char data, int frequency) {
    node *new_node = (node *)malloc(sizeof(node));
    new_node->data = data;
    new_node->frequency = frequency;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

node *build_huffman_tree(char data[], int frequency[], int size) {
    priority_queue *queue = create_priority_queue(size);
    for (int i = 0; i < size; i++) {
        enqueue(queue, create_node(data[i], frequency[i]));
    }

    while (queue->size > 1) {
        node *left = dequeue(queue);
        node *right = dequeue(queue);
        node *parent = create_node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        enqueue(queue, parent);
    }

    return dequeue(queue);
}

void print_huffman_tree(node *root, int level) {
    if (root != NULL) {
        print_huffman_tree(root->right, level + 1);
        for (int i = 0; i < level; i++) {
            printf("    ");
        }
        printf("%c(%d)\n", root->data, root->frequency);
        print_huffman_tree(root->left, level + 1);
    }
}

int main() {
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int frequency[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(data) / sizeof(data[0]);

    node *root = build_huffman_tree(data, frequency, size);
    print_huffman_tree(root, 0);

    return 0;
}
```

## Referências

- [Wikipedia - Huffman coding](https://en.wikipedia.org/wiki/Huffman_coding)
- [GeeksforGeeks - Huffman Coding](https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/)
