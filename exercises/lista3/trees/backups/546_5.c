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

binary_tree *parse_parenthesis_format(char *str, int *index)
{
    if (str[*index] == '\0')
    {
        return NULL;
    }

    // Pulamos os espaços
    while (str[*index] == ' ')
    {
        (*index)++;
    }

    // Procuramos por um parênteses aberto
    if (str[*index] == '(')
    {
        (*index)++; // Movemos para após o '('

        // Iniciamos agora o processo de conversão do valor para int

        // 1. Se o valor for negativo, multiplicamos por -1 (nunca se sabe, né?)
        int value = 0;
        int sign = 1;
        if (str[*index] == '-')
        {
            sign = -1;
            (*index)++;
        }

        // 2. Enquanto for um dígito, multiplicamos o valor por 10 e somamos o dígito, para converter o valor para int
        while (isdigit(str[*index]))
        {
            value = value * 10 + (str[*index] - '0');
            (*index)++;
        }
        value *= sign; // e multiplicamos pelo sinal que guardamos

        // Se o valor for zero, pulamos o nó e suas subárvores
        if (value == 0)
        {
            while (str[*index] != ')')
            {
                (*index)++;
            }

            (*index)++; // Pulamos o parênteses fechado

            return NULL;
        }

        // Criamos uma árvore com o valor
        binary_tree *node = create_binary_tree(value, NULL, NULL);

        // Chamamos a função recursivamente para as subárvores da esquerda e da direita
        node->left = parse_parenthesis_format(str, index);
        node->right = parse_parenthesis_format(str, index);

        // Pulamos os espaços e o parênteses fechado
        while (str[*index] == ' ')
        {
            (*index)++;
        }

        if (str[*index] == ')')
        {
            (*index)++;
        }

        return node; // Por fim, retornamos a árvore
    }

    return NULL;
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

    printf("Antes: %s\n", input);

    // Como as strings de entrada possuem um parênteses a mais no início e no final, removemos eles de cada árvore informada

    int index = 0;
    binary_tree *root = parse_parenthesis_format(input, &index); // Aqui, montamos a árvore com base na string

    printf("Pré-ordem: ");
    print_pre_order(root);

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
