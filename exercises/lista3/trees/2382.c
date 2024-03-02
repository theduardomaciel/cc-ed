#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

    Esta árvore binária é completa de grau = 2 pois todos os nós possuem dois filhos (exceto as folhas), todas as folhas estão no mesmo nível e a altura da árvore é 2 (a altura na raiz é 0).

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

typedef struct
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

    // Como as strings de entrada possuem um parênteses a mais no início e no final, removemos eles
    input++;
    input[strlen(input) - 1] = '\0';

    printf("Depois: %s\n", input);

    int index = 0;

    return 0;
}