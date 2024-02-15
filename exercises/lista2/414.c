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

priority_queue *create_priority_queue()
{
    priority_queue *pq = (priority_queue *)malloc(sizeof(priority_queue));
    pq->head = NULL;
    return pq;
}

int is_empty(priority_queue *pq)
{
    return pq->head == NULL;
}

void enqueue(priority_queue *pq, int i, int p)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->item = i;
    new_node->priority = p;
    new_node->next = NULL;

    if (is_empty(pq) || p > pq->head->priority)
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
        return -1;
    }
    else
    {
        return pq->head->item;
    }
}

/*
    void print_priority_queue(priority_queue *pq)
    {
        node *current = pq->head;
        while (current != NULL)
        {
            printf("(%d, %d) ", current->item, current->priority);
            current = current->next;
        }
        printf("\n");
    }
*/

int main()
{
    int tests_amount;
    scanf("%d", &tests_amount);

    while (tests_amount--)
    {
        int students_amount;
        scanf("%d", &students_amount);

        priority_queue *grades = create_priority_queue();

        // Preenchemos a fila de prioridade com as notas e a ordem de chegada
        for (int i = 0; i < students_amount; i++)
        {
            int nota;
            scanf("%d", &nota);
            enqueue(grades, i, nota);
        }

        // Contamos quantos alunos não precisaram trocar de lugar
        int swapped_place_count = 0;
        for (int i = 0; i < students_amount; i++)
        {
            // Para isso, desenfileiramos a fila de prioridade e comparamos a ordem de chegada
            node *temp = dequeue(grades);
            if (temp->item == i) // Se a ordem de chegada for a mesma que a ordem de saída, o aluno não precisou trocar de lugar
            {
                swapped_place_count++;
            }
            free(temp);
        }

        // Por fim, imprimimos a quantidade de alunos que não precisaram trocar de lugar
        printf("%d\n", swapped_place_count);
    }

    return 0;
}
