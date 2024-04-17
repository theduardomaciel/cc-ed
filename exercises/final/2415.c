#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_SIZE 100

typedef struct adjList
{
    int value;
    struct adjList *next;
} adjList;

typedef struct graph
{
    adjList *vertices[MAX_SIZE];
    short visited[MAX_SIZE];
} graph;

graph *initGraph(int size)
{
    graph *g = (graph *)malloc(sizeof(graph));

    for (int i = 0; i < size; i++)
    {
        g->vertices[i] = NULL;
        g->visited[i] = 0;
    }

    return g;
}

adjList *initAdjList(int value)
{
    adjList *adj = (adjList *)malloc(sizeof(adjList));

    adj->value = value;
    adj->next = NULL;

    return adj;
}

void addEdge(graph *g, int v1, int v2)
{
    adjList *vx = initAdjList(v2);

    vx->next = g->vertices[v1];
    g->vertices[v1] = vx;
}

int minPath(graph *g, int size, int first, int last)
{
    int front = 0, rear = 0;
    int queue[MAX_SIZE]; // fila pra implementar o BFS
    int distances[MAX_SIZE];

    for (int i = 0; i < size; i++)
    {
        distances[i] = INT_MAX;
    }

    queue[0] = first;
    distances[first] = 0;

    while (front <= rear)
    {
        int current = queue[front++]; // Primeiro elemento da fila

        if (current == last)
        {
            return distances[current];
        }

        adjList *adj = g->vertices[current];
        while (adj != NULL)
        {
            // Se o vértice adjacente (adj->value) ainda não foi visitado
            if (distances[adj->value] == INT_MAX)
            {
                queue[++rear] = adj->value;
                distances[adj->value] = distances[current] + 1;
            }
            adj = adj->next;
        }
    }

    return -1; // Se o último vértice não for alcançável a partir do primeiro
}

int main()
{
    int vertices, arestas;

    scanf("%i %i", &vertices, &arestas);

    graph *g = initGraph(vertices);

    for (int i = 0; i < arestas; i++)
    {
        int v1, v2;
        scanf("%i %i", &v1, &v2);

        addEdge(g, v1, v2);
    }

    int first, last;

    scanf("%i %i", &first, &last);

    printf("Tamanho do menor caminho de G: %i", minPath(g, vertices, first, last));

    return 0;
}