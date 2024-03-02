# Grafos

## Introdução

Grafos são estruturas de dados que representam relações entre objetos. Eles são formados por um conjunto de **vértices** (ou nós) e um conjunto de **arestas** (ou arcos) que conectam esses vértices. As arestas podem ser **direcionadas** (ou seja, ter uma direção) ou **não direcionadas**.  
Os grafos são usados para modelar uma variedade de problemas do mundo real, como redes de computadores, redes de transporte, redes sociais, etc.

## Representação

Grafos podem ser representados de várias maneiras. As duas formas mais comuns de representação são a `matriz de adjacência` e a `lista de adjacência`.

Tendo como base o grafo abaixo, veja como funciona a implementação dessas duas formas a seguir:

```
    0---1
    |   |
    3---2
```

### Matriz de adjacência

A matriz de adjacência é uma matriz bidimensional que representa as conexões entre os vértices.

> Se o grafo for direcionado, a matriz será simétrica. Se o grafo for não direcionado, a matriz será assimétrica.

O valor de cada célula da matriz indica se há uma aresta entre os vértices correspondentes.  
Por exemplo, se a célula `(i, j)` tiver o valor **1**, isso significa que há uma aresta entre os vértices `i` e `j`. Se a célula `(i, j)` tiver o valor **0**, isso significa que não há uma aresta entre os vértices `i` e `j`.

```
    0  1  2  3
0   0  1  0  1
1   1  0  1  0
2   0  1  0  1
3   1  0  1  0
```

### Lista de adjacência

A lista de adjacência é uma lista de listas que representa as conexões entre os vértices. Cada vértice tem uma lista de seus vizinhos.

> Se o grafo for **direcionado**, a lista de adjacência terá uma lista para os vizinhos de saída e uma lista para os vizinhos de entrada.  
> Se o grafo for **não direcionado**, a lista de adjacência terá apenas uma lista para os vizinhos.

Por exemplo, para o grafo acima, a lista de adjacência seria:

```
0: 1, 3
1: 0, 2
2: 1, 3
3: 0, 2
```

## Algoritmos

Existem vários algoritmos que podem ser aplicados a grafos. Alguns dos mais comuns são:

- **Busca em largura (BFS):** um algoritmo que visita todos os vértices de um grafo em largura, ou seja, visita todos os vizinhos de um vértice antes de visitar os vizinhos dos vizinhos.

- **Busca em profundidade (DFS):** um algoritmo que visita todos os vértices de um grafo em profundidade, ou seja, visita um vértice e, em seguida, visita um de seus vizinhos, e assim por diante, até que não haja mais vizinhos a visitar.

- **Algoritmo de Dijkstra:** um algoritmo que encontra o caminho mais curto entre dois vértices em um grafo ponderado.

- **Algoritmo de Kruskal:** um algoritmo que encontra a árvore geradora mínima de um grafo ponderado.

- **Algoritmo de Prim:** um algoritmo que encontra a árvore geradora mínima de um grafo ponderado.

- **Algoritmo de Bellman-Ford:** um algoritmo que encontra o caminho mais curto entre dois vértices em um grafo ponderado, mesmo que haja arestas com peso negativo.

- **Algoritmo de Floyd-Warshall:** um algoritmo que encontra todos os caminhos mais curtos entre todos os pares de vértices em um grafo ponderado.

- **Algoritmo de Kosaraju:** um algoritmo que encontra os componentes fortemente conectados em um grafo direcionado.

- **Algoritmo de Tarjan:** um algoritmo que encontra os componentes fortemente conectados em um grafo direcionado.

- **Algoritmo de A\*:** um algoritmo que encontra o caminho mais curto entre dois vértices em um grafo ponderado, usando uma heurística para acelerar a busca.

## Implementação

A implementação de grafos pode ser feita de várias maneiras. Dentre elas, as mais comuns são:

- **Lista de adjacência:** uma lista de listas que representa as conexões entre os vértices.
- **Matriz de adjacência:** uma matriz bidimensional que representa as conexões entre os vértices.

#### Utilizando lista de adjacência

Aqui está um exemplo de implementação de um grafo usando a lista de adjacência em C:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int vertex;
    struct node *next;
} node;

typedef struct graph
{
    int num_vertices;
    node **adjacency_lists;
} graph;

node *create_node(int v)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->vertex = v;
    new_node->next = NULL;
    return new_node;
}

graph *create_graph(int vertices)
{
    graph *graph = (graph *)malloc(sizeof(graph));
    graph->num_vertices = vertices;

    graph->adjacency_lists = (node **)malloc(vertices * sizeof(node *));

    int i;
    for (i = 0; i < vertices; i++)
    {
        graph->adjacency_lists[i] = NULL;
    }

    return graph;
}

void add_edge(graph *graph, int src, int dest)
{
    node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

void print_graph(graph *graph)
{
    int v;
    for (v = 0; v < graph->num_vertices; v++)
    {
        node *temp = graph->adjacency_lists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
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

    return 0;
}
```

Neste exemplo, a estrutura de dados de lista de adjacência é usada para representar o grafo.

- A função `create_graph` cria um grafo com um número específico de vértices.
- A função `add_edge` adiciona uma aresta entre dois vértices.
- A função `print_graph` imprime a lista de adjacência do grafo.

#### Utilizando matriz de adjacência

Aqui está um exemplo de implementação de um grafo usando a matriz de adjacência em C:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct graph
{
    int num_vertices;
    int **adjacency_matrix;
} graph;

graph *create_graph(int vertices)
{
    graph *graph = (graph *)malloc(sizeof(graph));
    graph->num_vertices = vertices;

    graph->adjacency_matrix = (int **)malloc(vertices * sizeof(int *));
    int i, j;
    for (i = 0; i < vertices; i++)
    {
        graph->adjacency_matrix[i] = (int *)malloc(vertices * sizeof(int));
        for (j = 0; j < vertices; j++)
        {
            graph->adjacency_matrix[i][j] = 0;
        }
    }

    return graph;
}

void add_edge(graph *graph, int src, int dest)
{
    graph->adjacency_matrix[src][dest] = 1;
    graph->adjacency_matrix[dest][src] = 1;
}

void print_graph(graph *graph)
{
    int i, j;
    for (i = 0; i < graph->num_vertices; i++)
    {
        for (j = 0; j < graph->num_vertices; j++)
        {
            printf("%d ", graph->adjacency_matrix[i][j]);
        }
        printf("\n");
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

    return 0;
}
```

Ao utilizar essas estruturas, é possível implementar vários algoritmos de grafos, como busca em largura, busca em profundidade, algoritmo de Dijkstra, algoritmo de Kruskal, algoritmo de Prim, etc.

## Referências

- [Grafos - Wikipedia](<https://en.wikipedia.org/wiki/Graph_(abstract_data_type)>)
