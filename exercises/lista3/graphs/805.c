#include <stdio.h>
#include <stdlib.h>

/*
-> Descrição
    O algoritmo de busca em largura é bastante utilizado em estruturas de dados, e costuma ser útil para descobrir o menor caminho entre dois pontos. O algoritmo é iniciado a partir de um vértice arbitrário de um grafo e explora primeiro os seus vizinhos (vértices adjacentes) para então seguir para os vizinhos dos vizinhos.

    Para cada iteração do algoritmo, a partir do vértice inicial, marcamos em cada vértice visitado:

    1. a distância a partir da origem em número de arestas percorridas;
    2. o vértice predecessor, o que permite realizarmos o backtracking a partir de um nó de destino, até a origem, assumindo que a busca foi realizada e há um caminho entre os dois vértices.

    Neste exercício você receberá um grafo como entrada e alguns casos de teste consistindo de um nó de origem e de destino, para informar se há um caminho entre os dois nós e qual seria este caminho.
*/

/*
-> Formato de entrada
    A primeira linha da entrada consiste dos valores "V A T", onde:
        V é a quantidade de vértices do grafo,
        A corresponde à quantidade de arestas presentes no grafo, e
        T é a quantidade de casos de teste a serem examinados.

    Após a primeira linha, existem A linhas detalhando todas as arestas do grafo no formato "O D", onde O é o vértice de origem da aresta e D o vértice de destino. Perceba que embora sejam V vértices, as chaves de cada vértice vão de 0 a V - 1.

    Após as linhas das arestas, existem T linhas detalhando os casos de teste também no formato "OD", onde O é o vértice de origem da busca em largura e D o vértice de destino, onde testaremos se há um caminho de O a D.

    Não é obrigatório utilizar uma representação específica de grafo, **porém vértices adjacentes são sempre visitados em ordem crescente**.
    Ou seja, se um dado vértice 10 tem como vértices adjacentes 15, 9, e 12, a ordem de visitação será 9, 12, e 15.
*/

/*
-> Formato de saída
    Para cada caso de teste, deve ser impressa inicialmente a linha "Caso de Teste #n - BFS(o)", onde n é o valor do n-ésimo caso de teste (iniciado em 1 originalmente) e o corresponde ao vértice de origem.

    Para cada passo da busca em largura, deve ser impressa, em uma linha distinta, a mensagem "Iniciando busca em largura a partir de v", onde v é o vértice em questão sendo examinado.

    Ao final da execução da busca, deve ser impresso, para cada vértice do grafo, uma linha no seguinte formato:
        "K | D | P", onde
        K é a chave do nó do grafo (que vai de 0 a V-1, como detalhado na entrada),
        D é a distância do nó em relação ao vértice de origem para o caso de teste (se não for alcançável, deve ser impresso "-"), e
        P é o vértice predecessor do nó (se não aplicável, também imprimir "-").

    Finalmente, deve ser impressa em uma linha uma mensagem informando se há caminho entre O e D, onde O é o vértice de origem da busca em largura e D o vértice de destino, para o caso de teste em questão.
    Para o valor desta mensagem há duas possibilidades:
        1. Se não há caminho entre O e D, imprima "Sem caminho entre O e D"
        2. Se existe caminho entre O e D, imprima "Caminho entre O e D: O => V1 => V2 => ... => Vn => D", onde será detalhado o menor caminho existente entre O e D, identificado pela busca em largura.

    Observe a quantidade de quebras de linhas entre as informações impressas e os delimitadores entre os casos de teste, para gerar a saída no formato esperado pelo Huxley.
*/

// Estrutura de um nó do grafo
typedef struct node
{
    int key;
    int distance;
    int predecessor;
    struct node *next;
} node;

// Estrutura de um grafo
typedef struct graph
{
    int vertices_amount;
    node **adj_list;
} graph;

// Função para inicializar um grafo
graph *init_graph(int vertices_amount)
{
    graph *g = (graph *)malloc(sizeof(graph));

    g->vertices_amount = vertices_amount;
    g->adj_list = (node **)malloc(vertices_amount * sizeof(node *));

    for (int i = 0; i < vertices_amount; i++)
    {
        g->adj_list[i] = NULL;
    }

    return g;
}

// Função para adicionar uma aresta ao grafo, mantendo a ordem crescente dos vértices adjacentes
void add_edge(graph *g, int src, int dest)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->key = dest;
    new_node->next = NULL;

    // Se a lista de adjacência (adj_list) do vértice de origem (src) está vazia,
    // simplesmente atribuímos o novo nó como o primeiro nó da lista
    if (g->adj_list[src] == NULL)
    {
        g->adj_list[src] = new_node;
    }
    // Se a chave do vértice de destino (dest) é menor que a chave do primeiro vértice adjacente,
    // inserimos o novo nó no início da lista de adjacência (adj_list) do vértice de origem (src)
    else if (dest < g->adj_list[src]->key)
    {
        new_node->next = g->adj_list[src];
        g->adj_list[src] = new_node;
    }
    else
    {
        // Caso contrário, percorremos a lista até encontrar o nó cuja chave é maior que a chave do vértice de destino (dest).
        node *current = g->adj_list[src];
        while (current->next != NULL && dest > current->next->key)
        {
            current = current->next;
        }

        // Inserimos o novo nó na posição correta para manter a ordem crescente
        new_node->next = current->next;
        current->next = new_node;
    }

    // Precisamos fazer isso pois desejamos manter a lista de adjacência do vértice de origem ordenada
    // Isso é necessário para que a busca em largura seja realizada na ordem correta
}

