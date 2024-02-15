#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

/*
    O programa deverá manipular uma estrutura de dados em que:
        um único vetor é compartilhado por duas pilhas com o seguinte comportamento:

    (I) A primeira pilha terá o topo na posição anterior ao primeiro índice do vetor (último índice) e, antes da inserção de um novo item, será reposicionado para a posição sucessora, isto é, crescerá em direção ao fim do vetor.

    (II) A segunda pilha terá o topo na posição seguinte ao último índice do vetor (primeiro índice) e, antes da inserção de um novo item, será reposicionado para a posição antecessora, isto é, crescerá em direção ao início do vetor.

    [[Note que nesta estrutura o topo de uma pilha crescerá em direção ao topo da outra.]]]]

    Observação: ambas as pilhas poderão usar todas as posições livres do vetor, ou seja, o vetor será compartilhado entre as pilhas de modo que, em um caso extremo, uma das pilhas ocupe todo o vetor e a outra, consequentemente, não ocupe posição alguma.
*/

typedef struct pilha_dupla
{
    ITEM vet[TAM];
    int topo1, topo2;
} TPilhaDupla;

void create(TPilhaDupla *pd)
{
    // Como a main já inicializa a pilha, somente inicializamos os ponteiros de início e fim
    pd->topo1 = -1;
    pd->topo2 = TAM;
}

void destroy(TPilhaDupla *pd)
{
    // Como estamos trabalhando com arrays, não precisamos liberar memória
}

int isfull(TPilhaDupla *pd)
{
    // Como não temos um currentSize, precisamos verificar se a próxima posição do topo1 é igual ao topo2
    return (pd->topo1 + 1 == pd->topo2);
}

int isempty(TPilhaDupla *pd, int topo)
{
    // Se o topo for 1, verificamos se o topo1 é igual a -1
    // Se o topo for 2, verificamos se o topo2 é igual ao TAM
    if (topo == 1)
    {
        return (pd->topo1 == -1);
    }
    else
    {
        return (pd->topo2 == TAM);
    }
}

void push(TPilhaDupla *pd, ITEM x, int topo)
{
    /* if (isfull(pd))
    {
        printf("Overflow\n");
        return;
    } */

    // Se o topo for 1, incrementamos o topo1 e armazenamos o novo item (x) no topo1
    // Se o topo for 2, decrementamos o topo2 e armazenamos o novo item (x) no topo2
    if (topo == 1)
    {
        pd->topo1++;
        pd->vet[pd->topo1] = x;
    }
    else
    {
        pd->topo2--;
        pd->vet[pd->topo2] = x;
    }
}

ITEM pop(TPilhaDupla *pd, int topo)
{
    /* if (isempty(pd, topo))
    {
        printf("Underflow\n");
        return -1;
    } */

    // Se o topo for 1, retornamos o item do topo1 e decrementamos o topo1
    // Se o topo for 2, retornamos o item do topo2 e incrementamos o topo2
    if (topo == 1)
    {
        return pd->vet[pd->topo1--];
    }
    else
    {
        return pd->vet[pd->topo2++];
    }
}

ITEM top(TPilhaDupla *pd, int topo)
{
    // Se o topo for 1, retornamos o item do topo1, caso contrário, retornamos o item do topo2
    if (topo == 1)
    {
        return pd->vet[pd->topo1];
    }
    else
    {
        return pd->vet[pd->topo2];
    }
}

void preenche(TPilhaDupla *pd)
{
    ITEM x;
    int topo, qtd, i;

    scanf("%d%*c", &qtd);

    for (i = 0; i < qtd; i++)
    {
        scanf("%c %d%*c", &x, &topo);
        push(pd, x, topo);
    }
}

void exibe(TPilhaDupla *pd)
{
    int topo;

    while (scanf("%d", &topo) != EOF)
        printf("TOPO %d = %c\n", topo, pop(pd, topo));
}

int main(void)
{
    TPilhaDupla pd;

    create(&pd);
    preenche(&pd);
    exibe(&pd);
    destroy(&pd);

    return 0;
}
