#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

typedef struct _deque deque_t;
typedef struct _node node_t;

// Guarda um ponteiro pro node anterior, para o proximo node e o valor guardado
struct _node
{
    node_t *prev;
    node_t *next;
    int value;
};

// Guarda um ponteiro para o primeiro node, um ponteiro para o ultimo node, e o tamanho do deque
struct _deque
{
    node_t *front;
    node_t *rear;
    int size;
};

// Cria um node que guarda os valores que são enfileirados no deque
node_t *node_new(int value);

// Cria um deque dinamicamente e retorna seu endereço de memoria
deque_t *construct();
// Libera a memória do conteúdo e do próprio deque
void destruct(deque_t *deque);

// Retorna o tamanho do deque
int size(deque_t *deque);
// Retorna verdadeiro se o deque esta vazio, caso contrário, retorna falso
bool empty(deque_t *deque);

// Retorna o valor da frente da lista, retorna int_min quando a lista estiver vazia
int front(deque_t *deque);
// Retorna o valor do fim da lista, retorna int_min quando a lista estiver vazia
int rear(deque_t *deque);

// Cria um nó que guarda um valor e o adiciona ao fim do deque
void enqueue_rear(deque_t *deque, int value);
// Cria um nó que guarda um valor e o adiciona ao inicio do deque
void enqueue_front(deque_t *deque, int value);
// Retira o valor do final caso não esteja vazia
void dequeue_rear(deque_t *deque);
// Retira o valor da frente caso não esteja vazia
void dequeue_front(deque_t *deque);
// Limpa o conteudo do deque(deixa ele vazio)
void erase(deque_t *deque);

// Imprime o deque em uma unica linha, com os elementos separados por um espaço,
// terminando com um \n, lembrando de respeitar os conceitos de fila.
void print(deque_t *deque);

/*
    Implemente os algoritmos de listas com contratos presentes no código utilizando a implementação dinâmica.

    Formato de entrada
        Os algoritmos expressos serão todos testados com a seguinte entrada:
            1. Primeiro, lê-se um inteiro N > 0, equivalente a quantos elementos serão inseridos no deque.
            2. Em seguida são lidos os N inteiros.
            3. E por fim, será lido um inteiro M, referente a M inteiros que serão inseridos; note que não serão lidos estes M inteiros.

    Formato de saída
        Valores dos extremos da lista e o Estado da Lista após cada modificador testado.

    Exemplo de Entrada:
        5
        4 5 6 7 8
        3

    Saída esperada:
        4
        8
        The size of the deque 5
        2 1 0 4 5 6 7 8
        1 0 4 5 6 7 8
        1 0 4 5 6 7
        0 1 2
*/

int main()
{
    int i, num;
    scanf("%d", &num);

    deque_t *deque = construct();

    int vector[num];
    for (i = 0; i < num; ++i)
        scanf("%d", &vector[i]);

    for (i = 0; i < num; ++i)
        enqueue_rear(deque, vector[i]);

    printf("%d\n", front(deque));
    printf("%d\n", rear(deque));

    if (!empty(deque))
        printf("The size of the deque %d\n", size(deque));
    else
        printf("The deque is empty\n");

    scanf("%d", &num);
    for (i = 0; i < num; ++i)
        enqueue_front(deque, i);
    print(deque);
    dequeue_front(deque);
    print(deque);
    dequeue_rear(deque);
    print(deque);

    erase(deque);
    for (i = 0; i < 3; ++i)
        enqueue_rear(deque, i);

    print(deque);
    destruct(deque);

    return 0;
}

// Basicamente, alocamos o espaço para o nó e setamos os valores iniciais
node_t *node_new(int value)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->value = value;
    node->prev = NULL;
    node->next = NULL;
    return node;
}

// Aqui, alocamos o espaço para o deque e setamos os valores iniciais (assim como com o nó)
deque_t *construct()
{
    deque_t *deque = (deque_t *)malloc(sizeof(deque_t));
    deque->front = NULL;
    deque->rear = NULL;
    deque->size = 0;
    return deque;
}

