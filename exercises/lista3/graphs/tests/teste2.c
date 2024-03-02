#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100
#define MAX_LENGTH 16

typedef struct
{
    char name[MAX_LENGTH];
} Node;

typedef struct
{
    Node nodes[MAX_NODES];
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
    int numNodes;
} Graph;

void initGraph(Graph *graph)
{
    graph->numNodes = 0;
    for (int i = 0; i < MAX_NODES; i++)
    {
        for (int j = 0; j < MAX_NODES; j++)
        {
            graph->adjacencyMatrix[i][j] = 0;
        }
    }
}

void addEdge(Graph *graph, char from[MAX_LENGTH], char to[MAX_LENGTH])
{
    int i, j;
    for (i = 0; i < graph->numNodes; i++)
    {
        if (strcmp(graph->nodes[i].name, from) == 0)
            break;
    }
    if (i == graph->numNodes)
    {
        strcpy(graph->nodes[i].name, from);
        graph->numNodes++;
    }

    for (j = 0; j < graph->numNodes; j++)
    {
        if (strcmp(graph->nodes[j].name, to) == 0)
            break;
    }
    if (j == graph->numNodes)
    {
        strcpy(graph->nodes[j].name, to);
        graph->numNodes++;
    }

    graph->adjacencyMatrix[i][j] = 1;
}

void dfs(Graph *graph, int node, int *visited, char leaves[MAX_NODES][MAX_LENGTH], int *numLeaves)
{
    visited[node] = 1;

    for (int i = 0; i < graph->numNodes; i++)
    {
        if (graph->adjacencyMatrix[node][i] && !visited[i])
        {
            dfs(graph, i, visited, leaves, numLeaves);
        }
    }

    strcpy(leaves[*numLeaves], graph->nodes[node].name);
    (*numLeaves)++;
}

int compareStrings(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

void processTestCase()
{
    Graph graph;
    initGraph(&graph);

    int n;
    scanf("%d", &n);

    char from[MAX_LENGTH], to[MAX_LENGTH];
    for (int i = 0; i < n; i++)
    {
        scanf("%s %s", from, to);
        addEdge(&graph, from, to);
    }

    int visited[MAX_NODES] = {0};
    char leaves[MAX_NODES][MAX_LENGTH];
    int numLeaves = 0;

    for (int i = 0; i < graph.numNodes; i++)
    {
        if (!visited[i])
        {
            dfs(&graph, i, visited, leaves, &numLeaves);
        }
    }

    char *sortedLeaves[MAX_NODES];
    for (int i = 0; i < numLeaves; i++)
    {
        sortedLeaves[i] = leaves[i];
    }

    qsort(sortedLeaves, numLeaves, sizeof(char *), compareStrings);

    for (int i = 0; i < numLeaves; i++)
    {
        printf("%s\n", sortedLeaves[i]);
    }
}

int main()
{
    while (1)
    {
        if (feof(stdin))
            break;
        processTestCase();
    }

    return 0;
}