// Função para imprimir o menor caminho entre dois vértices
void print_path(int *predecessors, int src, int dest)
{
    // Se o vértice de origem é o mesmo que o vértice de destino, imprimimos o vértice de origem
    if (src == dest)
    {
        printf("%d", src);
    }
    else
    {
        // Caso contrário, imprimimos o menor caminho entre o vértice de origem e o vértice de destino
        // Fazemos isso de forma recursiva, imprimindo o menor caminho entre o vértice de origem e o vértice predecessor do vértice de destino
        // Fazendo isso, estamos percorrendo o caminho do vértice de destino ao vértice de origem ao contrário.
        // Após a chamada recursiva, a função imprime o vértice de destino, o que resulta na impressão do caminho do vértice de origem ao vértice de destino na ordem correta
        print_path(predecessors, src, predecessors[dest]);
        printf(" => %d", dest);
    }
}

// Função para realizar a busca em largura
void bfs(graph *g, int src, int dest, int test_case)
{
    int *visited = (int *)malloc(g->vertices_amount * sizeof(int));
    int *distances = (int *)malloc(g->vertices_amount * sizeof(int));
    int *predecessors = (int *)malloc(g->vertices_amount * sizeof(int));

    for (int i = 0; i < g->vertices_amount; i++)
    {
        visited[i] = 0;
        distances[i] = -1;
        predecessors[i] = -1;
    }

    visited[src] = 1;
    distances[src] = 0;

    // Inicializamos uma lista com o vértice de origem (essa é a fila de vértices a serem visitados)
    // (não é necessário criar uma fila de fato, pois podemos simular uma fila utilizando uma lista encadeada, onde o primeiro elemento é o primeiro a ser visitado e novas adições são feitas no fim, a fim de simplificar o código e evitar a necessidade de implementar uma fila do zero :))
    node *queue = (node *)malloc(sizeof(node));
    queue->key = src;
    queue->next = NULL;

    printf("\nCaso de Teste #%d - BFS(%d)", test_case, src);
    printf("\n\n");

    // Enquanto a fila não estiver vazia
    while (queue != NULL)
    {
        // Retiramos o primeiro elemento da fila
        int current = queue->key;
        node *temp = queue;
        queue = queue->next;
        free(temp);

        printf("Iniciando busca em largura a partir de %d\n", current);

        // Percorremos todos os vértices adjacentes ao vértice atual em ordem crescente
        for (node *adj = g->adj_list[current]; adj != NULL; adj = adj->next)
        {
            int neighbor = adj->key;
            // printf("Visitando %d\n", neighbor);

            // Se o vértice adjacente ainda não foi visitado
            if (!visited[neighbor])
            {
                visited[neighbor] = 1;                        // Marcamos ele como visitado
                distances[neighbor] = distances[current] + 1; // Atualizamos a sua distância
                predecessors[neighbor] = current;             // E marcamos o vértice atual como seu predecessor

                // Adiciona o vértice adjacente à fila
                node *new_node = (node *)malloc(sizeof(node));
                new_node->key = neighbor;
                new_node->next = NULL;

                // Se a fila estiver vazia, o novo nó será o primeiro
                if (queue == NULL)
                {
                    queue = new_node;
                }
                else
                {
                    // Senão, adicionamos o novo nó no final da fila, para manter a ordem de visitação
                    node *last = queue;
                    while (last->next != NULL)
                    {
                        last = last->next;
                    }
                    last->next = new_node;
                }
            }
        }
    }

    printf("\n");

    for (int i = 0; i < g->vertices_amount; i++)
    {
        char distance = distances[i] == -1 ? '-' : distances[i] + '0';
        char predecessor = predecessors[i] == -1 ? '-' : predecessors[i] + '0';
        printf("%d | %c | %c\n", i, distance, predecessor);
    }

    printf("\n");

    if (predecessors[dest] == -1)
    {
        // Se não há caminho entre o vértice de origem e o vértice de destino, imprimimos uma mensagem informando isso
        printf("Sem caminho entre %d e %d", src, dest);
    }
    else
    {
        // Se há caminho entre o vértice de origem e o vértice de destino, podemos imprimimos o menor caminho
        // obs: o printf abaixo tem que ser feito fora da chamada de print_path, pois é uma função recursiva
        printf("Caminho entre %d e %d: ", src, dest);
        print_path(predecessors, src, dest);
    }

    printf("\n\n");
    printf("--------\n");
}

int main()
{
    int vertices_amount, edges_amount, test_cases;
    scanf("%d %d %d", &vertices_amount, &edges_amount, &test_cases);

    graph *g = init_graph(vertices_amount);

    // Adição das arestas ao grafo
    for (int i = 0; i < edges_amount; i++)
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        add_edge(g, src, dest);
    }

    printf("\n--------\n");

    // Realização da busca em largura para cada caso de teste
    for (int i = 0; i < test_cases; i++)
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        bfs(g, src, dest, i + 1);
    }

    return 0;
}