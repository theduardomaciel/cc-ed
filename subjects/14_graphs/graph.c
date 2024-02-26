#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 100

struct adj_list
{
    int item; // ou vertex
    struct adj_list *next;
};

typedef struct adj_list adj_list;

struct graph
{
    adj_list *vertices[MAX_SIZE];
    short visited[MAX_SIZE];
};

typedef struct graph graph;

// Abstract Data Type (ADT)

graph *create_graph();
void add_edge(graph *graph, int vertex1, int vertex2);
void dfs(graph *graph, int source);
void bfs(graph *graph, int source);
void print_graph(graph *graph);

// Implementation

graph *create_graph()
{
    graph *new_graph = (graph *)malloc(sizeof(graph));
    int i;
    for (i = 0; i < MAX_SIZE; i++) // ou i = 1; i < MAX_SIZE - 1
    {
        new_graph->vertices[i] = NULL;
        new_graph->visited[i] = 0;
    }
    return new_graph;
}

adj_list *create_adj_list(int item) // ou vertex
{
    adj_list *new_adj_list = (adj_list *)malloc(sizeof(adj_list));
    new_adj_list->item = item;
    new_adj_list->next = NULL;
    return new_adj_list;
}

void add_edge(graph *graph, int vertex1, int vertex2)
{
    adj_list *vertex = create_adj_list(vertex2);
    vertex->next = graph->vertices[vertex1];
    graph->vertices[vertex1] = vertex;

    // Grafo não direcionado. Adiciona a aresta no outro sentido.
    vertex = create_adj_list(vertex1);
    vertex->next = graph->vertices[vertex2];
    graph->vertices[vertex2] = vertex;
}

// Graph Traversals

// Depth First Search (DFS)
// Marcamos um vértice como visitado assim que o alcançamos.
// Em seguida, visitamos um vértice adjacente não visitado.
// Se não houverem vértices não visitados na posição atual, nós voltamos pelos vértices visitados até que encontremos um vértice com um vértice adjacente não visitado, o qual nós visitamos e repetimos o processo.
// Ou seja, repetimos esse processo até que não haja mais vértices adjacentes a serem visitados.

void dfs(graph *graph, int source)
{
    graph->visited[source] = 1;
    printf("Visited %d\n", source);

    adj_list *adj_list = graph->vertices[source];

    while (adj_list != NULL)
    {
        if (!graph->visited[adj_list->item])
        {
            dfs(graph, adj_list->item);
        }
        adj_list = adj_list->next;
    }
}

// Breadth First Search (BFS)
// A partir de um vértice, visitamos todos os seus vizinhos possíveis de alcançar a partir do vértice atual.
// Dessa forma, exploramos os vértices vizinhos primeiro antes de movermos para um novo nível de vizinhança.

struct queue
{
    int items[MAX_SIZE];
    int front;
    int rear;
};

typedef struct queue queue;

queue *create_queue()
{
    queue *new_queue = (queue *)malloc(sizeof(queue));
    new_queue->front = -1;
    new_queue->rear = -1;
    return new_queue;
}

int is_queue_empty(queue *queue)
{
    return queue->front == -1;
}

void enqueue(queue *queue, int value)
{
    if (queue->rear == MAX_SIZE - 1)
    {
        printf("Queue is full\n");
    }
    else
    {
        if (queue->front == -1)
        {
            queue->front = 0;
        }
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

int dequeue(queue *queue)
{
    int item;
    if (is_empty(queue))
    {
        printf("Queue is empty\n");
        item = -1;
    }
    else
    {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear)
        {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

void bfs(graph *graph, int source)
{
    queue *queue = create_queue();

    int dequeued;

    adj_list *adj_list = graph->vertices[source];
    graph->visited[source] = 1;

    enqueue(queue, source);

    while (!is_queue_empty(queue))
    {
        dequeued = dequeue(queue);
        adj_list = graph->vertices[dequeued];

        while (adj_list != NULL)
        {
            int adj_vertex = adj_list->item;

            if (!graph->visited[adj_vertex])
            {
                printf("Visited %d\n", adj_vertex);
                graph->visited[adj_vertex] = 1;
                enqueue(queue, adj_vertex);
            }
            adj_list = adj_list->next;
        }
    }
}