// Liberamos a memória do conteúdo e do próprio deque
void destruct(deque_t *deque)
{
    erase(deque);
    free(deque);
}

// Retorna o tamanho do deque
int size(deque_t *deque)
{
    return deque->size;
}

// Verifica se o deque está vazio
bool empty(deque_t *deque)
{
    return deque->size == 0;
}

int front(deque_t *deque)
{
    // Se o deque estiver vazio, retornamos o menor inteiro possível
    if (empty(deque))
    {
        return INT_MIN;
    }

    // Caso contrário, retornamos o valor da frente
    return deque->front->value;
}

int rear(deque_t *deque)
{
    // Se o deque estiver vazio, retornamos o menor inteiro possível
    if (empty(deque))
    {
        return INT_MIN;
    }

    // Caso contrário, retornamos o valor do fim
    return deque->rear->value;
}

void enqueue_rear(deque_t *deque, int value)
{
    // Criamos um novo nó com o valor passado como parâmetro
    node_t *node = node_new(value);
    if (empty(deque))
    {
        // Se o deque estiver vazio, setamos o nó como o primeiro e o último da lista
        deque->front = node;
        deque->rear = node;
    }
    else
    {
        // Caso contrário, para adicionar um nó ao FINAL da lista, fazemos o seguinte:

        deque->rear->next = node; // Setamos o próximo elemento do último nó como o nó criado
        node->prev = deque->rear; // Setamos o elemento anterior do nó criado como o último nó (antes da adição) da lista
        deque->rear = node;       // Setamos o nó criado como o último do deque (rear)
    }

    // E por fim incrementamos o tamanho do deque
    deque->size++;
}

void enqueue_front(deque_t *deque, int value)
{
    // Aqui, a lógica é a mesma do enqueue_rear, mas para adicionar um nó ao início da lista
    node_t *node = node_new(value);
    if (empty(deque))
    {
        deque->front = node;
        deque->rear = node;
    }
    else
    {
        // Para adicionar um nó ao INÍCIO da lista, fazemos o seguinte:

        deque->front->prev = node; // Setamos o nó criado como o anterior do primeiro nó
        node->next = deque->front; // Setamos o próximo elemento do nó criado como o primeiro nó (antes da adição) da lista
        deque->front = node;       // Setamos o nó criado como o primeiro nó do deque (front)
    }
    deque->size++;
}

void dequeue_rear(deque_t *deque)
{
    if (empty(deque))
    {
        return;
    }

    // Para retirar um nó do FINAL da lista, fazemos o seguinte:

    node_t *node = deque->rear; // Guardamos o último nó
    deque->rear = node->prev;   // Setamos o penúltimo nó como o último

    if (deque->rear != NULL) // Se o último elemento do deque existir
    {
        deque->rear->next = NULL; // Setamos o próximo elemento desse último nó como NULL
    }

    free(node);
    deque->size--; // E por fim decrementamos o tamanho do deque
}

void dequeue_front(deque_t *deque)
{
    if (empty(deque))
    {
        return;
    }

    // Para retirar um nó do INÍCIO da lista, fazemos o seguinte:

    node_t *node = deque->front; // Guardamos o primeiro nó
    deque->front = node->next;   // Setamos o primeiro nó da lista como o próximo nó do primeiro nó (que armazenamos, antes da retirada)

    if (deque->front != NULL) // Se o primeiro elemento do deque existir
    {
        deque->front->prev = NULL; // Setamos o elemento anterior desse primeiro nó como NULL
    }

    free(node);
    deque->size--; // E por fim decrementamos o tamanho do deque
}

void erase(deque_t *deque)
{
    while (!empty(deque))
    {
        // Aqui, basicamente vamos retirando o primeiro nó do deque até que ele esteja vazio
        dequeue_front(deque);
    }
}

void print(deque_t *deque)
{
    // E aqui, percorremos o deque e imprimimos os valores dos nós
    node_t *node = deque->front;
    while (node != NULL)
    {
        printf("%d", node->value);
        if (node->next != NULL) // Somente imprimimos um espaço se o próximo nó existir
        {
            printf(" ");
        }
        node = node->next;
    }
    printf("\n");
}