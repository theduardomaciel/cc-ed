#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    struct node *esq;
    struct node *dir;
    int valor;
};

typedef struct node Node;

Node *criaNo(int value)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->valor = value;
    temp->esq = temp->dir = NULL;

    return temp;
}

void construir(Node *raiz)
{
    int value;
    scanf("%d", &value);

    if (value == -1)
        return;

    raiz->esq = criaNo(value);
    construir(raiz->esq);

    scanf("%d", &value);
    if (value == -1)
        return;

    raiz->dir = criaNo(value);
    construir(raiz->dir);
}

bool inOrder(Node *raiz)
{
    if (raiz->valor == -1)
        return true;

    if (raiz->esq != NULL)
    {
        if (raiz->esq->valor > raiz->valor)
            return false;

        if (!inOrder(raiz->esq))
            return false;
    }

    if (raiz->dir != NULL)
    {
        if (raiz->dir->valor < raiz->valor && raiz->dir->valor != -1)
            return false;

        if (!inOrder(raiz->dir))
            return false;
    }

    return true;
}

int main()
{
    char str[100];
    scanf("%s", str);

    int atual = 0;
    bool encontrou = false;

    Node *raiz = criaNo(0);

    for (int i = 0; str[i]; ++i)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            atual = atual * 10 + (str[i] - '0');
            encontrou = true;
        }
        else
        {
            if (str[i] == ')' && str[i - 1] == '(')
                atual = -1;
            else if (encontrou)
            {
                Node *no = criaNo(atual);
                raiz->esq = no;
                construir(no);
            }

            atual = 0;
            encontrou = false;
        }
    }

    bool retorno = inOrder(raiz);
    printf("%s\n", (retorno ? "VERDADEIRO" : "FALSO"));

    return 0;
}
