#include <stdio.h>
#include <stdlib.h>

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

graph *initGraph()
{
    graph *g = (graph *)malloc(sizeof(graph));

    for (int i = 0; i < MAX_SIZE; i++)
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

void dfs_recursive(int passages[MAX_SIZE][MAX_SIZE], int visited[MAX_SIZE], int roomsAmount, int currentRoom, int exitRoom, int *pathFound)
{
    if (*pathFound == 1 || visited[currentRoom])
    {
        return;
    }

    visited[currentRoom] = 1;

    if (currentRoom == exitRoom)
    {
        *pathFound = 1;
        return;
    }

    for (int i = 0; i < roomsAmount; i++)
    {
        if (passages[currentRoom][i])
        {
            dfs_recursive(passages, visited, roomsAmount, i, exitRoom, pathFound);
        }
    }
}

int main()
{
    int rooms, steps;
    int from, to;

    scanf("%d %d", &rooms, &steps);

    int passages[MAX_SIZE][MAX_SIZE] = {0};
    int visited[MAX_SIZE] = {0};

    for (int i = 0; i < steps; i++)
    {
        int originRoom, destinationRoom;
        scanf("%d %d", &originRoom, &destinationRoom);

        passages[originRoom][destinationRoom] = 1;
    }

    int exitRoom = rooms - 1;
    int pathFound = 0;

    dfs_recursive(passages, visited, rooms, 0, exitRoom, &pathFound);

    printf(pathFound ? "EXISTE CAMINHO\n" : "NAO EXISTE CAMINHO\n");

    int allRoomsHavePassage = 1;
    for (int i = 0; i < rooms; i++)
    {
        if (!visited[i])
        {
            allRoomsHavePassage = 0;
            break;
        }
    }

    printf(allRoomsHavePassage ? "EH POSSIVEL PASSAR POR TODAS AS SALAS\n" : "NAO EH POSSIVEL PASSAR POR TODAS AS SALAS\n");

    return 0;
}