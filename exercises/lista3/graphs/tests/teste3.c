#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 15

// Estrutura para representar um nó do grafo
typedef struct Node
{
    char data[MAX_STRING_LENGTH + 1]; // +1 para o caractere nulo '\0'
    struct Node *next;
} Node;

// Estrutura para representar o Grafo
typedef struct Graph
{
    int vertices;
    Node **adjacencyList;
} Graph;

// Função para criar um novo nó
Node *createNode(const char *data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strncpy(newNode->data, data, MAX_STRING_LENGTH);
    newNode->data[MAX_STRING_LENGTH] = '\0'; // Garantir que a string termina com '\0'
    newNode->next = NULL;
    return newNode;
}

// Função para criar um grafo com 'vertices' vértices
Graph *createGraph(int vertices)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacencyList = (Node **)malloc(vertices * sizeof(Node *));

    for (int i = 0; i < vertices; ++i)
        graph->adjacencyList[i] = NULL;

    return graph;
}

// Função para adicionar uma aresta ao grafo
void addEdge(Graph *graph, const char *src, const char *dest)
{
    int srcIndex = src[0] - 'A';
    int destIndex = dest[0] - 'A';

    Node *newNode = createNode(dest);
    newNode->next = graph->adjacencyList[srcIndex];
    graph->adjacencyList[srcIndex] = newNode;

    // Para um grafo não direcionado, descomente as linhas abaixo para adicionar a aresta no sentido contrário
    // Node* reverseNode = createNode(src);
    // reverseNode->next = graph->adjacencyList[destIndex];
    // graph->adjacencyList[destIndex] = reverseNode;
}

// Função de busca por profundidade (DFS)
void DFSUtil(Graph *graph, int vertex, int *visited)
{
    visited[vertex] = 1; // Marcar o vértice como visitado
    printf("%s ", graph->adjacencyList[vertex]->data);

    Node *current = graph->adjacencyList[vertex];
    while (current != NULL)
    {
        int index = current->data[0] - 'A';
        if (!visited[index])
            DFSUtil(graph, index, visited);
        current = current->next;
    }
}

// Função principal para realizar a busca por profundidade no grafo
void DFS(Graph *graph)
{
    int *visited = (int *)malloc(graph->vertices * sizeof(int));

    for (int i = 0; i < graph->vertices; ++i)
        visited[i] = 0; // Inicializar todos os vértices como não visitados

    printf("DFS: ");
    for (int i = 0; i < graph->vertices; ++i)
    {
        if (!visited[i])
            DFSUtil(graph, i, visited);
    }

    printf("\n");

    free(visited);
}

// Função principal
int main()
{
    Graph *graph = createGraph(6); // Criar um grafo com 6 vértices (A, B, C, D, E, F)

    // Adicionar arestas ao grafo
    addEdge(graph, "A", "B");
    addEdge(graph, "A", "C");
    addEdge(graph, "B", "D");
    addEdge(graph, "B", "E");
    addEdge(graph, "C", "F");

    // Realizar a busca por profundidade no grafo
    DFS(graph);

    // Liberar a memória alocada
    free(graph->adjacencyList);
    free(graph);

    return 0;
}
