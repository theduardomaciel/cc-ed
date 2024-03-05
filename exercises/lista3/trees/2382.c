#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

/*
-> Descrição
    Em estrutura de dados, chama-se de Árvore Binária Completa de grau D uma árvore em que todos os nós (exceto as folhas) possuem dois filhos e todas as folhas estão no mesmo nível D, sendo D a altura da árvore.

    Por exemplo:

    (7(13(0()())(1()()))(11(2()())(9()())))

    É a representação em notação de parênteses da árvore abaixo:

        7
       / \
      13  11
     / \  / \
    0  1 2  9

    Esta árvore binária é completa de grau = 2 pois:
        1. todos os nós possuem dois filhos (exceto as folhas),
        2. todas as folhas estão no mesmo nível e
        3. a altura da árvore é 2 (a altura na raiz é 0).

    Sua tarefa é simples. Dada uma árvore binária em notação de parêntese, verifique se ela é completa ou não.
    Se for, informe o total de nós da árvore. Caso contrário, informe quais nós tem apenas um filho.

-> Formato de entrada
    A entrada consiste de uma linha contendo a string da árvore em notação de parênteses.

-> Formato de saída
    A saída consiste de duas linhas:
        - A primeira linha contém a mensagem "completa" caso a árvore binária seja completa e "nao completa", caso contrário.
        - Na segunda linha, deve-se exibir:
            * Caso a árvore seja completa: a mensagem "total de nos: N" onde N é um inteiro representando o total de nós na árvore
            * Caso a árvore não seja completa: a mensagem "nos com um filho: N1 N2 N3 ... Ni", onde cada Ni é o inteiro que representa o nó. (N1, N2, N3, ... , Ni estão in ordem).
    - Cada linha deve conter um caractere de quebra de linha no final
    - Observe que na impressão da lista de nós, todos os nós estão separados por um caractere de espaço exceto o último nó.
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

    printf("%c--%d\n", direction, root->item);

    print_tree(root->left, level + 1, '\\');
}

int get_tree_height(binary_tree *bt)
{
    if (bt == NULL)
    {
        return -1;
    }
    else
    {
        int left_height = get_tree_height(bt->left);
        int right_height = get_tree_height(bt->right);

        if (left_height > right_height)
        {
            return (left_height + 1);
        }
        else
        {
            return (right_height + 1);
        }
    }
}

int get_node_depth(binary_tree *bt, int item, int depth)
{
    if (bt == NULL)
    {
        return -1;
    }
    else if (bt->item == item)
    {
        return depth;
    }
    else
    {
        int left_depth = get_node_depth(bt->left, item, depth + 1);
        int right_depth = get_node_depth(bt->right, item, depth + 1);

        if (left_depth != -1)
        {
            return left_depth;
        }
        else
        {
            return right_depth;
        }
    }
}

int is_leaf(binary_tree *bt)
{
    return (bt->left == NULL && bt->right == NULL);
}

void print_not_binary_nodes(binary_tree *bt)
{
    if (bt != NULL)
    {
        print_not_binary_nodes(bt->left);

        if (bt->left == NULL && bt->right != NULL || bt->left != NULL && bt->right == NULL)
        {
            printf("%d ", bt->item);
        }

        print_not_binary_nodes(bt->right);
    }
}

int get_total_tree_nodes_amount(binary_tree *bt)
{
    if (bt == NULL)
    {
        return 0;
    }
    else
    {
        return (1 + get_total_tree_nodes_amount(bt->left) + get_total_tree_nodes_amount(bt->right));
    }
}

int check_complete(binary_tree *bt, int index, int total_nodes)
{
    if (bt == NULL)
    {
        return 1;
    }

    if (index >= total_nodes)
    {
        return 0;
    }

    return check_complete(bt->left, 2 * index + 1, total_nodes) &&
           check_complete(bt->right, 2 * index + 2, total_nodes);
}

int is_tree_complete(binary_tree *bt, int *total_nodes_amount)
{
    if (bt == NULL)
    {
        return 1;
    }

    *total_nodes_amount = get_total_tree_nodes_amount(bt);
    return check_complete(bt, 0, *total_nodes_amount);
}

int main()
{
    char input[1000];

    while (scanf("%s", input) != EOF)
    {
        binary_tree *bt = from_string(input, 0, strlen(input) - 1);

        int total_nodes_amount;
        int is_complete = is_tree_complete(bt, &total_nodes_amount);

        if (is_complete)
        {
            printf("completa\n");
            printf("total de nos: %d\n", total_nodes_amount);
        }
        else
        {
            printf("nao completa\n");
            printf("nos com um filho: ");
            print_not_binary_nodes(bt);
            printf("\n");
        }
    }

    return 0;
}