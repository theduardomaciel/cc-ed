#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node
{
    int item;
    node *next;
};

typedef struct queue queue;
struct queue
{
    int current_size;
    node *head;
    node *tail;
};

// Abstract Data Type (ADT)

queue *create_queue();
void enqueue_start(queue *queue, int item);
void enqueue_end(queue *queue, int item);
int dequeue_start(queue *queue);
int dequeue_end(queue *queue);
int is_empty(queue *queue);
void print_queue(queue *queue);

// -----------====================----------------

queue *create_queue()
{
    queue *new_queue = (queue *)malloc(sizeof(queue));
    new_queue->current_size = 0;
    new_queue->head = NULL;
    new_queue->tail = NULL;
    return new_queue;
}

int is_empty(queue *queue)
{
    return (queue->current_size == 0);
}

// -----------====================----------------

int main()
{

    return 0;
}