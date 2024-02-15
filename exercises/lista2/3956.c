#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

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
    Descrição:
        Complete a função indicada para que o programa exiba corretamente uma indicação de que a palavra dada é ou não é palíndromo.

        Observação: uma palavra palíndromo é aquela em que a leitura da esquerda para direita é idêntica à leitura da direita para esquerda.

    Formato de Entrada:
        Uma única palavra com letras minúsculas do alfabeto latino e não acentuadas. A palavra poderá conter até 50 caracteres e sem espaços.

    Formato de Saída:
        A palavra 'sim' (em minúsculo e sem apóstrofos) caso a palavra dada na entrada seja palíndromo ou 'nao' (em minúsculo, sem apóstrofos e sem acentuação) caso a palavra dada na entrada não seja palíndromo.
*/

int palindromo(char s[])
{
    // Inicializamos uma pilha para armazenar os caracteres da palavra
    TPilha *pilha = (TPilha *)malloc(sizeof(TPilha));
    create(pilha);

    // Empilhamos os caracteres da palavra
    for (int i = 0; s[i] != '\0'; i++)
    {
        push(pilha, s[i]);
    }

    // Em seguida, desempilhamos os caracteres da palavra e os comparamos com a palavra original
    for (int i = 0; s[i] != '\0'; i++)
    {
        // Se algum caractere desempilhado for diferente do caractere original, a palavra não é palíndromo
        if (pop(pilha) != s[i])
        {
            return 0;
        }
    }

    // Obs: Dava pra utilizar a função strcmp para fazer uma comparação de strings, modificando um pouco o código para gerar uma nova string, como alternativa

    return 1;
}

int main(void)
{
    char palavra[TAM];

    scanf("%s", palavra);
    printf(palindromo(palavra) ? "sim" : "nao");

    return 0;
}
