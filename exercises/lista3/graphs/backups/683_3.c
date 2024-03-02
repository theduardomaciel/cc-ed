#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    DFS: imprimindo as folhas

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
    char item[MAX_STRING_LENGTH + 1]; // +1 para o caractere nulo
    struct node *next;
} node;

// Definição da estrutura do grafo
typedef struct
{
    node *adj_list[MAX_VERTICES];
    int visited[MAX_VERTICES];
    int vertices_amount;
} directed_acyclic_graph;

// Função para inicializar o grafo
directed_acyclic_graph *create_graph()
{
    directed_acyclic_graph *new_graph = (directed_acyclic_graph *)malloc(sizeof(directed_acyclic_graph));

    new_graph->vertices_amount = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        new_graph->adj_list[i] = NULL;
        new_graph->visited[i] = 0;
    }

    return new_graph;
}

// Função para adicionar um vértice ao grafo
void add_vertex(directed_acyclic_graph *graph, const char *vertexData)
{
    if (graph->vertices_amount < MAX_VERTICES)
    {
        node *newNode = (node *)malloc(sizeof(node));
        strncpy(newNode->item, vertexData, MAX_STRING_LENGTH);
        newNode->item[MAX_STRING_LENGTH] = '\0'; // Garante que a string termine corretamente
        newNode->next = NULL;

        graph->adj_list[graph->vertices_amount++] = newNode;
    }
}

// Função para adicionar uma aresta direcionada entre dois vértices
void add_edge(directed_acyclic_graph *graph, const char *sourceVertex, const char *destinationVertex)
{
    int sourceIndex = -1, destinationIndex = -1;

    // Procura os índices dos vértices source e destination
    for (int i = 0; i < graph->vertices_amount; i++)
    {
        if (strcmp(graph->adj_list[i]->item, sourceVertex) == 0)
        {
            sourceIndex = i;
        }
        if (strcmp(graph->adj_list[i]->item, destinationVertex) == 0)
        {
            destinationIndex = i;
        }
    }

    // Se o vértice source não existir, adiciona-o ao grafo
    if (sourceIndex == -1)
    {
        add_vertex(graph, sourceVertex);
        sourceIndex = graph->vertices_amount - 1;
    }

    // Se o vértice destination não existir, adiciona-o ao grafo
    if (destinationIndex == -1)
    {
        add_vertex(graph, destinationVertex);
        destinationIndex = graph->vertices_amount - 1;
    }

    // Adiciona a aresta direcionada
    node *newNode = (node *)malloc(sizeof(node));

    strncpy(newNode->item, destinationVertex, MAX_STRING_LENGTH);

    newNode->item[MAX_STRING_LENGTH] = '\0';
    newNode->next = graph->adj_list[sourceIndex]->next;
    graph->adj_list[sourceIndex]->next = newNode;
}

int find_min_vertex_index(directed_acyclic_graph *graph)
{
    int min_index = -1;

    for (int i = 0; i < graph->vertices_amount; i++)
    {
        if (!graph->visited[i] && (min_index == -1 || strcmp(graph->adj_list[i]->item, graph->adj_list[min_index]->item) < 0))
        {
            min_index = i;
        }
    }

    return min_index;
}

void remove_vertex_from_destinations(directed_acyclic_graph *graph, const char *vertex)
{
    for (int i = 0; i < graph->vertices_amount; ++i)
    {
        printf("i: %d\n", i);
        if (graph->adj_list[i] != NULL)
        {
            node *current = graph->adj_list[i];
            node *prev = NULL;

            while (current != NULL)
            {
                if (strcmp(current->item, vertex) == 0)
                {
                    if (prev == NULL)
                    {
                        graph->adj_list[i] = current->next;
                        free(current);
                        current = graph->adj_list[i];
                    }
                    else
                    {
                        prev->next = current->next;
                        free(current);
                        current = prev->next;
                    }
                }
                else
                {
                    prev = current;
                    current = current->next;
                }
            }
        }
    }
}

void remove_vertex(directed_acyclic_graph *graph, int index)
{
    graph->visited[index] = 1;

    if (graph->adj_list[index] != NULL)
    {
        remove_vertex_from_destinations(graph, graph->adj_list[index]->item);

        free(graph->adj_list[index]);
        graph->adj_list[index] = NULL;
    }
}

void dfs_lexicographical(directed_acyclic_graph *graph, int vertex_index, char **result, int *count)
{
    graph->visited[vertex_index] = 1;
    node *current = graph->adj_list[vertex_index]->next;

    if (current == NULL)
    {
        result[(*count)++] = strdup(graph->adj_list[vertex_index]->item);
    }

    while (current != NULL)
    {
        int neighbor_index = -1;

        for (int i = 0; i < graph->vertices_amount; i++)
        {
            if (strcmp(graph->adj_list[i]->item, current->item) == 0)
            {
                neighbor_index = i;
                break;
            }
        }

        if (!graph->visited[neighbor_index])
        {
            dfs_lexicographical(graph, neighbor_index, result, count);
        }

        current = current->next;
    }
}

void depth_first_search(directed_acyclic_graph *graph)
{
    while (1)
    {
        char *result[MAX_VERTICES];
        int count = 0;

        int start_vertex_index = find_min_vertex_index(graph);

        if (start_vertex_index == -1)
        {
            break;
        }

        dfs_lexicographical(graph, start_vertex_index, result, &count);

        printf("Folhas em ordem lexicográfica: ");
        for (int i = 0; i < count; i++)
        {
            printf("%s ", result[i]);
            free(result[i]);
        }
        printf("\n");

        remove_vertex(graph, start_vertex_index);
    }
}

// Função para imprimir o grafo
void print_graph(directed_acyclic_graph *graph)
{
    printf("Graph:\n");
    for (int i = 0; i < graph->vertices_amount; i++)
    {
        node *current = graph->adj_list[i];
        printf("%s -> ", current->item);

        current = current->next;
        while (current != NULL)
        {
            printf("%s -> ", current->item);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// Função para liberar a memória alocada pelo grafo
void free_graph(directed_acyclic_graph *graph)
{
    for (int i = 0; i < graph->vertices_amount; i++)
    {
        node *current = graph->adj_list[i];
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
        directed_acyclic_graph *g = create_graph();

        for (int i = 0; i < n; i++)
        {
            char a[15], b[15];
            scanf("%s %s", a, b);
            add_edge(g, a, b);
        }

        print_graph(g);

        depth_first_search(g);

        // free_graph(g);
    }

    return 0;
}