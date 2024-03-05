#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

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

binary_tree *create_empty_binary_tree(int item)
{
    binary_tree *node = (binary_tree *)malloc(sizeof(binary_tree));
    node->item = item;
    node->left = node->right = NULL;
    return node;
}

binary_tree *create_binary_tree(int item, binary_tree *left, binary_tree *right)
{
    binary_tree *new_binary_tree = (binary_tree *)malloc(sizeof(binary_tree));
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

int is_binary_search_tree(binary_tree *root, int min, int max)
{
    if (root == NULL)
    {
        return 1;
    }

    if (root->item < min || root->item > max)
    {
        return 0;
    }

    return is_binary_search_tree(root->left, min, root->item - 1) &&
           is_binary_search_tree(root->right, root->item + 1, max);
}

int find_index(char *str, int start, int end)
{
    if (start > end)
    {
        return -1;
    }

    char stack[end - start + 1];
    int top = -1;

    // Percorremos a string e empilhamos os parênteses de abertura
    for (int i = start; i <= end; i++)
    {
        if (str[i] == '(')
        {
            stack[++top] = '(';
        }
        else if (str[i] == ')')
        {
            if (top >= 0)
            {
                top--;
                if (top == -1)
                {
                    return i;
                }
            }
        }
    }
    return -1;
}

binary_tree *from_string(char *str, int start, int end)
{
    if (start > end)
    {
        return NULL;
    }

    char num[25]; // Assumindo que o comprimento máximo de um número é de 25 dígitos
    int numIndex = 0;

    while (start < strlen(str) && str[start] >= '0' && str[start] <= '9')
    {
        num[numIndex++] = str[start++];
    }
    num[numIndex] = '\0';

    binary_tree *root = create_empty_binary_tree(atoi(num));

    int index = -1;

    // Se o caractere atual for um parênteses de abertura, encontramos o índice do parênteses de fechamento correspondente
    if (start <= end && str[start] == '(')
    {
        index = find_index(str, start, end);
    }

    // Se encontramos o índice do parênteses de fechamento correspondente, chamamos a função recursivamente para a subárvore esquerda e direita
    if (index != -1)
    {
        root->left = from_string(str, start + 1, index - 1);
        root->right = from_string(str, index + 2, end - 1);
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

int main()
{
    char *input = (char *)malloc(1000 * sizeof(char));
    scanf("%[^\n]", input); // Usamos isso pra pegar a string inteira, incluindo espaços

    // printf("Antes: %s\n", input);

    // Como as strings de entrada possuem um parênteses a mais no início e no final, removemos eles de cada árvore
    input[strlen(input) - 1] = '\0';

    // Removemos os espaços do input
    int j = 0;
    for (int i = 0; input[i]; i++)
    {
        if (input[i] != ' ')
        {
            input[j++] = input[i];
        }
    }

    int index = 0;
    binary_tree *root = from_string(input, 1, strlen(input) - 2);

    // printf("Pré-ordem: ");
    // print_pre_order(root);

    // Checamos se a árvore é uma árvore de busca binária
    if (is_binary_search_tree(root, INT_MIN, INT_MAX))
    {
        printf("VERDADEIRO\n");
    }
    else
    {
        printf("FALSO\n");
    }

    return 0;
}
