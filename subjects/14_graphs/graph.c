#include <stdlib.h>
#include <stdio.h>
#include "../12_queues/queue.c"

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

    // Como o grafo não é direcionado, adicionamos a aresta no outro sentido.
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

/**
 * Performs a depth-first search (DFS) traversal on the given graph starting from the specified source vertex.
 *
 * @param graph The graph to perform the DFS traversal on.
 * @param source The source vertex to start the traversal from.
 */
void dfs(graph *graph, int source)
{
    graph->visited[source] = 1;
    printf("%d ", source);

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

/**
 * Performs a breadth-first search (BFS) traversal on a graph starting from a given source vertex.
 *
 * @param graph The graph to perform the BFS traversal on.
 * @param source The source vertex to start the traversal from.
 */
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
            if (!graph->visited[adj_list->item])
            {
                printf("%d ", adj_list->item);
                graph->visited[adj_list->item] = 1;
                enqueue(queue, adj_list->item);
            }
            adj_list = adj_list->next;
        }
    }
}

void print_graph(graph *graph)
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        adj_list *adj_list = graph->vertices[i];
        if (adj_list != NULL)
        {
            printf("Vertex %d: ", i);
            while (adj_list != NULL)
            {
                printf("%d -> ", adj_list->item);
                adj_list = adj_list->next;
            }
            printf("\n");
        }
    }
}

/*
add_edge(undirected_graph, 1, 2);
add_edge(undirected_graph, 1, 3);
add_edge(undirected_graph, 1, 5);
// add_edge(undirected_graph, 2, 1);
add_edge(undirected_graph, 2, 4);
add_edge(undirected_graph, 2, 5);
// add_edge(undirected_graph, 3, 1);
add_edge(undirected_graph, 3, 6);
add_edge(undirected_graph, 3, 7);
add_edge(undirected_graph, 4, 1);
// add_edge(undirected_graph, 4, 2);
add_edge(undirected_graph, 4, 5);
// add_edge(undirected_graph, 5, 1);
// add_edge(undirected_graph, 5, 2);
// add_edge(undirected_graph, 5, 4);
// add_edge(undirected_graph, 6, 3);
add_edge(undirected_graph, 6, 7);
// add_edge(undirected_graph, 7, 3);
// add_edge(undirected_graph, 7, 6);
*/

int main()
{
    graph *undirected_graph = create_graph();
    add_edge(undirected_graph, 6, 4);
    add_edge(undirected_graph, 6, 9);
    add_edge(undirected_graph, 9, 1);
    add_edge(undirected_graph, 9, 2);
    add_edge(undirected_graph, 1, 5);
    add_edge(undirected_graph, 1, 3);

    // print_graph(undirected_graph);
    graph *graph_copy = create_graph();
    for (int i = 0; i < MAX_SIZE; i++)
    {
        graph_copy->vertices[i] = undirected_graph->vertices[i];
        graph_copy->visited[i] = undirected_graph->visited[i];
    }

    printf("DFS: ");
    dfs(undirected_graph, 6);
    printf("\n");

    printf("BFS: ");
    bfs(graph_copy, 6);
    printf("\n");

    return 0;
}