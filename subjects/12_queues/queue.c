#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 10

typedef struct queue queue;
struct queue
{
    int current_size;
    int head;
    int tail;
    int items[MAX_QUEUE_SIZE];
};

// Abstract Data Type (ADT)

queue *create_queue();
void enqueue(queue *queue, int item);
int dequeue(queue *queue);
int is_empty(queue *queue);
void print_queue(queue *queue);

// -----------====================----------------

queue *create_queue()
{
    queue *new_queue = (queue *)malloc(sizeof(queue));
    new_queue->current_size = 0;
    new_queue->head = 0;
    new_queue->tail = MAX_QUEUE_SIZE - 1;
    return new_queue;
}

int is_empty(queue *queue)
{
    return (queue->current_size == 0);
}

void enqueue(queue *queue, int item)
{
    if (queue->current_size >= MAX_QUEUE_SIZE)
    {
        printf("Queue overflow");
    }
    else
    {
        queue->tail = (queue->tail + 1) % MAX_QUEUE_SIZE;
        queue->items[queue->tail] = item;
        queue->current_size++;
    }
}

int dequeue(queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue underflow");
        return -1;
    }
    else
    {
        int dequeued = queue->items[queue->head];
        queue->head = (queue->head + 1) % MAX_QUEUE_SIZE;
        queue->current_size--;
        return dequeued;
    }
}

void print_queue(queue *queue)
{
    for (int i = queue->head; i < queue->head + queue->current_size; i++)
    {
        printf("%d ", queue->items[i]);
    }
    printf("\n");
}

// -----------====================----------------

int main()
{
    queue *fila = create_queue();
    enqueue(fila, 10);
    enqueue(fila, 20);
    enqueue(fila, 30);
    enqueue(fila, 40);
    enqueue(fila, 50);

    print_queue(fila);

    printf("Dequeued: %d\n", dequeue(fila));
    printf("Dequeued: %d\n", dequeue(fila));

    printf("Queue: ");
    print_queue(fila);

    return 0;
}