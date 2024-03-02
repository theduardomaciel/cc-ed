#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
-> Descrição
    Escreva um programa que aceita uma árvore binária, e um inteiro N.

    Seu programa deve ser capaz de dizer se existe um nó cujo inteiro é N bem como em que profundidade ele se encontra.

-> Formato de entrada

    Uma árvore binária, representada da seguinte maneira:
    (5(4(11(7()())(2()()))())  (8(13()())(4()(1()()))))

    Que é a arvore:
            5
         /    \
        4      8
       /      / \
      11     13  4
     /  \         \
    7   2         1

    E um inteiro N

    Formato de saída
    Duas linhas. Em uma delas, você irá dizer ESTA NA ARVORE, caso o nó cujo inteiro é N esteja na árvore, e NAO ESTA NA ARVORE, caso contrário. Na outra linha, você irá informar em que profundidade da árvore o nó está. Caso não esteja, imprima -1.

    ENTRADA:
    (12(7(3()())(10()(11()())))(23(17()())(31()())))
    11

    SAÍDA:
    ESTA NA ARVORE
    3
*/

struct node
{
    int data;
    struct node *left;
    struct node *right;
};

struct node *create_node(int data)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

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

struct node *from_string(char *str, int start, int end)
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

    struct node *root = create_node(atoi(num));

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

int find_node(struct node *root, int n)
{
    // Se a árvore estiver vazia, retornamos 0
    if (root == NULL)
    {
        return 0;
    }

    // Se a árvore não for a raiz, verificamos se o nó atual tem a mesma chave da raiz
    if (root->data == n)
    {
        return 1;
    }

    /// Chamamos a função recursivamente para os filhos da árvore
    return find_node(root->left, n) || find_node(root->right, n);
}

int depth(struct node *root, int n)
{
    // Se a árvore estiver vazia, retornamos -1
    if (root == NULL)
    {
        return -1;
    }

    // Se a árvore não for a raiz, verificamos se o nó atual tem a mesma chave da raiz
    if (root->data == n)
    {
        return 0;
    }

    // Chamamos a função recursivamente para os filhos da árvore
    int left = depth(root->left, n);
    int right = depth(root->right, n);

    if (left != -1)
    {
        return left + 1;
    }
    else if (right != -1)
    {
        return right + 1;
    }

    return -1;
}

int main()
{
    char *str = (char *)malloc(1000 * sizeof(char));
    scanf("%[^\n]", str); // Utilizamos o %[^\n] para ler a string contando os espaços até a quebra de linha

    // printf("Antes: %s\n", str);

    // Como as strings de entrada possuem um parênteses a mais no início e no final, removemos eles
    str++;
    str[strlen(str) - 1] = '\0';

    // printf("Depois: %s\n", str);

    int n;
    scanf("%d", &n);

    struct node *root = from_string(str, 0, strlen(str) - 1);

    if (find_node(root, n))
    {
        printf("ESTA NA ARVORE\n");
        printf("%d\n", depth(root, n));
    }
    else
    {
        printf("NAO ESTA NA ARVORE\n");
        printf("-1\n");
    }

    return 0;
}