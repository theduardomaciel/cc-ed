#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*
-> Descrição
    Assuma que partimos de uma árvore de busca binária vazia inicialmente, e recebemos uma sequência de números a serem inseridos. Para cada inserção, devemos imprimir a árvore resultante da inserção, no formato de parênteses discutido abaixo.

-> Formato de entrada
    A entrada consiste de uma sequência de números a serem lidos e inseridos na árvore de busca binária (inicialmente vazia).

-> Formato de saída
    A saída deve imprimir o valor resultante da árvore T para cada inserção de um número X, no formato:

    ----
    Adicionando X
    imprime T no formato de parênteses
    ----

    Para a impressão de uma árvore T, utilizamos o formato de parênteses, da mesma forma que em outras questões de árvores binárias. Isto é, todo nó N é representado como ( VALOR N.left N.right ), onde N.left e N.right são os nós filhos da esquerda e direita de N.

    Para o caso de um nó folha, contendo o valor 15, o nó deve ser impresso como ( 15 () () ).
*/

typedef struct binary_tree binary_tree;

struct binary_tree
{
    int item;
    binary_tree *left;
    binary_tree *right;
};

// Implementation

binary_tree *create_empty_binary_tree()
{
    return NULL;
}

binary_tree *create_binary_tree(
    int item, binary_tree *left, binary_tree *right)
{
    binary_tree *new_binary_tree =
        (binary_tree *)malloc(sizeof(binary_tree));
    new_binary_tree->item = item;
    new_binary_tree->left = left;
    new_binary_tree->right = right;
    return new_binary_tree;
}

int is_binary_tree_empty(binary_tree *bt)
{
    return (bt == NULL);
}

binary_tree *add(binary_tree *bt, int item)
{
    if (bt == NULL)
    {
        bt = create_binary_tree(item, NULL, NULL);
    }
    else if (bt->item > item)
    {
        bt->left = add(bt->left, item);
    }
    else
    {
        bt->right = add(bt->right, item);
    }
    return bt;
}

void print_in_parenthesis(binary_tree *bt)
{
    if (bt == NULL)
    {
        printf(" () ");
    }
    else
    {
        printf(" ( %d ", bt->item);
        print_in_parenthesis(bt->left);
        print_in_parenthesis(bt->right);
        printf(") ");
    }
}

int main()
{
    int number;

    // Inicializamos a árvore de busca binária
    binary_tree *bt = create_empty_binary_tree();

    while (scanf("%d", &number) != EOF)
    {
        printf("----\n");
        printf("Adicionando %d\n  ", number);

        // Inserimos o número na árvore de busca binária
        bt = add(bt, number);

        // Imprimimos a árvore resultante
        print_in_parenthesis(bt);
        printf("\n");
    }

    printf("----\n");

    return 0;
}