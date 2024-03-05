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

// Estrutura de uma fila
typedef struct queue_node queue_node;
struct queue_node
{
    int item;
    queue_node *next;
};

typedef struct queue queue;
struct queue
{
    int current_size;
    queue_node *head;
    queue_node *tail;
};

queue *create_queue()
{
    queue *new_queue = (queue *)malloc(sizeof(queue));
    new_queue->current_size = 0;
    new_queue->head = NULL;
    new_queue->tail = NULL;
    return new_queue;
}

int is_queue_empty(queue *queue)
{
    return (queue->current_size == 0);
}

void enqueue(queue *queue, int item)
{
    queue_node *new_node = (queue_node *)malloc(sizeof(queue_node));
    new_node->item = item;
    new_node->next = NULL;

    if (queue->head == NULL)
    {
        queue->head = new_node;
    }
    else
    {
        queue->tail->next = new_node;
    }

    queue->tail = new_node;
    queue->current_size++;
}

int dequeue(queue *queue)
{
    if (is_queue_empty(queue))
    {
        printf("Queue underflow\n");
        return -1;
    }

    queue_node *node_to_dequeue = queue->head;
    int dequeued = node_to_dequeue->item;

    queue->head = queue->head->next;
    queue->current_size--;

    if (queue->head == NULL)
    {
        queue->tail = NULL;
    }

    free(node_to_dequeue);
    return dequeued;
}

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

    // Inicializamos uma lista com o vértice de origem
    // (essa é a fila de vértices a serem visitados)
    queue *queue = create_queue();
    enqueue(queue, src);

    printf("Caso de Teste #%d - BFS(%d)\n\n", test_case, src);

    // Enquanto a fila não estiver vazia
    while (!is_queue_empty(queue))
    {
        // Retiramos o primeiro elemento da fila
        int current = dequeue(queue);

        printf("Iniciando busca em largura a partir de %d\n", current);

        // Percorremos a lista de adjacência do vértice atual
        node *adj_list = g->adj_list[current];

        int *adjacent_vertices = (int *)malloc(g->vertices_amount * sizeof(int));
        int count = 0;
        while (adj_list)
        {
            adjacent_vertices[count++] = adj_list->key;
            adj_list = adj_list->next;
        }

        // Ordenamos os vértices adjacentes em ordem crescente
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                if (adjacent_vertices[i] > adjacent_vertices[j])
                {
                    int temp = adjacent_vertices[i];
                    adjacent_vertices[i] = adjacent_vertices[j];
                    adjacent_vertices[j] = temp;
                }
            }
        }

        // Para cada vértice adjacente
        for (int i = 0; i < count; i++)
        {
            int adjacent_vertex = adjacent_vertices[i];

            // Se o vértice adjacente ainda não foi visitado
            if (!visited[adjacent_vertex])
            {
                // Adicionamos o vértice adjacente à fila
                enqueue(queue, adjacent_vertex);

                visited[adjacent_vertex] = 1;
                distances[adjacent_vertex] = distances[current] + 1;
                predecessors[adjacent_vertex] = current;
            }
        }

        free(adjacent_vertices);
    }

    printf("\n");

    for (int i = 0; i < g->vertices_amount; ++i)
    {
        // Imprimimos a chave do vértice, a distância do vértice em relação ao vértice de origem, e o vértice predecessor
        printf("%d | ", i);

        // Se a distância do vértice é -1, imprimimos "-"
        if (distances[i] == -1)
        {
            printf("- | ");
        }
        else
        {
            printf("%d | ", distances[i]);
        }

        // Se o vértice predecessor é -1, imprimimos "-"
        if (predecessors[i] == -1)
        {
            printf("-\n");
        }
        else
        {
            printf("%d\n", predecessors[i]);
        }
    }

    printf("\n");

    if (distances[dest] == -1)
    {
        // Se não há caminho entre o vértice de origem e o vértice de destino, imprimimos uma mensagem informando isso
        printf("Sem caminho entre %d e %d\n", src, dest);
    }
    else
    {
        // Se há caminho entre o vértice de origem e o vértice de destino, podemos imprimimos o menor caminho
        // obs: o printf abaixo tem que ser feito fora da chamada de print_path, pois é uma função recursiva
        printf("Caminho entre %d e %d: ", src, dest);
        print_path(predecessors, src, dest);
        printf("\n");
    }

    printf("\n--------\n");
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

    printf("--------\n\n");

    // Realização da busca em largura para cada caso de teste
    for (int i = 0; i < test_cases; i++)
    {
        int src, dest;
        scanf("%d %d", &src, &dest);
        bfs(g, src, dest, i + 1);
        printf("\n");
    }

    return 0;
}