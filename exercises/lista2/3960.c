#include <stdio.h>
#include <stdlib.h>
#define ITEM char
#define TAM 50

typedef struct deque
{
    ITEM vet[TAM];
    int front, rear;
} TDeque;

/*
    Considere a implementação do deque em um array e com um índice front (demarca a posição em que está o primeiro item do deque) e um índice rear (demarca a posição vazia onde entrará o próximo item do deque, caso seja colocado na extremidade do fim).

    Nesta implementação o front será sempre zero. Caso um item seja enfileirado no início do deque, cada item a partir do front deverá ser deslocado para a posição seguinte, assim liberando espaço para que o novo item seja colocado na primeira posição do array. De forma análoga, caso seja desenfileirado um item do início do deque, cada item que esteja na posição seguinte ao front deverá ser deslocado para a posição antecessora.

    Para enfileirar no final do deque, basta incluir o item na posição indicada por rear e incrementá-lo. De modo semelhante, para desenfileirar um item do final do deque, basta retirá-lo da posição que antecede o rear e decrementá-lo.
*/

void create(TDeque *d)
{
    // Como a main já inicializa o deque, somente inicializamos os ponteiros de início e fim
    d->front = 0;
    d->rear = 0;
}

void destroy(TDeque *d)
{
    // Como estamos trabalhando com arrays, não precisamos liberar memória
}

int isfull(TDeque *d)
{
    // Como não temos um currentSize, precisamos verificar se a próxima posição do fim é igual ao início
    return ((d->rear + 1) % TAM == d->front);
}

int isempty(TDeque *d)
{
    return (d->front == d->rear); // Caso a frente e o fim sejam iguais, o deque está vazio
}

void store(TDeque *d, int extremidade, ITEM x)
{
    // Seria bom lidar com o overflow também (num cenário real, no nosso caso, a questão não pede isso)
    /* if (isfull(d))
    {
        printf("Overflow\n");
    }
    */

    // Se a extremidade for 1, o elemento é inserido no início
    if (extremidade == 1)
    {
        // Decrementamos o início (front) tomando cuidado para não ultrapassar o tamanho do array (com o operador %)
        d->front = (d->front - 1 + TAM) % TAM;

        // E armazenamos o novo item (x) no início
        d->vet[d->front] = x;
    }
    else
    {
        // Se a extremidade for 2, o elemento é inserido no fim

        // Armazenamos o novo item (x) no fim
        d->vet[d->rear] = x;

        // E incrementamos o fim (rear) tomando cuidado para não ultrapassar o tamanho do array (com o operador %)
        d->rear = (d->rear + 1) % TAM;
    }
}

ITEM retrieve(TDeque *d, int extremidade)
{
    // Seria bom lidar com o underflow também (num cenário real, no nosso caso, a questão não pede isso)
    /* if (isempty(d))
    {
        printf("Underflow\n");
        return -1;
    }
    */

    // printf("front: %d, rear: %d, extremidade: %d\n", d->front, d->rear, extremidade);

    ITEM result;

    // Se a extremidade for 1, o elemento é retirado do início
    if (extremidade == 1)
    {
        // Armazenamos o valor do início
        result = d->vet[d->front];

        // E incrementamos o início (front) tomando cuidado para não ultrapassar o tamanho do array (com o operador %)
        d->front = (d->front + 1) % TAM;
    }
    else
    {
        // Se a extremidade for 2, o elemento é retirado do fim
        // Decrementamos o fim (rear) tomando cuidado para não ultrapassar o tamanho do array (com o operador %)
        d->rear = (d->rear - 1 + TAM) % TAM;

        // E armazenamos o valor do fim
        result = d->vet[d->rear];
    }

    return result;
}

void preenche(TDeque *d)
{
    ITEM x;
    int qtd, extremidade, i;

    scanf("%d%*c", &qtd);

    for (i = 0; i < qtd; i++)
    {
        scanf("%c %d%*c", &x, &extremidade);
        store(d, extremidade, x);
    }
}

void exibe(TDeque *d)
{
    int extremidade;

    while (scanf("%d", &extremidade) != EOF)
    {
        if (extremidade == 1)
            printf("INICIO = %c\n", retrieve(d, extremidade));
        else
            printf("FIM = %c\n", retrieve(d, extremidade));
    }
}

int main(void)
{
    TDeque d;

    create(&d);
    preenche(&d);
    exibe(&d);
    destroy(&d);

    return 0;
}
