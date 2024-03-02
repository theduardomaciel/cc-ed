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

#define MAX_SIZE 100

typedef struct adj_list adj_list;
struct adj_list
{
    char item[15]; // ou vertex
    struct adj_list *next;
};

typedef struct graph graph;
struct graph
{
    adj_list *vertices[MAX_SIZE];
    short visited[MAX_SIZE];
};

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

// Função para criar um nó na lista de adjacência
adj_list *create_adj_list(char item[15]) // ou vertex
{
    adj_list *new_adj_list = (adj_list *)malloc(sizeof(adj_list));
    strcpy(new_adj_list->item, item);
    new_adj_list->next = NULL;
    return new_adj_list;
}

// Função para adicionar uma aresta entre dois vértices de um grafo direcionado acíclico
void add_edge(graph *graph, char vertex1[15], char vertex2[15])
{
    adj_list *new_edge = create_adj_list(vertex2);

    int i;
    for (i = 0; i < MAX_SIZE; i++)
    {
        // Procuramos pelo vértice1 no grafo, e se ele existir
        if (graph->vertices[i] != NULL && strcmp(graph->vertices[i]->item, vertex1) == 0)
        {
            // Adicionamos a aresta no início da lista de adjacência
            new_edge->next = graph->vertices[i]->next;
            graph->vertices[i]->next = new_edge;
            return;
        }
    }

    // Se o vértice1 não for encontrado, criamos um novo vértice e adicionamos a aresta
    for (i = 0; i < MAX_SIZE; i++)
    {
        if (graph->vertices[i] == NULL)
        {
            graph->vertices[i] = create_adj_list(vertex1);
            graph->vertices[i]->next = new_edge;
            return;
        }
    }
}

void print_graph(graph *graph)
{
    printf("Grafo:\n");

    int i;
    for (i = 0; i < MAX_SIZE; i++)
    {
        if (graph->vertices[i] != NULL)
        {
            printf("%s", graph->vertices[i]->item);
            adj_list *current = graph->vertices[i]->next;
            while (current != NULL)
            {
                printf(" -> %s", current->item);
                current = current->next;
            }
            printf("\n");
        }
    }
}

// Função para imprimir as folhas de um grafo em ordem lexicográfica, os remove e repete o procedimento até que não existam mais nós
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

int main()
{
    int n;

    while (scanf("%d", &n) != EOF)
    {
        graph *g = create_graph();

        for (int i = 0; i < n; i++)
        {
            char a[15], b[15];
            scanf("%s %s", a, b);
            add_edge(g, a, b);
        }

        print_graph(g);
        print_graph_leafs(g);
    }

    return 0;
}