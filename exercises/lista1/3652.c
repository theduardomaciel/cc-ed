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
    struct estrutura *ant;
    struct estrutura *prox;
} NO;

typedef struct
{
    NO *cabeca;
    NO *cauda;
    int tamanho;
} LISTA;

// Inicializa a lista deixando-a pronta para ser utilizada.
void inicializar(LISTA *l)
{
    l->cabeca = NULL;
    l->cauda = NULL;
    l->tamanho = 0;
}

// Cria um novo no com o item, os apontadores para o anterior e para o proximo
NO *criarNo(ITEM item, NO *ant, NO *prox)
{
    NO *pNovo = (NO *)malloc(sizeof(NO));
    pNovo->item = item;
    pNovo->ant = ant;
    pNovo->prox = prox;
    return pNovo;
}

// Retornar o tamanho da lista
int tamanho(LISTA *l)
{
    return l->tamanho;
}

// Retorna true se a lista esta vazia, ou seja, se tem tamanho = 0
bool vazia(LISTA *l)
{
    return tamanho(l) == 0;
}

/*
  Objetivo: Insere o item passado como parâmetro na lista passada.
            A inserção ocorre no inicio da lista, ou seja, na cabeça.
            Não verifica se o item existe na lista, ou seja, permite
            duplicação.
*/
bool inserir(ITEM item, LISTA *l)
{
    NO *pNovo = criarNo(item, NULL, l->cabeca);
    l->tamanho++;

    if (l->cabeca)              // cabeca != NULL
        l->cabeca->ant = pNovo; // ajusta o apontador para o anterior na antiga cabeca

    l->cabeca = pNovo;

    if (l->cauda == NULL) // se nao tinha cauda, o novo Nó estará também na cauda
        l->cauda = pNovo;

    return true;
}

// Exibição da lista
void exibirListaCabecaCauda(LISTA *l)
{
    NO *p = l->cabeca;
    while (p)
    {
        printf("(%d,%s)", p->item.chave, p->item.valor);
        p = p->prox;
    }
}

// Exibição da lista começando da cauda
void exibirListaCaudaCabeca(LISTA *l)
{
    NO *p = l->cauda;
    while (p)
    {
        printf("(%d,%s)", p->item.chave, p->item.valor);
        p = p->ant;
    }
}

void imprimirLista(LISTA *l, bool crescente)
{
    printf("Tamanho = %d\n", tamanho(l));
    if (crescente)
        exibirListaCabecaCauda(l);
    else
        exibirListaCaudaCabeca(l);
    printf("\n");
}

// LIberação das variáveis dinâmicas dos nos da lista, iniciando da cabeca
void destruir(LISTA *l)
{
    NO *atual = l->cabeca;
    while (atual)
    {
        NO *prox = atual->prox; // guarda proxima posicao
        free(atual);            // libera memoria apontada por atual
        atual = prox;
    }
    l->cabeca = NULL; // ajusta a cabeca da lista (vazia)
    l->cauda = NULL;  // ajusta a cauda da lista (vazia)
}

/////////////////////////////////////////////////////

/*
 Objetivo: Inverte a lista encadeada ajustando apenas os apontadores,
           ou seja, evitando copiar os dados para uma nova lista.
*/
void inverter(LISTA *l)
{
    /*
        Implementar a função inverter que recebe uma lista l como parâmetro e tem como objetivo inverter a ordem dos itens da lista, ou seja, o primeiro valor passará a ser o último, o segundo o penúltimo e assim por diante.

        Para implementar a função, não deve ser criado nenhuma lista auxiliar, vetores ou variáveis dinâmicas.
        Também não pode ser utilizada a função inserir, já que a mesma cria uma variável dinâmica.
        Na solução são permitidas apenas variáveis do tipo apontador para fazer a inversão da lista original.
    */

    NO *temp = NULL;
    NO *current = l->cabeca;

    // Troca os ponteiros "prox" e "ant" de todos os nós da lista
    while (current != NULL)
    {
        // Armazenamos o nó anterior numa variável temporária
        temp = current->ant;

        // Trocamos os ponteiros "prox" e "ant"
        current->ant = current->prox;
        current->prox = temp;

        // Avançamos para o próximo nó
        current = current->ant;
    }

    // Atualiza a cauda
    l->cauda = l->cabeca;

    // Antes de atualizar a cabeça, precisamos checar os casos de uma lista vazia ou com apenas um nó
    if (temp != NULL)
    {
        l->cabeca = temp->ant;
    }
}

/////////////////////////////////////////////////////

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
        inserir(item, l);
    }
}

//////////////////////////////////////////////////////////////

int main()
{
    LISTA l;
    ITEM item;

    inicializar(&l);

    lerItens(&l);
    imprimirLista(&l, true); // cabeca => cauda

    inverter(&l);
    imprimirLista(&l, true);  // cabeca => cauda
    imprimirLista(&l, false); // cauda => cabeca

    destruir(&l);
    return 0;
}