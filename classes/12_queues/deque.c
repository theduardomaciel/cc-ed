#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node
{
    int item;
    node *next;
    node *previous;
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
void enqueue(queue *queue, int item, int on_start);
int dequeue(queue *queue, int on_start);
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

void enqueue(queue *queue, int item, int on_start)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = item;
    new_node->next = NULL;
    new_node->previous = NULL;

    if (queue->head == NULL)
    {
        queue->head = new_node;
        queue->tail = new_node;
    }
    else
    {
        if (on_start)
        {
            new_node->next = queue->head;
            queue->head->previous = new_node;
            queue->head = new_node;
        }
        else
        {
            queue->tail->next = new_node;
            new_node->previous = queue->tail;
            queue->tail = new_node;
        }
    }

    queue->current_size++;
}

int dequeue(queue *queue, int on_start)
{
    if (is_empty(queue))
    {
        printf("Queue underflow\n");
        return -1;
    }
    else
    {
        node *dequeued;
        int dequeued_item;

        if (on_start)
        {
            dequeued = queue->head;
            dequeued_item = dequeued->item;
            queue->head = queue->head->next;
            if (queue->head != NULL)
            {
                queue->head->previous = NULL;
            }
        }
        else
        {
            dequeued = queue->tail;
            dequeued_item = dequeued->item;
            queue->tail = queue->tail->previous;
            if (queue->tail != NULL)
            {
                queue->tail->next = NULL;
            }
        }

        free(dequeued);
        queue->current_size--;
        return dequeued_item;
    }
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
    queue *queue = create_queue();
    enqueue(queue, 10, 1);
    enqueue(queue, 20, 1);
    enqueue(queue, 30, 0);
    enqueue(queue, 40, 0);

    print_queue(queue);

    printf("Dequeued: %d\n", dequeue(queue, 1));
    printf("Dequeued: %d\n", dequeue(queue, 0));

    printf("Queue: ");
    print_queue(queue);

    return 0;
}

/*

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

void enqueue_start(queue *queue, int item)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = item;
    new_node->next = queue->head;
    new_node->previous = NULL;

    if (queue->head == NULL)
    {
        queue->tail = new_node;
    }
    else
    {
        queue->head->previous = new_node;
    }

    queue->head = new_node;
    queue->current_size++;
}

void enqueue_end(queue *queue, int item)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = item;
    new_node->next = NULL;
    new_node->previous = queue->tail;

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

int dequeue_start(queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue underflow\n");
        return -1;
    }

    node *dequeued = queue->head;
    int dequeued_item = dequeued->item;

    queue->head = queue->head->next;
    if (queue->head == NULL)
    {
        queue->tail = NULL;
    }
    else
    {
        queue->head->previous = NULL;
    }

    free(dequeued);
    queue->current_size--;
    return dequeued_item;
}

int dequeue_end(queue *queue)
{
    if (is_empty(queue))
    {
        printf("Queue underflow\n");
        return -1;
    }

    node *dequeued = queue->tail;
    int dequeued_item = dequeued->item;

    queue->tail = queue->tail->previous;
    if (queue->tail == NULL)
    {
        queue->head = NULL;
    }
    else
    {
        queue->tail->next = NULL;
    }

    free(dequeued);
    queue->current_size--;
    return dequeued_item;
}

void print_queue(queue *queue)
{
    node *current = queue->head;
    while (current != NULL)
    {
        printf("%d\n", current->item);
        current = current->next;
    }
}
*/