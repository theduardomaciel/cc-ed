# Pilhas

## Introdução

Uma pilha é uma estrutura de dados que segue a regra LIFO (Last In, First Out), ou seja, o último elemento a ser inserido é o primeiro a ser removido.

## Operações

- **Empilhar (push)**: Adiciona um elemento no topo da pilha.
- **Desempilhar (pop)**: Remove o elemento do topo da pilha.
- **Topo (top)**: Retorna o elemento do topo da pilha.
- **Tamanho (size)**: Retorna a quantidade de elementos na pilha.
- **Vazia (empty)**: Retorna se a pilha está vazia.

| Operação | Complexidade |
| -------- | ------------ |
| push     | O(1)         |
| pop      | O(1)         |
| top      | O(1)         |

## Implementação

A implementação de uma pilha pode ser feita de diversas formas, como por exemplo, utilizando um vetor ou uma lista encadeada. A escolha da estrutura de dados a ser utilizada depende do problema a ser resolvido.

### Exemplo

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;
}

int empty(Stack *s) {
    return s->top == -1;
}

int full(Stack *s) {
    return s->top == MAX - 1;
}

void push(Stack *s, int x) {
    if (full(s)) {
        printf("Stack overflow\n");
        exit(1);
    }
    s->data[++s->top] = x;
}

int pop(Stack *s) {
    if (empty(s)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->data[s->top--];
}

int top(Stack *s) {
    if (empty(s)) {
        printf("Stack underflow\n");
        exit(1);
    }
    return s->data[s->top];
}

int main() {
    Stack s;
    init(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    printf("%d\n", top(&s)); // 3
    printf("%d\n", pop(&s)); // 3
    printf("%d\n", top(&s)); // 2
    printf("%d\n", pop(&s)); // 2
    printf("%d\n", top(&s)); // 1
    printf("%d\n", pop(&s)); // 1
    return 0;
}
```

## Referências

- [Pilha - Wikipedia](<https://en.wikipedia.org/wiki/Stack_(abstract_data_type)>)
- [Pilha - GeeksforGeeks](https://www.geeksforgeeks.org/stack-data-structure/)
