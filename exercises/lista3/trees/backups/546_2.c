#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

/*
-> Descrição
    Escreva um programa que aceita uma árvore binária e retorna VERDADEIRO se for uma árvore de busca binária válida, e FALSO caso contrário.

-> Formato de entrada
    Uma árvore de busca binária, representada da seguinte maneira:
    (5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))

-> Formato de saída
    VERDADEIRO, se a árvore for uma árvore de busca binária.
    FALSO, se não for.
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

binary_tree *string_to_tree(char *str, int *index)
{
    if (str[*index] == '\0' || str[*index] == ')')
    {
        (*index)++;
        return NULL;
    }

    // Precisamos percorrer a string até o final do número
    int i = *index;

    while (str[i] != '(' && str[i] != ')' && str[i] != '\0')
    {
        // printf("Navegando por %c\n", str[i]);
        i++;
    }

    // Extraímos o número da string
    char *number = (char *)malloc(1000 * sizeof(char));
    int j = 0;

    while (*index < i)
    {
        number[j++] = str[(*index)++];
    }

    number[j] = '\0';

    int num = atoi(number);
    // printf("number: %s -> num: %d\n", number, num);

    // Criamos um novo nó com o número extraído
    binary_tree *root = create_binary_tree(num, NULL, NULL);

    // Procuramos por '(' e recursivamente chamamos a função para as subárvores esquerda e direita
    if (str[*index] == '(')
    {
        (*index)++;
        root->left = string_to_tree(str, index);
        (*index)++;
        root->right = string_to_tree(str, index);
        (*index)++;
    }

    return root;
}

void print_pre_order(binary_tree *bt)
{
    if (!is_binary_tree_empty(bt))
    {
        printf("%d ", bt->item);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }
}

int isBST(binary_tree *root, int min, int max)
{
    if (root == NULL)
    {
        return 1;
    }

    if (root->item < min || root->item > max)
    {
        return 0;
    }

    // Recursivamente checa as subárvores esquerda e direita
    return isBST(root->left, min, root->item - 1) && isBST(root->right, root->item + 1, max);
}

int main()
{
    char *left_tree = (char *)malloc(100000 * sizeof(char));
    char *right_tree = (char *)malloc(100000 * sizeof(char));

    /* scanf("%s", left_tree);
    getchar();
    scanf("%s", right_tree); */

    getchar(); // (
    int first_node = getchar() - '0';

    scanf("%s", left_tree);
    getchar();

    scanf("%s", right_tree);

    // printf("%s\n", left_tree);
    // printf("%s\n", right_tree);

    // Navegamos por cada caractere da string da subárvore esquerda adicionando os valores em uma pilha
    // Em seguida, criamos a subárvore esquerda a partir da pilha
    int index = 1;
    binary_tree *left_binary_tree = string_to_tree(left_tree, &index);
    // print_pre_order(left_binary_tree);

    // printf("\n");

    index = 1;
    binary_tree *right_binary_tree = string_to_tree(right_tree, &index);
    // print_pre_order(right_binary_tree);

    // printf("\n");

    binary_tree *bt = create_binary_tree(first_node, left_binary_tree, right_binary_tree);
    // print_pre_order(bt);

    // printf("\n");

    if (isBST(bt, INT_MIN, INT_MAX))
    {
        printf("VERDADEIRO\n");
    }
    else
    {
        printf("FALSO\n");
    }

    return 0;
}