#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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

typedef struct node node;
struct node
{
    int item;
    node *next;
};

typedef struct stack stack;
struct stack
{
    node *top;
};

stack *create_stack()
{
    stack *new_stack = (stack *)malloc(sizeof(stack));
    new_stack->top = NULL;
    return new_stack;
}

int is_stack_empty(stack *stack)
{
    return (stack->top == NULL);
}

void push(stack *stack, int item)
{
    node *new_top = (node *)malloc(sizeof(node));
    new_top->item = item;
    new_top->next = stack->top;
    stack->top = new_top;
}

int pop(stack *stack)
{
    if (is_stack_empty(stack))
    {
        printf("Stack underflow\n");
        return -1;
    }
    else
    {
        node *top = stack->top;
        int item = top->item;

        stack->top = top->next;
        free(top);

        return item;
    }
}

// ------

typedef struct binary_tree binary_tree;

struct binary_tree
{
    int item;
    binary_tree *left;
    binary_tree *right;
};

// Abstract Data Type (ADT)

binary_tree *create_empty_binary_tree();
binary_tree *create_binary_tree(
    int item, binary_tree *left, binary_tree *right);
binary_tree *search(binary_tree *bt, int item);
int is_binary_tree_empty(binary_tree *bt);
void print_in_order(binary_tree *bt);
void print_pre_order(binary_tree *bt);
void print_post_order(binary_tree *bt);

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

    // Recursively check the left and right subtrees
    return isBST(root->left, min, root->item - 1) && isBST(root->right, root->item + 1, max);
}

binary_tree *generate_tree(char *tree)
{
    binary_tree *bt = create_empty_binary_tree();

    int is_bracket_open = 0;

    for (int i = 0; i < strlen(tree); i++)
    {
        if (tree[i] == '(')
        {
            /// push(s, tree[i]);
            is_bracket_open = 1;
        }
        else if (tree[i] == ')')
        {
            is_bracket_open = 0;
        }
        else if (tree[i] != '(' && tree[i] != ')')
        {
            /* int item = tree[i] - '0';
            bt = add(bt, item); */

            // Precisamos percorrer a string até o final do número
            int j = i;
            while (tree[j] != '(' && tree[j] != ')')
            {
                j++;
            }

            char *number = (char *)malloc(1000 * sizeof(char));
            int k = 0;
            for (int l = i; l < j; l++)
            {
                number[k] = tree[l];
                k++;
            }

            int item = atoi(number);

            bt = add(bt, item);

            i = j - 1;

            free(number);
        }
    }

    return bt;
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
    char *left_tree = (char *)malloc(1000 * sizeof(char));
    char *right_tree = (char *)malloc(1000 * sizeof(char));

    scanf("%s", left_tree);
    getchar();
    scanf("%s", right_tree);

    printf("%s\n", left_tree);
    printf("%s\n", right_tree);

    // Navegamos por cada caractere da string da subárvore esquerda adicionando os valores em uma pilha
    // Em seguida, criamos a subárvore esquerda a partir da pilha
    binary_tree *left_binary_tree = generate_tree(left_tree);
    print_pre_order(left_binary_tree);
    /*

    // Navegamos por cada caractere da string da subárvore direita adicionando os valores em uma pilha
    // Em seguida, criamos a subárvore direita a partir da pilha
    binary_tree *right_binary_tree = generate_tree(right_tree);

    // Criamos a árvore binária a partir das subárvores esquerda e direita
    binary_tree *binary_tree = create_binary_tree(0, left_binary_tree, right_binary_tree);

    // Verificamos se a árvore é uma árvore de busca binária
    if (isBST(binary_tree, -1000000, 1000000))
    {
        printf("VERDADEIRO\n");
    }
    else
    {
        printf("FALSO\n");
    } */

    return 0;
}