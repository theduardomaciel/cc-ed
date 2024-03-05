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

// Estrutura para representar um nó (vértice) no grafo
typedef struct node
{
    int node_number;     // Número do nó
    int insertion_index; // Índice de inserção do nó
    char item[MAX_STRING_LENGTH + 1];
    struct node *next;
} node;

// Estrutura para representar um grafo como a questão pede, sendo direcionado e acíclico
typedef struct directed_acyclic_graph
{
    int size;        // Número de nós no grafo
    node **adj_list; // Lista de adjacência para representar as arestas entre os nós do grafo
} directed_acyclic_graph;

// Responsável por criar um grafo direcionado acíclico
directed_acyclic_graph *create_graph()
{
    directed_acyclic_graph *g = (directed_acyclic_graph *)malloc(sizeof(directed_acyclic_graph));

    g->size = 100;
    g->adj_list = (node **)malloc(100 * sizeof(node *));

    for (int i = 0; i < 100; i++)
    {
        g->adj_list[i] = NULL;
    }

    return g;
}

// Função para adicionar um nó à lista em ordem lexicográfica
node *insert_node(node *head, const char item[MAX_STRING_LENGTH + 1], int index)
{
    // Inicializamos um novo nó
    node *new_node = (node *)malloc(sizeof(node));
    new_node->insertion_index = index;
    strcpy(new_node->item, item);
    new_node->next = NULL;

    // Se a lista estiver vazia, simplesmente retornamos o novo nó
    if (head == NULL)
    {
        return new_node;
    }

    node *current = head;
    node *prev = NULL;

    // Procuramos a posição correta para inserir o novo nó
    while (current != NULL && strcmp(current->item, item) < 0)
    {
        prev = current;
        current = current->next;
    }

    // Precisamos lidar com o caso do nó que queremos inserir ser o primeiro da lista
    if (prev == NULL)
    {
        // Se for, atualizamos a cabeça da lista
        new_node->next = current;
        head = new_node;
    }
    else
    {
        // Se não for, atualizamos o ponteiro do nó anterior para apontar para o novo nó
        prev->next = new_node;
        new_node->next = current;
    }

    return head;
}

// Para evitar código duplicado, criamos a assinatura do tipo de função de comparação
typedef int (*CompareFunction)(node *, int);

// Criamos uma função genérica de remoção
node *remove_node_generic(node *head, int item, CompareFunction compareFunction)
{
    if (head == NULL)
    {
        return head;
    }

    node *current = head;
    node *prev = NULL;

    // Procuramos o nó que queremos remover usando a função de comparação
    while (current != NULL && compareFunction(current, item))
    {
        prev = current;
        current = current->next;
    }

    // Se não encontramos o nó, retornamos a lista original
    if (current == NULL)
    {
        return head;
    }

    // Precisamos lidar com o caso do nó que queremos remover ser o primeiro da lista
    if (prev == NULL)
    {
        // Se for, atualizamos a cabeça da lista
        head = head->next;
    }
    else
    {
        // Se não for, atualizamos o ponteiro do nó anterior para pular o nó que queremos remover
        prev->next = current->next;
    }

    free(current);

    return head;
}

// Função de comparação para remover nó pelo número do nó
int compare_by_node_number(node *current, int item)
{
    return current->node_number != item;
}

// Função de comparação para remover nó pelo índice de inserção
int compare_by_insertion_index(node *current, int item)
{
    return current->insertion_index != item;
}

// Função para imprimir os itens da lista
void print_nodes(node *head)
{
    node *aux = head;
    while (aux != NULL)
    {
        printf("%s\n", aux->item);
        aux = aux->next;
    }
}

// Função para encontrar o índice de um nó pelo valor de seu item (char*) na lista
int get_item_index(node *head, const char item[])
{
    node *temp = head;

    while (temp != NULL && (strcmp(temp->item, item) != 0))
    {
        temp = temp->next;
    }

    return (temp != NULL) ? temp->insertion_index : -1;
}

// Função que realiza a busca em profundidade no grafo
void dfs(directed_acyclic_graph *g, node *src_nodes, int size)
{
    while (src_nodes != NULL)
    {
        node *aux_src = src_nodes;
        node *dest_nodes = NULL;

        // Processamos cada um dos nós que estão na lista de entrada
        while (aux_src != NULL)
        {
            int index = get_item_index(src_nodes, aux_src->item);

            if (g->adj_list[index] == NULL)
                dest_nodes = insert_node(dest_nodes, aux_src->item, index);

            aux_src = aux_src->next;
        }

        print_nodes(dest_nodes);

        aux_src = dest_nodes;

        // Removemos tanto as arestas quanto os nós de uma só vez
        while (aux_src != NULL)
        {
            for (int i = 0; i < size; i++)
            {
                // Removemos a aresta entre os nós
                g->adj_list[i] = remove_node_generic(g->adj_list[i], aux_src->insertion_index, compare_by_node_number);
            }
            // Removemos o nó da lista
            src_nodes = remove_node_generic(src_nodes, aux_src->insertion_index, compare_by_insertion_index);
            aux_src = aux_src->next;
        }
    }
}

// Função responsável por adicionar uma aresta entre dois nós
void add_edge(directed_acyclic_graph *g, int indexA, int indexB)
{
    node *new_node = (node *)malloc(sizeof(node));

    new_node->insertion_index = 0;
    new_node->node_number = indexB;
    new_node->next = g->adj_list[indexA];
    g->adj_list[indexA] = new_node;
}

int main()
{
    int n;

    while (scanf("%d", &n) != EOF)
    {
        directed_acyclic_graph *g = create_graph();

        char itemA[16], itemB[16];
        node *items = NULL;

        int size = 0;

        // Processamos cada uma das arestas
        for (int i = 0; i < n; i++)
        {
            scanf("%s %s", itemA, itemB);

            // Processamos cada um dos nós
            int indexA = get_item_index(items, itemA);
            if (indexA == -1)
            {
                items = insert_node(items, itemA, size);
                indexA = size;
                size++;
            }

            int indexB = get_item_index(items, itemB);
            if (indexB == -1)
            {
                items = insert_node(items, itemB, size);
                indexB = size;
                size++;
            }

            // E adicionamos a aresta entre os nós
            add_edge(g, indexA, indexB);
        }

        // Por fim, realizamos a busca em profundidade no grafo
        dfs(g, items, size);
    }

    return 0;
}
