#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 100

typedef struct pilha
{
    ITEM vet[TAM];
    int topo;
} TPilha;

void create(TPilha *p)
{
    p->topo = -1;
}

void destroy(TPilha *p)
{
    p->topo = -1;
}

int isfull(TPilha *p)
{
    return p->topo == TAM;
}

int isempty(TPilha *p)
{
    return p->topo == -1;
}

void push(TPilha *p, ITEM x)
{
    if (isfull(p))
    {
        puts("overflow");
        abort();
    }
    p->topo++;
    p->vet[p->topo] = x;
}

ITEM pop(TPilha *p)
{
    if (isempty(p))
    {
        puts("underflow");
        abort();
    }
    ITEM x = p->vet[p->topo];
    p->topo--;
    return x;
}

ITEM top(TPilha *p)
{
    if (isempty(p))
    {
        puts("underflow");
        abort();
    }
    return p->vet[p->topo];
}

/*
    Complete a função indicada para que o programa exiba: a) a frase inserida pelo usuário e; b) a frase inserida pelo usuário com os caracteres de cada palavra em sequência invertida.

    Observação: note que apenas os caracteres das palavras devem ser exibidos em sequência invertida, porém a frase continuará com a mesma sequência de palavras.
*/

void inverte_palavras_frase(char frase[])
{
    TPilha pilha;
    create(&pilha);

    int i = 0;

    // Invertemos as palavras da frase e sobrescrevemos a frase original
    while (frase[i] != '\0')
    {
        if (frase[i] == ' ')
        {
            while (!isempty(&pilha))
            {
                frase[i - pilha.topo - 1] = pop(&pilha);
            }
        }
        else
        {
            push(&pilha, frase[i]);
        }
        i++;
    }

    // Descobri que, se preferir fazer com um for, dá pra fazer assim também:
    /* for (int i = 0; frase[i] != '\0'; i++)
    {
        if (frase[i] == ' ')
        {
            while (!isempty(&pilha))
            {
                frase[i - pilha.topo - 1] = pop(&pilha);
            }
            printf(" ");
        }
        else
        {
            push(&pilha, frase[i]);
        }
    } */

    // Precisamos lidar com o caso da última palavra não ser seguida por um espaço
    // Para isso, repetimos o processo de inverter as letras para a última palavra
    while (!isempty(&pilha))
    {
        frase[strlen(frase) - pilha.topo - 1] = pop(&pilha);
    }
}

int main(void)
{
    char frase[TAM];

    gets(frase);
    printf("original = %s\n", frase);
    inverte_palavras_frase(frase);
    printf("invertida = %s\n", frase);

    return 0;
}
