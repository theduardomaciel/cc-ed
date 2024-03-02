#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
-> Descrição
    Dado um *"grafo direcionado acíclico", você deve:
    -   imprimir todas as folhas em **"ordem lexicográfica";
    -   remover as folhas da árvore;
    -   repetir o procedimento até que não existam mais nós.

-> Formato de entrada
    Consiste de vários casos de teste.
    Cada caso de teste começa com uma linha contendo o inteiro n indicando o número linhas.
    Cada linha possui duas strings A e B, indicando que existe uma aresta do nó A para o nó B. A e B possuem no máximo 15 caracteres formados pelas letras maiúsculas A...Z;

    **O número máximo de nós é 100.**

-> Formato de saída
    Para cada caso de teste imprima uma linha contendo cada um dos nós folhas, de acordo com a descrição do problema.
*/

/*
    *grafo direcionado acíclico:
        - Não possui ciclos, ou seja, não é possível sair de um nó e voltar para ele mesmo.
        - As arestas são direcionadas, ou seja, se existe uma aresta de A para B, não necessariamente existe uma aresta de B para A.

    **ordem lexicográfica: é a ordem em que as palavras são ordenadas em um dicionário.
    Dizemos que uma string  s  é lexicograficamente menor que uma string  t  se o primeiro caractere de s que difere do correspondente caractere de t é menor que o caractere de t.  Assim, para decidir se s é lexicograficamente menor que t basta procurar a primeira posição, digamos k, em que as duas strings diferem. Se s[k] < t[k] então s é lexicograficamente menor que t.  Se s[k] > t[k] então t é lexicograficamente menor que s.  Se k não está definido então s e t são iguais ou uma é prefixo próprio da outra; no segundo caso, a string mais curta é lexicograficamente menor que a mais longa.
*/

#define MAX_STRING_LENGTH 15
#define MAX_VERTICES 100

// Definição da estrutura do nó da lista de adjacência
typedef struct node
{
    char data[MAX_STRING_LENGTH + 1]; // +1 para o caractere nulo
    struct node *next;
} node;

// Definição da estrutura do grafo
typedef struct
{
    node *adjacency_list[MAX_VERTICES];
    int num_vertices;
} directed_acyclic_graph;

// Função para inicializar o grafo
directed_acyclic_graph *create_graph()
{
    directed_acyclic_graph *new_graph = (directed_acyclic_graph *)malloc(sizeof(directed_acyclic_graph));

    new_graph->num_vertices = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        new_graph->adjacency_list[i] = NULL;
    }

    return new_graph;
}

// Função para adicionar um vértice ao grafo
void addVertex(directed_acyclic_graph *graph, const char *vertexData)
{
    if (graph->num_vertices < MAX_VERTICES)
    {
        node *newNode = (node *)malloc(sizeof(node));
        strncpy(newNode->data, vertexData, MAX_STRING_LENGTH);
        newNode->data[MAX_STRING_LENGTH] = '\0'; // Garante que a string é terminada corretamente
        newNode->next = NULL;

        graph->adjacency_list[graph->num_vertices++] = newNode;
    }
}

// Função para adicionar uma aresta direcionada entre dois vértices
void add_edge(directed_acyclic_graph *graph, const char *sourceVertex, const char *destinationVertex)
{
    int sourceIndex = -1, destinationIndex = -1;

    // Procura os índices dos vértices source e destination
    for (int i = 0; i < graph->num_vertices; i++)
    {
        if (strcmp(graph->adjacency_list[i]->data, sourceVertex) == 0)
        {
            sourceIndex = i;
        }
        if (strcmp(graph->adjacency_list[i]->data, destinationVertex) == 0)
        {
            destinationIndex = i;
        }
    }

    // Se o vértice source não existir, adiciona-o ao grafo
    if (sourceIndex == -1)
    {
        addVertex(graph, sourceVertex);
        sourceIndex = graph->num_vertices - 1;
    }

    // Se o vértice destination não existir, adiciona-o ao grafo
    if (destinationIndex == -1)
    {
        addVertex(graph, destinationVertex);
        destinationIndex = graph->num_vertices - 1;
    }

    // Adiciona a aresta direcionada
    node *newNode = (node *)malloc(sizeof(node));
    strncpy(newNode->data, destinationVertex, MAX_STRING_LENGTH);
    newNode->data[MAX_STRING_LENGTH] = '\0';
    newNode->next = graph->adjacency_list[sourceIndex]->next;
    graph->adjacency_list[sourceIndex]->next = newNode;
}

