# Filas

Filas são estruturas de dados que seguem o princípio FIFO (First In, First Out), ou seja, o primeiro elemento a ser inserido é o primeiro a ser retirado.

## Operações

- **Enfileirar (enqueue)**: Adiciona um elemento no final da fila.
- **Desenfileirar (dequeue)**: Remove o primeiro elemento da fila.
- **Frente (front)**: Retorna o primeiro elemento da fila.
- **Tamanho (size)**: Retorna a quantidade de elementos na fila.
- **Vazia (empty)**: Retorna se a fila está vazia.

## Implementação

A implementação de uma fila pode ser feita de diversas formas, como por exemplo, utilizando um vetor ou uma lista encadeada. A escolha da estrutura de dados a ser utilizada depende do problema a ser resolvido.

### Exemplo

```c
#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int front, rear;
} Queue;

void init(Queue *q) {
    q->front = q->rear = -1;
}

int empty(Queue *q) {
    return q->front == -1;
}

int full(Queue *q) {
    return q->rear == MAX - 1;
}

void enqueue(Queue *q, int x) {
    if (full(q)) {
        printf("Queue overflow\n");
        exit(1);
    }
    if (empty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    q->data[q->rear] = x;
}

int dequeue(Queue *q) {
    if (empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    int x = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return x;
}

int front(Queue *q) {
    if (empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    return q->data[q->front];
}

int size(Queue *q) {
    if (empty(q)) {
        return 0;
    }
    return q->rear - q->front + 1;
}

int main() {
    Queue q;
    init(&q);
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    printf("Front: %d\n", front(&q));
    printf("Size: %d\n", size(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Empty: %d\n", empty(&q));
    return 0;
}
```

## Tipos de Fila

- **Fila de Prioridade**: Cada elemento possui uma prioridade associada e a remoção é feita de acordo com a prioridade.
- **Fila Circular**: A última posição da fila está ligada à primeira, formando um círculo.
- **Fila de Duas Pontas (Deque)**: Permite a inserção e remoção de elementos nas duas extremidades da fila.

### Exemplos em C:

#### Fila de Prioridade

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data[MAX];
    int priority[MAX];
    int front, rear;
} PriorityQueue;

void init(PriorityQueue *q) {
    q->front = q->rear = -1;
}

int empty(PriorityQueue *q) {
    return q->front == -1;
}

int full(PriorityQueue *q) {
    return q->rear == MAX - 1;
}

void enqueue(PriorityQueue *q, int x, int p) {
    if (full(q)) {
        printf("Queue overflow\n");
        exit(1);
    }
    if (empty(q)) {
        q->front = q->rear = 0;
    } else {
        q->rear++;
    }
    int i = q->rear;
    while (i > 0 && p > q->priority[i - 1]) {
        q->data[i] = q->data[i - 1];
        q->priority[i] = q->priority[i - 1];
        i--;
    }
    q->data[i] = x;
    q->priority[i] = p;
}

int dequeue(PriorityQueue *q) {
    if (empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    int x = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->front++;
    }
    return x;
}

int front(PriorityQueue *q) {
    if (empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    return q->data[q->front];
}

int size(PriorityQueue *q) {
    if (empty(q)) {
        return 0;
    }
    return q->rear - q->front + 1;
}

int main() {
    PriorityQueue q;
    init(&q);
    enqueue(&q, 1, 3);
    enqueue(&q, 2, 1);
    enqueue(&q, 3, 2);
    printf("Front: %d\n", front(&q));
    printf("Size: %d\n", size(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Empty: %d\n", empty(&q));
    return 0;
}
```

#### Fila Circular

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data[MAX];
    int front, rear;
} CircularQueue;

void init(CircularQueue *q) {
    q->front = q->rear = 0;
}

int empty(CircularQueue *q) {
    return q->front == q->rear;
}

int full(CircularQueue *q) {
    return (q->rear + 1) % MAX == q->front;
}

void enqueue(CircularQueue *q, int x) {
    if (full(q)) {
        printf("Queue overflow\n");
        exit(1);
    }
    q->data[q->rear] = x;
    q->rear = (q->rear + 1) % MAX;
}

int dequeue(CircularQueue *q) {
    if (empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    int x = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    return x;
}

int front(CircularQueue *q) {
    if (empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    return q->data[q->front];
}

int size(CircularQueue *q) {
    return (q->rear - q->front + MAX) % MAX;
}

int main() {
    CircularQueue q;
    init(&q);
    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    printf("Front: %d\n", front(&q));
    printf("Size: %d\n", size(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Dequeue: %d\n", dequeue(&q));
    printf("Empty: %d\n", empty(&q));
    return 0;
}
```

#### Fila de Duas Pontas (Deque)

```c

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int data[MAX];
    int front, rear;
} Deque;

void init(Deque *q) {
    q->front = q->rear = 0;
}

int empty(Deque *q) {
    return q->front == q->rear;
}

int full(Deque *q) {
    return (q->rear + 1) % MAX == q->front;
}

void push_front(Deque *q, int x) {
    if (full(q)) {
        printf("Queue overflow\n");
        exit(1);
    }
    q->front = (q->front - 1 + MAX) % MAX;
    q->data[q->front] = x;
}

void push_back(Deque *q, int x) {
    if (full(q)) {
        printf("Queue overflow\n");
        exit(1);
    }
    q->data[q->rear] = x;
    q->rear = (q->rear + 1) % MAX;
}

int pop_front(Deque *q) {
    if (empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    int x = q->data[q->front];
    q->front = (q->front + 1) % MAX;
    return x;
}

int pop_back(Deque *q) {
    if (empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    q->rear = (q->rear - 1 + MAX) % MAX;
    return q->data[q->rear];
}

int front(Deque *q) {
    if (empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    return q->data[q->front];
}

int back(Deque *q) {
    if (empty(q)) {
        printf("Queue underflow\n");
        exit(1);
    }
    return q->data[(q->rear - 1 + MAX) % MAX];
}

int size(Deque *q) {
    return (q->rear - q->front + MAX) % MAX;
}

int main() {
    Deque q;
    init(&q);
    push_back(&q, 1);
    push_back(&q, 2);
    push_front(&q, 3);
    printf("Front: %d\n", front(&q));
    printf("Back: %d\n", back(&q));
    printf("Size: %d\n", size(&q));
    printf("Pop front: %d\n", pop_front(&q));
    printf("Pop back: %d\n", pop_back(&q));
    printf("Pop back: %d\n", pop_back(&q));
    printf("Empty: %d\n", empty(&q));
    return 0;
}
```

## Referências

- [Fila - Wikipedia](<https://en.wikipedia.org/wiki/Queue_(abstract_data_type)>)
- [Fila - GeeksforGeeks](https://www.geeksforgeeks.org/queue-data-structure/)
- [Fila - Programiz](https://www.programiz.com/dsa/queue)
