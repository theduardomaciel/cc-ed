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
*/

#define MAX_STRING_LENGTH 15
#define MAX_VERTICES 100

// Definição da estrutura do nó da lista de adjacência
typedef struct adj_list
{
    char item[MAX_STRING_LENGTH + 1]; // +1 para o caractere nulo
    struct adj_list *next;
} adj_list;

// Definição da estrutura do grafo
typedef struct
{
    adj_list *vertices[MAX_VERTICES];
    short visited[MAX_VERTICES];
    int vertices_amount;
} directed_acyclic_graph;

// Função para inicializar o grafo
directed_acyclic_graph *create_graph()
{
    directed_acyclic_graph *new_graph = (directed_acyclic_graph *)malloc(sizeof(directed_acyclic_graph));

    new_graph->vertices_amount = 0;
    for (int i = 0; i < MAX_VERTICES; i++)
    {
        new_graph->vertices[i] = NULL;
        new_graph->visited[i] = 0;
    }

    return new_graph;
}

// Função para adicionar um vértice ao grafo
void add_vertex(directed_acyclic_graph *graph, const char *vertexData)
{
    if (graph->vertices_amount < MAX_VERTICES)
    {
        adj_list *vertex = (adj_list *)malloc(sizeof(adj_list));
        strncpy(vertex->item, vertexData, MAX_STRING_LENGTH);
        vertex->item[MAX_STRING_LENGTH] = '\0'; // Garante que a string termine corretamente
        vertex->next = NULL;

        graph->vertices[graph->vertices_amount++] = vertex;
    }
}

// Função para adicionar uma aresta direcionada entre dois vértices
void add_edge(directed_acyclic_graph *graph, const char *source_vertex, const char *destination_vertex)
{
    int source_index = -1, destination_index = -1;

    // Procura os índices dos vértices source e destination
    for (int i = 0; i < graph->vertices_amount; i++)
    {
        if (strcmp(graph->vertices[i]->item, source_vertex) == 0)
        {
            source_index = i;
        }
        if (strcmp(graph->vertices[i]->item, destination_vertex) == 0)
        {
            destination_index = i;
        }
    }

    // Se o vértice source não existir, adiciona-o ao grafo
    if (source_index == -1)
    {
        add_vertex(graph, source_vertex);
        source_index = graph->vertices_amount - 1;
    }

    // Se o vértice destination não existir, adiciona-o ao grafo
    if (destination_index == -1)
    {
        add_vertex(graph, destination_vertex);
        destination_index = graph->vertices_amount - 1;
    }

    // Adiciona a aresta direcionada
    adj_list *vertex = (adj_list *)malloc(sizeof(adj_list));

    strncpy(vertex->item, destination_vertex, MAX_STRING_LENGTH);

    vertex->item[MAX_STRING_LENGTH] = '\0';
    vertex->next = graph->vertices[source_index]->next;
    graph->vertices[source_index]->next = vertex;
}

// Função para imprimir o grafo
void print_graph(directed_acyclic_graph *graph)
{
    printf("\nGraph:\n");
    for (int i = 0; i < graph->vertices_amount; i++)
    {
        adj_list *current = graph->vertices[i];
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

int find_index(directed_acyclic_graph *graph)
{
    int next_index = -1;

    for (int i = 0; i < graph->vertices_amount; i++)
    {
        // printf("%s foi visitado? %d\n", graph->vertices[i]->item, graph->visited[i]);
        if (!graph->visited[i] && (next_index == -1 || strcmp(graph->vertices[i]->item, graph->vertices[next_index]->item) < 0))
        {
            next_index = i;
        }
    }

    // printf("-----------------\n");

    return next_index;
}

void dfs_lexicographical(directed_acyclic_graph *graph, int vertex_index, char **result, int *count)
{
    graph->visited[vertex_index] = 1;
    adj_list *current = graph->vertices[vertex_index]->next;

    if (current == NULL)
    {
        result[(*count)++] = strdup(graph->vertices[vertex_index]->item);
    }

    while (current != NULL)
    {
        int neighbor_index = -1;

        for (int i = 0; i < graph->vertices_amount; i++)
        {
            if (strcmp(graph->vertices[i]->item, current->item) == 0)
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

// Função para realizar o DFS nas folhas do grafo
// Após a execução, as folhas são removidas do grafo
void dfs_leaves(directed_acyclic_graph *graph)
{
    while (1)
    {

        char *result[MAX_VERTICES];
        int count = 0;

        int start_vertex_index = find_index(graph);

        if (start_vertex_index == -1)
        {
            break;
        }

        printf("Procurando a partir de: %s\n", graph->vertices[start_vertex_index]->item);

        dfs_lexicographical(graph, start_vertex_index, result, &count);

        printf("FOLHAS: ");
        for (int i = 0; i < count; i++)
        {
            printf("%s ", result[i]);
            free(result[i]);
        }
        printf("\n");

        graph->visited[start_vertex_index] = 1;
    }
}

void dfs(directed_acyclic_graph *graph, int vertex_index)
{
    graph->visited[vertex_index] = 1;
    printf("%s ", graph->vertices[vertex_index]->item);

    adj_list *current = graph->vertices[vertex_index]->next;
    while (current != NULL)
    {
        int neighbor_index = -1;

        for (int i = 0; i < graph->vertices_amount; i++)
        {
            if (strcmp(graph->vertices[i]->item, current->item) == 0)
            {
                neighbor_index = i;
                break;
            }
        }

        if (!graph->visited[neighbor_index])
        {
            dfs(graph, neighbor_index);
        }

        current = current->next;
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

        printf("\nDFS:\n");
        // dfs_leaves(g);
        dfs(g, 0);
    }

    return 0;
}

// Função para liberar a memória alocada pelo grafo
/* void free_graph(directed_acyclic_graph *graph)
{
    for (int i = 0; i < graph->vertices_amount; i++)
    {
        adj_list *current = graph->vertices[i];
        while (current != NULL)
        {
            adj_list *next = current->next;
            free(current);
            current = next;
        }
    }
} */