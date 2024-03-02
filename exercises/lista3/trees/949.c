#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
-> Descrição
    Ambrosinho está com dificuldades em construir um algoritmo para encontrar o menor valor e o maior valor dos nós de uma árvore binária e você como colega vai ajudá-lo a construir o algoritmo.

    Cada nó tem três informações, o valor do nó, o filho a esquerda e o filho a direita.

    Dado uma árvore binária encontre o menor e maior valor em cada nível da árvore.
    Sempre iniciamos no nó 0.
    O nível de um nó é a altura dele.

-> Formato de entrada
    A entrada consiste em um número N, seguido de N linhas, cada linha Ni contém 3 inteiros, o valor do nó, o filho da esquerda e o filho da direita do i-ésimo nó.

    - Caso o nó não possua nenhum ramo filho, esse inteiro será -1.

    Exemplo:
    6
    10 2 1
    14 -1 5
    19 3 4
    5 -1 -1
    23 -1 -1
    51 -1 -1

    Os nós que estão no nível 1: { 0 };
    Os nós que estão no nível 2: { 1, 2 };
    Os nós que estão no nível 3: { 3, 4, 5 };

-> Formato de saída
    A saída terá a altura da árvore linhas, em cada linha terá a mensagem:
    Nivel i: Maior = X, Menor = Y.
*/

typedef struct binary_tree
{
    int item;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

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

// Função para encontrar os valores mínimos e máximos por nível
// É basicamente um BFS (Busca em Largura) na árvore
void find_min_max(binary_tree *root, int level, int *min_values, int *max_values)
{
    if (root == NULL)
        return;

    // Atualizamos os valores mínimos e máximos para o nível atual
    if (root->item < min_values[level])
        min_values[level] = root->item;

    if (root->item > max_values[level])
        max_values[level] = root->item;

    // Chamamos a função recursivamente para os filhos
    find_min_max(root->left, level + 1, min_values, max_values);
    find_min_max(root->right, level + 1, min_values, max_values);
}

int calculate_tree_height(binary_tree *root)
{
    if (root == NULL)
        return 0;

    // Calculamos a altura da árvore recursivamente
    int left_height = calculate_tree_height(root->left);
    int right_height = calculate_tree_height(root->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

void print_result(int height, int *min_values, int *max_values)
{
    for (int i = 1; i <= height; i++)
    {
        printf("Nivel %d: Maior = %d, Menor = %d\n", i, max_values[i], min_values[i]);
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

int main()
{
    int n;
    scanf("%d", &n);

    // O primeiro nó sempre sera 0, então vamos criar a raiz da árvore
    int item[n], left[n], right[n];

    binary_tree *root = NULL;

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d", &item[i], &left[i], &right[i]);
    }

    // Para cada item, vamos criar um nó e adicionar na árvore
    // Os valores de left[i] e right[i] são os índices dos nós filhos
    // Se left[i] == -1, então o nó não tem filho à esquerda
    // Se right[i] == -1, então o nó não tem filho à direita
    // Já os valores de item[i] são os valores dos nós

    binary_tree *nodes[n];

    for (int i = 0; i < n; i++)
    {
        nodes[i] = create_binary_tree(item[i], NULL, NULL);
    }

    for (int i = 0; i < n; i++)
    {
        if (left[i] != -1)
        {
            nodes[i]->left = nodes[left[i]];
        }
        if (right[i] != -1)
        {
            nodes[i]->right = nodes[right[i]];
        }
    }

    root = nodes[0];

    /* binary_tree *teste = create_binary_tree(
        10,
        create_binary_tree(
            14,
            create_binary_tree(19, create_binary_tree(5, NULL, NULL), create_binary_tree(23, NULL, NULL)),
            create_binary_tree(51, NULL, NULL)),
        create_binary_tree(2, NULL, NULL)); */

    // print_tree(root, 0, '-');

    // Determinar a altura da árvore
    int height = calculate_tree_height(root);

    // Inicializar arrays para armazenar os valores mínimos e máximos por nível
    int min_values[height + 1];
    int max_values[height + 1];

    for (int i = 0; i <= height; i++)
    {
        min_values[i] = INT_MAX; // Inicializar com o maior valor possível
        max_values[i] = INT_MIN; // Inicializar com o menor valor possível
    }

    // Encontrar os valores mínimos e máximos por nível
    find_min_max(root, 1, min_values, max_values);

    // Imprimir o resultado
    print_result(height, min_values, max_values);

    return 0;
}