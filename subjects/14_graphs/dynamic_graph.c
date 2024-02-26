#include <stdlib.h>
#include <stdio.h>

struct ajd_list
{
    int vertex;
    struct ajd_list *next;
};

typedef struct ajd_list ajd_list;

struct graph
{
    int num_vertices;
    ajd_list **adjacency_lists;
    short *visited;
};

typedef struct graph graph;

// Abstract Data Type (ADT)

graph *create_graph();
void add_edge(graph *graph, int vertex1, int vertex2);
void dfs(graph *graph, int source);
void bfs(graph *graph, int source);
void print_graph(graph *graph);

// Implementation

graph *create_graph(int num_vertices)
{
    graph *new_graph = (graph *)malloc(sizeof(graph));
    new_graph->num_vertices = num_vertices;
    new_graph->adjacency_lists = (ajd_list **)malloc(num_vertices * sizeof(ajd_list *));
    new_graph->visited = (short *)malloc(num_vertices * sizeof(short));
    int i;
    for (i = 0; i < num_vertices; i++)
    {
        new_graph->adjacency_lists[i] = NULL;
        new_graph->visited[i] = 0;
    }
    return new_graph;
}

ajd_list *create_node(int vertex)
{
    ajd_list *new_node = (ajd_list *)malloc(sizeof(ajd_list));
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

void add_edge(graph *graph, int vertex1, int vertex2)
{
    ajd_list *new_node = create_node(vertex2);
    new_node->next = graph->adjacency_lists[vertex1];
    graph->adjacency_lists[vertex1] = new_node;

    new_node = create_node(vertex1);
    new_node->next = graph->adjacency_lists[vertex2];
    graph->adjacency_lists[vertex2] = new_node;
}

void dfs(graph *graph, int source)
{
    graph->visited[source] = 1;
    printf("Visited %d\n", source);
    ajd_list *adj_list = graph->adjacency_lists[source];
    while (adj_list != NULL)
    {
        if (!graph->visited[adj_list->vertex])
        {
            dfs(graph, adj_list->vertex);
        }
        adj_list = adj_list->next;
    }
}

void bfs(graph *graph, int source)
{
    int queue[graph->num_vertices];
    int front = 0;
    int rear = 0;
    queue[rear] = source;
    graph->visited[source] = 1;
    printf("Visited %d\n", source);
    while (front <= rear)
    {
        int current_vertex = queue[front];
        ajd_list *adj_list = graph->adjacency_lists[current_vertex];
        while (adj_list != NULL)
        {
            if (!graph->visited[adj_list->vertex])
            {
                queue[++rear] = adj_list->vertex;
                graph->visited[adj_list->vertex] = 1;
                printf("Visited %d\n", adj_list->vertex);
            }
            adj_list = adj_list->next;
        }
        front++;
    }
}

void print_graph(graph *graph)
{
    int i;
    for (i = 0; i < graph->num_vertices; i++)
    {
        ajd_list *adj_list = graph->adjacency_lists[i];
        printf("Adjacency list of vertex %d\n", i);
        while (adj_list != NULL)
        {
            printf("%d -> ", adj_list->vertex);
            adj_list = adj_list->next;
        }
        printf("NULL\n");
    }
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

    ajd_list *adj_list = graph->adjacency_lists[source];

    while (adj_list != NULL)
    {
        if (!graph->visited[adj_list->vertex])
        {
            dfs(graph, adj_list->vertex);
        }
        adj_list = adj_list->next;
    }
}

// Breadth First Search (BFS)
// A partir de um vértice, visitamos todos os seus vizinhos possíveis de alcançar a partir do vértice atual.
// Dessa forma, exploramos os vértices vizinhos primeiro antes de movermos para um novo nível de vizinhança.

struct queue_node
{
    int item;
    queue_node *next;
};

typedef struct queue_node queue_node;

struct queue
{
    int current_size;
    queue_node *head;
    queue_node *tail;
};

typedef struct queue queue;

queue *create_queue()
{
    queue *new_queue = (queue *)malloc(sizeof(queue));
    new_queue->current_size = 0;
    new_queue->head = NULL;
    new_queue->tail = NULL;
    return new_queue;
}

int is_queue_empty(queue *queue)
{
    return queue->current_size == 0;
}

void enqueue(queue *queue, int item)
{
    queue_node *new_node = (queue_node *)malloc(sizeof(queue_node));
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
    if (is_queue_empty(queue))
    {
        printf("Queue underflow\n");
        return -1;
    }
    else
    {
        queue_node *node = queue->head;
        int dequeued = node->item;
        queue->head = queue->head->next;
        if (queue->head == NULL)
        {
            queue->tail = NULL;
        }
        free(node);
        queue->current_size--;
        return dequeued;
    }
}

void bfs(graph *graph, int source)
{
    queue *queue = create_queue();

    int dequeued;

    ajd_list *adj_list = graph->adjacency_lists[source];
    graph->visited[source] = 1;

    enqueue(queue, source);

    while (!is_queue_empty(queue))
    {
        dequeued = dequeue(queue);
        printf("Visited %d\n", dequeued);
        adj_list = graph->adjacency_lists[dequeued];
        while (adj_list != NULL)
        {
            if (!graph->visited[adj_list->vertex])
            {
                graph->visited[adj_list->vertex] = 1;
                enqueue(queue, adj_list->vertex);
            }
            adj_list = adj_list->next;
        }
    }
}

int main()
{
    graph *graph = create_graph(4);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 2);
    add_edge(graph, 1, 2);
    add_edge(graph, 2, 3);
    print_graph(graph);
    dfs(graph, 2);
    return 0;
}