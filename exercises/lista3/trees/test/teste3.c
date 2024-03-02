#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tree structure
typedef struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
} tree;

tree *create_tree(
    int item, tree *left, tree *right)
{
    tree *new_tree =
        (tree *)malloc(sizeof(tree));
    new_tree->data = item;
    new_tree->left = left;
    new_tree->right = right;
    return new_tree;
}

// Função para encontrar o índice do parêntese de fechamento para um parêntese de abertura dado
int find_index(char *str, int start, int end)
{
    if (start > end)
    {
        return -1;
    }

    char stack[end - start + 1];
    int top = -1;
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

// Função para construir a árvore de forma recursiva a partir da string
tree *from_string(char *str, int start, int end)
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

    tree *root = create_tree(atoi(num), NULL, NULL);

    int index = -1;

    if (start <= end && str[start] == '(')
    {
        index = find_index(str, start, end);
    }

    if (index != -1)
    {
        root->left = from_string(str, start + 1, index - 1);
        root->right = from_string(str, index + 2, end - 1);
    }

    return root;
}

// Função para construir a árvore binária a partir da string
tree *get_tree_from_string(char *s)
{
    return from_string(s, 0, strlen(s) - 1);
}

void print_pre_order(tree *bt)
{
    if (bt != NULL)
    {
        printf("%d ", bt->data);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }
}

int main()
{
    // Os exemplos das questões do Huxley possuem parênteses no início e no fim da string, o que quebra a função from_string, que imprime um 0 no início da árvore
    char s[] = "(12(7(3()())(10()(11()())))(23(17()())(31()())))";
    struct tree *root = get_tree_from_string(s);

    print_pre_order(root);

    return 0;
}
