#include <stdlib.h>
#include <stdio.h>

struct binary_tree
{
    int item;
    binary_tree *left;
    binary_tree *right;
};

typedef struct binary_tree binary_tree;

// Abstract Data Type (ADT)

binary_tree *create_empty_binary_tree();
binary_tree *create_binary_tree(
    int item, binary_tree *left, binary_tree *right);
binary_tree *search(binary_tree *bt, int item);
int is_empty(binary_tree *bt);
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

// Binary Tree Traversals
// Inspecionando cada nodo, eles podem ser:
// Em ordem (in-order): esquerda, raiz, direita (LVR)
// Pré-ordem (pre-order): raiz, esquerda, direita (VLR)
// Pós-ordem (post-order): esquerda, direita, raiz (LRV)

// In Order
// LVR (Left, Visit, Right)

void print_in_order(binary_tree *bt)
{
    if (!is_empty(bt))
    {
        print_in_order(bt->left);
        printf("%d ", bt->item);
        print_in_order(bt->right);
    }
}

// Pre Order
// VLR (Visit, Left, Right)

void print_pre_order(binary_tree *bt)
{
    if (!is_empty(bt))
    {
        printf("%d ", bt->item);
        print_pre_order(bt->left);
        print_pre_order(bt->right);
    }
}

// Post Order
// LRV (Left, Right, Visit)

void print_post_order(binary_tree *bt)
{
    if (!is_empty(bt))
    {
        print_post_order(bt->left);
        print_post_order(bt->right);
        printf("%d ", bt->item);
    }
}

// Binary Tree Search

binary_tree *recursive_search(binary_tree *bt, int item)
{
    if (bt == NULL || bt->item == item)
    {
        return bt;
    }
    else if (bt->item > item)
    {
        return recursive_search(bt->left, item);
    }
    else
    {
        return recursive_search(bt->right, item);
    }
}

binary_tree *search(binary_tree *bt, int item)
{
    while (bt != NULL && bt->item != item)
    {
        if (bt->item > item)
        {
            bt = bt->left;
        }
        else
        {
            bt = bt->right;
        }
    }

    return bt;
}

int main()
{
    binary_tree *bt = create_binary_tree(
        1,
        create_binary_tree(
            2,
            create_binary_tree(4, create_empty_binary_tree(), create_empty_binary_tree()),
            create_binary_tree(5, create_empty_binary_tree(), create_empty_binary_tree())),
        create_binary_tree(
            3,
            create_binary_tree(6, create_empty_binary_tree(), create_empty_binary_tree()),
            create_empty_binary_tree()));

    printf("In Order: ");
    print_in_order(bt);
    printf("\n");

    printf("Pre Order: ");
    print_pre_order(bt);
    printf("\n");

    printf("Post Order: ");
    print_post_order(bt);
    printf("\n");

    binary_tree *searched = search(bt, 3);
    printf("Searched: %d\n", searched->item);

    return 0;
}