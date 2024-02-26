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
void enqueue(queue *queue, int item);
int dequeue(queue *queue);
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

void enqueue(queue *queue, int item)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = item;
    new_node->next = NULL;

    if (queue->head == NULL)
    {
        queue->head = new_node;
    }
    else
    {
        queue->tail->next = new_node;
    }

    queue->tail = new_node;
    queue->current_size++;
}

int dequeue(queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue underflow\n");
        return -1;
    }

    node *node_to_dequeue = queue->head;
    int dequeued = node_to_dequeue->item;

    queue->head = queue->head->next;
    queue->current_size--;

    if (queue->head == NULL)
    {
        queue->tail = NULL;
    }

    free(node_to_dequeue);
    return dequeued;
}

void print_queue(queue *queue)
{
    node *current = queue->head;
    while (current != NULL)
    {
        printf("%d ", current->item);
        current = current->next;
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