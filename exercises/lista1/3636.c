#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
    char valor[100];
} ITEM;

typedef struct estrutura
{
    ITEM item;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO *cabeca;
} LISTA;

// Inicializa a lista deixando-a pronta para ser utilizada.
void inicializar(LISTA *l)
{
    l->cabeca = NULL;
}

// Cria um novo no com o item passado e tendo NULL como prox
NO *criarNo(ITEM item, NO *prox)
{
    NO *pNovo = (NO *)malloc(sizeof(NO));
    pNovo->item = item;
    pNovo->prox = prox;
    return pNovo;
}

// Retornar o tamanho da lista
int tamanho(LISTA *l)
{
    NO *p = l->cabeca;
    int tam = 0;
    while (p) // p != NULL
    {
        tam++;
        p = p->prox;
    }
    return tam;
}

// Retorna true se a lista esta vazia (Cabeca = NULL)
bool vazia(LISTA *l)
{
    return l->cabeca == NULL;
}

// Exibicao da lista sequencial
void exibirLista(LISTA *l)
{
    NO *p = l->cabeca;
    while (p) // p != NULL
    {
        printf("(%d,%s)", p->item.chave, p->item.valor);
        p = p->prox;
    }
}

// Liberacao das variaveis dinamicas dos nos da lista, iniciando da cabeca
void destruir(LISTA *l)
{
    NO *atual = l->cabeca;
    while (atual)
    {
        NO *prox = atual->prox; // guarda proxima posicao
        free(atual);            // libera memoria apontada por atual
        atual = prox;
    }
    l->cabeca = NULL; // ajusta inicio da lista (vazia)
}

void imprimirLista(LISTA *l)
{
    printf("Tamanho = %d\n", tamanho(l));
    exibirLista(l);
    printf("\n");
}

/////////////////////////////////////////////////////

/*
 Objetivo: Inserir em uma lista ordenada o item passado e garantir
           que nao havera duplicacao.
*/
bool inserirNaOrdem(ITEM item, LISTA *l)
{
    /*
        Implementar a função inserirNaOrdem que recebe dois parâmetros (item e l):
            item: Item que se deseja inserir na lista e cuja chave é utilizada para mantê-la ordenada.
            l: Lista na qual se deseja inserir o item.

        A função deve buscar a posição correta para inserção na lista encadeada para que a mesma permaneça sempre ordenada.
        Se a chave do item já existir na lista, retorna false e não o inclui na lista.
        Caso contrário, faz a inserção na lista na posição correta e retorna true.
    */

    NO *head = l->cabeca; // ponteiro para percorrer a lista
    NO *anterior = NULL;  // ponteiro para guardar o nó anterior

    // Percorremos a lista até encontrar a posição correta para inserir o item
    while (head && head->item.chave < item.chave)
    {
        anterior = head;
        head = head->prox;
    }

    // Se a chave já existir na lista, retornamos false
    if (head && head->item.chave == item.chave)
    {
        return false;
    }

    // Se a chave não existir, inserimos o item na lista
    NO *novo = criarNo(item, head);

    if (anterior)
    {
        // Se existe um nó anterior, inserimos o novo nó após ele
        anterior->prox = novo;
    }
    else
    {
        // Se não existe, inserimos o novo nó no início da lista
        l->cabeca = novo;
    }

    return true;
}
//////////////////////////////////////////////////////////////

void lerItens(LISTA *l)
{
    int n;
    scanf("%d", &n);

    // insere os valores n pares chave,valor
    ITEM item;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &item.chave);
        scanf("%s", item.valor);
        inserirNaOrdem(item, l);
    }
}

int main()
{
    LISTA l;
    ITEM item;

    inicializar(&l);

    lerItens(&l);
    imprimirLista(&l);

    lerItens(&l);
    imprimirLista(&l);

    destruir(&l);
    return 0;
}
