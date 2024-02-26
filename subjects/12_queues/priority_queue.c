#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int item;
    int priority;
    struct node *next;
} node;

typedef struct priority_queue
{
    node *head;
} priority_queue;

// Abstract Data Type (ADT)

priority_queue *create_priority_queue();
void enqueue(priority_queue *pq, int i, int p);
node *dequeue(priority_queue *pq);
int maximum(priority_queue *pq);
int is_empty(priority_queue *pq);
void print_priority_queue(priority_queue *pq);

// -----------====================----------------

priority_queue *create_queue()
{
    priority_queue *new_queue = (priority_queue *)malloc(sizeof(priority_queue));
    new_queue->head = NULL;
    return new_queue;
}

int is_empty(priority_queue *priority_queue)
{
    return (priority_queue->head == NULL);
}

void enqueue(priority_queue *pq, int i, int p)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = i;
    new_node->priority = p;
    if ((is_empty(pq)) || (p > pq->head->priority))
    {
        new_node->next = pq->head;
        pq->head = new_node;
    }
    else
    {
        node *current = pq->head;
        while ((current->next != NULL) &&
               (current->next->priority > p))
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

node *dequeue(priority_queue *pq)
{
    if (is_empty(pq))
    {
        printf("Priority Queue underflow\n");
        return NULL;
    }

    node *temp = pq->head;
    pq->head = pq->head->next;
    temp->next = NULL;
    return temp;
}

int maximum(priority_queue *pq)
{
    if (is_empty(pq))
    {
        printf("Priority Queue underflow\n");
        return -1;
    }
    else
    {
        return pq->head->item;
    }
}

void print_queue(priority_queue *priority_queue)
{
    node *current = priority_queue->head;

    printf("Value \t | Priority\n");
    printf("------\t | --------\n");
    while (current != NULL)
    {
        printf("%d \t | %d\n", current->item, current->priority);
        current = current->next;
    }
}

// -----------====================----------------

int main()
{
    priority_queue *fila = create_queue();
    enqueue(fila, 10, 50);
    enqueue(fila, 20, 30);
    enqueue(fila, 30, 45);
    enqueue(fila, 40, 90);
    enqueue(fila, 50, 10);

    print_queue(fila);

    node *dequeued = dequeue(fila);
    printf("Dequeued: %d with priority %d\n", dequeued->item, dequeued->priority);

    dequeued = dequeue(fila);
    printf("Dequeued: %d with priority %d\n", dequeued->item, dequeued->priority);

    print_queue(fila);

    return 0;
}