// Função para imprimir o grafo
void print_graph(directed_acyclic_graph *graph)
{
    printf("Graph:\n");
    for (int i = 0; i < graph->num_vertices; i++)
    {
        node *current = graph->adjacency_list[i];
        printf("%s -> ", current->data);

        current = current->next;
        while (current != NULL)
        {
            printf("%s -> ", current->data);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int isLeaf(node *vertex)
{
    return vertex != NULL; // && vertex->next == NULL;
}

void removeLeaf(directed_acyclic_graph *graph, int vertexIndex)
{
    node *current = graph->adjacency_list[vertexIndex];
    node *previous = NULL;

    while (current != NULL && current->next != NULL)
    {
        previous = current;
        current = current->next;
    }

    if (current != NULL)
    {
        // Remove a última aresta (folha)
        free(current);
        if (previous != NULL)
        {
            previous->next = NULL;
        }
        else
        {
            graph->adjacency_list[vertexIndex] = NULL;
        }
    }
}

// Função de comparação para a função qsort
// Função de comparação personalizada para a função qsort
int compare_strings(const void *a, const void *b)
{
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    // Encontrar a primeira posição onde as strings diferem
    int k = 0;
    while (str1[k] != '\0' && str2[k] != '\0' && str1[k] == str2[k])
    {
        k++;
    }

    // Comparar os caracteres nessas posições
    return str1[k] - str2[k];
}

void print_graph_leafs(directed_acyclic_graph *graph)
{
    char **leaves = malloc(graph->num_vertices * sizeof(char *));
    int numLeaves = 0;

    // Coleta todas as folhas em um array
    for (int i = 0; i < graph->num_vertices; i++)
    {
        if (isLeaf(graph->adjacency_list[i]))
        {
            printf("UNORDERED VERTEX: %s\n", graph->adjacency_list[i]->data);
            leaves[numLeaves] = strdup(graph->adjacency_list[i]->data);
            removeLeaf(graph, i);
            numLeaves++;
        }
    }

    // Ordena o array de folhas lexicograficamente
    qsort(leaves, sizeof(leaves) / sizeof(leaves[0]), sizeof(char *), compare_strings);

    // Imprime as folhas ordenadas
    printf("Leaves in lexicographic order:\n");
    for (int i = 0; i < numLeaves; i++)
    {
        printf("VERTEX: %s\n", leaves[i]);
        free(leaves[i]); // Liberar memória alocada por strdup
    }

    free(leaves); // Liberar memória alocada para o array de folhas
}

// Função para liberar a memória alocada pelo grafo
void free_graph(directed_acyclic_graph *graph)
{
    for (int i = 0; i < graph->num_vertices; i++)
    {
        node *current = graph->adjacency_list[i];
        while (current != NULL)
        {
            node *next = current->next;
            free(current);
            current = next;
        }
    }
}

int main()
{
    int n;

    while (scanf("%d", &n) != EOF)
    {
        directed_acyclic_graph *graph = create_graph();

        for (int i = 0; i < n; i++)
        {
            char a[15], b[15];
            scanf("%s %s", a, b);
            add_edge(graph, a, b);
        }

        // print_graph(graph);
        print_graph_leafs(graph);

        // free_graph(graph);
    }

    return 0;
}