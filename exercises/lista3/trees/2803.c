#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/*
-> Descrição
    Sua tarefa é simples: dadas várias árvores em notação de parênteses, concatene a primeira árvore com as demais fornecidas.
    Por exemplo, as árvores (1(2()())(3()())) e (3(4()())(5()())) são as representações em notação de parênteses das árvores mostradas abaixo:

      1       3
     / \     / \
    2   3   4   5

    O resultado da concatenação da segunda árvore com a primeira será (1(2()())(3(4()())(5()()))):

          1
         / \
        2   3
           / \
          4   5

    Obs:
        - A primeira árvore informada é a matriz.
        - A segunda árvore informada deve ser concatenada com a matriz. A árvore resultante dessa concatenação será sua nova matriz.
        - A terceira árvore informada (se houver) será concatenada com a nova matriz obtida no passo anterior gerando uma nova matriz e assim por diante...
        - É garantido que todas as árvores fornecidas têm nós de valores distintos (exceto as raízes).

-> Formato de entrada
    A entrada consiste de várias linhas.
    Cada linha contendo uma String que é a representação de uma árvore em notação de parênteses.
    As entradas se encerram ao ser fornecida a String "()".

-> Formato de saída
    A saída deve ser uma String com a representação em notação de parênteses da matriz resultante de todas as concatenações de árvores.
*/

typedef struct binary_tree
{
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

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

int has_value_in_tree(binary_tree *bt, int value)
{
    if (bt == NULL)
    {
        return 0;
    }

    if (bt->item == value)
    {
        return 1;
    }

    has_value_in_tree(bt->left, value);
    has_value_in_tree(bt->right, value);

    return has_value_in_tree(bt->left, value) || has_value_in_tree(bt->right, value);
}

binary_tree *search_value_in_tree(binary_tree *bt, int value)
{
    if (bt == NULL)
    {
        return NULL;
    }

    // Se o valor do nó atual for igual ao valor procurado e ele for uma folha, retornamos o nó atual
    if (bt->item == value && bt->left == NULL && bt->right == NULL)
    {
        return bt;
    }

    // Se o valor do nó atual for igual ao valor procurado, retornamos o nó atual
    binary_tree *left = search_value_in_tree(bt->left, value);
    binary_tree *right = search_value_in_tree(bt->right, value);

    if (left != NULL)
    {
        return left;
    }

    if (right != NULL)
    {
        return right;
    }

    return NULL;
}

binary_tree *concatenate_trees(binary_tree *tree1, binary_tree *tree2)
{
    // Precisamos concatenar as árvores, e para isso, ao encontrar um nó em comum, devemos substituir esse nó em comum pela árvore 2 e seus descendentes

    // Se a árvore 1 for nula, retornamos a árvore 2
    if (tree1 == NULL)
    {
        return tree2;
    }

    // Se a árvore 2 for nula, retornamos a árvore 1
    if (tree2 == NULL)
    {
        return tree1;
    }

    // Se encontrarmos um nó em comum, substituímos esse nó em comum pela árvore 2
    if (has_value_in_tree(tree1, tree2->item))
    {
        // printf("Nó em comum: %d\n", tree2->item);
        binary_tree *node = search_value_in_tree(tree1, tree2->item);
        node->left = tree2->left;
        node->right = tree2->right;
        return tree1;
    }

    // Se a árvore 1 somente for constituída de raiz, retornamos a árvore 2
    if (tree1->left == NULL && tree1->right == NULL)
    {
        // printf("Árvore 1 somente com raiz\n");
        return tree2;
    }

    // Se a árvore 2 somente for constituída de raiz, retornamos a árvore 1
    if (tree2->left == NULL && tree2->right == NULL)
    {
        // printf("Árvore 2 somente com raiz\n");
        return tree1;
    }

    // Se não encontrarmos um nó em comum, retornamos a árvore 1
    return tree1;
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
            stack[++top] = str[i];
        }
        else if (str[i] == ')')
        {
            if (stack[top] == '(')
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

    // Se nos depararmos com um parêntese de abertura, o próximo caractere será o valor do nó
    if (str[start] == '(')
    {
        start++;
    }

    // Se nos depararmos com um parêntese de fechamento, retornamos NULL
    if (str[start] == ')')
    {
        return NULL;
    }

    // Encontramos o valor do nó
    int i = start;
    int sign = 1;

    // Verifica se o número é negativo
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }

    // Verifica se há um número após o parêntese de abertura, se não houver, retorna NULL
    if (str[i] == '(' || str[i] == ')')
    {
        return NULL;
    }

    while (str[i] != '(' && str[i] != ')')
    {
        i++;
    }

    int item = 0;
    for (int j = start; j < i; j++)
    {
        // Ignora o sinal negativo na conversão para inteiro
        if (str[j] != '-')
        {
            item = item * 10 + (str[j] - '0');
        }
    }

    // Se o número for negativo, multiplica por -1
    item *= sign;

    binary_tree *root = create_empty_binary_tree(item);

    // Encontramos o índice do parêntese de fechamento do nó atual
    int index = find_index(str, start, end);

    // Se o índice for -1, significa que não encontramos o parêntese de fechamento
    if (index != -1)
    {
        root->left = from_string(str, i, index);
        root->right = from_string(str, index + 1, end - 1);
    }

    return root;
}

char *to_string(binary_tree *bt)
{
    if (bt == NULL)
    {
        return "()";
    }
    char *left = to_string(bt->left);
    char *right = to_string(bt->right);
    char *tree = (char *)malloc(1000 * sizeof(char)); // (char *)malloc(sizeof(char) * (strlen(left) + strlen(right) + 10));
    sprintf(tree, "(%d%s%s)", bt->item, left, right);
    return tree;
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

void print_tree(binary_tree *root, int level, char direction)
{
    if (root == NULL)
    {
        return;
    }

    print_tree(root->right, level + 1, '/');

    for (int i = 0; i < level; i++)
    {
        printf("    ");
    }

    printf("%c~%d\n", direction, root->item);

    print_tree(root->left, level + 1, '\\');
}

int main()
{
    char tree[1000];
    fgets(tree, 1000, stdin);

    binary_tree *root = from_string(tree, 0, strlen(tree) - 1);

    /* printf("Árvore Original:\n");
    print_tree(root, 0, ' ');
    printf("\nPré-ordem: ");
    print_pre_order(root);
    printf("\n"); */

    while (1)
    {
        char tree[1000];
        fgets(tree, 1000, stdin);
        if (tree[0] == '(' && tree[1] == ')')
        {
            break;
        }
        binary_tree *new_tree = from_string(tree, 0, strlen(tree) - 1);

        root = concatenate_trees(root, new_tree);

        /* printf("Nova Árvore:\n");
        print_tree(new_tree, 0, ' ');
        printf("\nPré-ordem: ");
        print_pre_order(new_tree);
        printf("\n");
        printf("Árvore concatenada:\n");
        print_tree(root, 0, ' ');
        printf("\nPré-ordem: ");
        print_pre_order(root);
        printf("\n"); */
    }

    char *result = to_string(root);
    printf("%s\n", result);
}