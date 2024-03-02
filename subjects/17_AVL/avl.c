#include <stdio.h>
#include <stdlib.h>

typedef struct binary_tree
{
    int item;
    int height;
    struct binary_tree *left;
    struct binary_tree *right;
} binary_tree;

// ADT
binary_tree *create_empty_binary_tree();
binary_tree *create_binary_tree(
    int item, binary_tree *left, binary_tree *right);
binary_tree *add_node(binary_tree *bt, int item);
int is_empty(binary_tree *bt);
int height(binary_tree *bt);
int balance_factor(binary_tree *bt);
binary_tree *rotate_left(binary_tree *bt);
binary_tree *rotate_right(binary_tree *bt);

// A função create_empty_binary_tree cria uma árvore binária vazia.
binary_tree *create_empty_binary_tree()
{
    return NULL;
}

// A função create_binary_tree cria uma árvore binária com um nó raiz e duas subárvores.
binary_tree *create_binary_tree(
    int item, binary_tree *left, binary_tree *right)
{
    binary_tree *new_binary_tree = (binary_tree *)malloc(sizeof(binary_tree));
    new_binary_tree->item = item;
    new_binary_tree->left = left;
    new_binary_tree->right = right;
    new_binary_tree->height = 0;
    return new_binary_tree;
}

// A função is_empty verifica se uma árvore binária é vazia.
int is_empty(binary_tree *bt)
{
    return (bt == NULL);
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// A função height retorna a altura de um nó da árvore.
int height(binary_tree *bt)
{
    // Se o nó for nulo, a função retorna -1.
    // Caso contrário, a função retorna 1 + o maior valor entre a altura da subárvore esquerda e a altura da subárvore direita.
    if (bt == NULL)
    {
        return -1;
    }
    else
    {
        return 1 + max(height(bt->left), height(bt->right));
    }
}

/* int is_balanced(binary_tree *bt)
{
    int bf = height(bt->left) - height(bt->right);
    return ((-1 <= bf) && (bf <= 1));
} */

// A função balance_factor retorna o fator de balanceamento de um nó da árvore.
int balance_factor(binary_tree *node)
{
    if (node == NULL)
    {
        return 0;
    }

    return height(node->left) - height(node->right);
}

// A função rotate_left realiza uma rotação simples à esquerda em um nó da árvore.
binary_tree *rotate_left(binary_tree *bt)
{
    binary_tree *subtree_root = NULL;
    if (bt != NULL && bt->right != NULL)
    {
        subtree_root = bt->right;
        bt->right = subtree_root->left;
        subtree_root->left = bt;
    }
    subtree_root->height = height(subtree_root);
    bt->height = height(bt);
    return subtree_root;
}

// A função rotate_right realiza uma rotação simples à direita em um nó da árvore.
binary_tree *rotate_right(binary_tree *bt)
{
    binary_tree *subtree_root = NULL;
    if (bt != NULL && bt->left != NULL)
    {
        subtree_root = bt->left;
        bt->left = subtree_root->right;
        subtree_root->right = bt;
    }
    subtree_root->height = height(subtree_root);
    bt->height = height(bt);
    return subtree_root;
}

// A função add_node adiciona um item à árvore binária.
binary_tree *add_node(binary_tree *bt, int item)
{
    if (bt == NULL)
    {
        return create_binary_tree(item, NULL, NULL);
    }
    else if (bt->item > item)
    {
        bt->left = add_node(bt->left, item);
    }
    else
    {
        bt->right = add_node(bt->right, item);
    }
    bt->height = height(bt);
    binary_tree *child;
    if (balance_factor(bt) == 2 || balance_factor(bt) == -2)
    {
        if (balance_factor(bt) == 2)
        {
            child = bt->left;
            if (balance_factor(child) == -1)
            {
                bt->left = rotate_left(child);
            }
            bt = rotate_right(bt);
        }
        else if (balance_factor(bt) == -2)
        {
            child = bt->right;
            if (balance_factor(child) == 1)
            {
                bt->right = rotate_right(child);
            }
            bt = rotate_left(bt);
        }
    }
    return bt;
}

binary_tree *find_min(binary_tree *bt)
{
    while (bt->left != NULL)
    {
        bt = bt->left;
    }
    return bt;
}

binary_tree *remove_node(binary_tree *bt, int item)
{
    if (bt == NULL)
    {
        return NULL;
    }

    if (item < bt->item)
    {
        bt->left = remove_node(bt->left, item);
    }
    else if (item > bt->item)
    {
        bt->right = remove_node(bt->right, item);
    }
    else
    {
        if (bt->left == NULL || bt->right == NULL)
        {
            binary_tree *temp = bt->left ? bt->left : bt->right;

            if (temp == NULL)
            {
                temp = bt;
                bt = NULL;
            }
            else
            {
                *bt = *temp;
            }

            free(temp);
        }
        else
        {
            binary_tree *temp = find_min(bt->right);
            bt->item = temp->item;
            bt->right = remove_node(bt->right, temp->item);
        }
    }

    if (bt == NULL)
    {
        return NULL;
    }

    // Update height and balance factor
    bt->height = 1 + max(height(bt->left), height(bt->right));
    int bf = balance_factor(bt);

    // Perform rotations if necessary
    if (bf == 2)
    {
        if (balance_factor(bt->left) >= 0)
        {
            bt = rotate_right(bt);
        }
        else
        {
            bt->left = rotate_left(bt->left);
            bt = rotate_right(bt);
        }
    }
    else if (bf == -2)
    {
        if (balance_factor(bt->right) <= 0)
        {
            bt = rotate_left(bt);
        }
        else
        {
            bt->right = rotate_right(bt->right);
            bt = rotate_left(bt);
        }
    }

    return bt;
}

void print_pre_order(binary_tree *bt)
{
    if (bt != NULL)
    {
        printf("%d\n", bt->item);
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

int main()
{
    binary_tree *bt = create_empty_binary_tree();
    bt = add_node(bt, 30);
    bt = add_node(bt, 20);
    bt = add_node(bt, 40);
    bt = add_node(bt, 10);
    bt = add_node(bt, 25);
    bt = add_node(bt, 35);
    bt = add_node(bt, 50);

    print_tree(bt, 0, ' ');
    printf("\n");

    bt = remove_node(bt, 20);

    print_tree(bt, 0, ' ');
    printf("\n");

    bt = add_node(bt, 60);

    print_tree(bt, 0, ' ');
    printf("\n");

    bt = add_node(bt, 80);

    print_tree(bt, 0, ' ');
    printf("\n");

    bt = add_node(bt, 90);

    print_tree(bt, 0, ' ');
    printf("\n");

    bt = remove_node(bt, 10);

    print_tree(bt, 0, ' ');
    printf("\n");

    return 0;
}