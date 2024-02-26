#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

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

int is_empty(binary_tree *bt)
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

/**
 * Removes a node with the specified item from a binary tree.
 *
 * @param bt The binary tree from which to remove the node.
 * @param item The item to be removed from the binary tree.
 * @return The updated binary tree after removing the node.
 */
binary_tree *remove_node(binary_tree *bt, int item)
{
    if (bt == NULL)
    {
        return NULL;
    }
    else if (bt->item > item)
    {
        // If the item to be removed is in the left subtree
        bt->left = remove_node(bt->left, item);
    }
    else if (bt->item < item)
    {
        // If the item to be removed is in the right subtree
        bt->right = remove_node(bt->right, item);
    }
    else
    {
        if (bt->left == NULL && bt->right == NULL)
        {
            // If the node has no children, free the memory and set it to NULL
            free(bt);
            bt = NULL;
        }
        else if (bt->left == NULL)
        {
            // If the node has only a right child, replace it with the right child
            binary_tree *node = bt;
            bt = bt->right;
            free(node);
        }
        else if (bt->right == NULL)
        {
            // If the node has only a left child, replace it with the left child
            binary_tree *node = bt;
            bt = bt->left;
            free(node);
        }
        else
        {
            // If the node has both left and right children
            // Find the rightmost node in the left subtree
            binary_tree *node = bt->left;
            while (node->right != NULL)
            {
                node = node->right;
            }
            // Swap the item of the rightmost node with the item of the node to be removed
            bt->item = node->item;
            node->item = item;
            // Remove the rightmost node from the left subtree
            bt->left = remove_node(bt->left, item);
        }
    }
    return bt;
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

/**
 * Helper function to check if a binary tree is a binary search tree (BST).
 *
 * @param root The root of the binary tree.
 * @param min The minimum value a node in the tree can have.
 * @param max The maximum value a node in the tree can have.
 * @return true if the tree is a valid BST, false otherwise.
 */
bool isBST(binary_tree *root, int min, int max)
{
    if (root == NULL)
    {
        return true;
    }

    if (root->item < min || root->item > max)
    {
        return false;
    }

    // Recursively check the left and right subtrees
    return isBST(root->left, min, root->item - 1) && isBST(root->right, root->item + 1, max);
}

/**
 * Searches for an item in a binary tree.
 *
 * @param bt The binary tree to search in.
 * @param item The item to search for.
 * @return A pointer to the node containing the item, or NULL if the item is not found.
 */
binary_tree *search(binary_tree *bt, int item)
{
    while (bt != NULL)
    {
        if (bt->item == item)
        {
            return bt;
        }
        else if (bt->item > item)
        {
            bt = bt->left;
        }
        else
        {
            bt = bt->right;
        }

        // Check if the tree is a valid binary search tree
        if (!isBST(bt, INT_MIN, INT_MAX))
        {
            // Return an error code or specific value to indicate invalid BST
            perror("Invalid binary search tree");
            return NULL;
        }
    }

    return NULL;
}

int main()
{
    binary_tree *bt = create_binary_tree(
        6,
        create_binary_tree(4, NULL, NULL),
        create_binary_tree(9,
                           create_binary_tree(1, NULL, NULL),
                           create_binary_tree(2, NULL, NULL)));

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
    if (searched != NULL)
    {
        printf("Searched: %d\n", searched->item);
    }
    else
    {
        printf("Item not found\n");
    }

    binary_tree *binary_search_tree = create_binary_tree(4,
                                                         create_binary_tree(2,
                                                                            create_binary_tree(1, NULL, NULL),
                                                                            create_binary_tree(3, NULL, NULL)),
                                                         create_binary_tree(6,
                                                                            create_binary_tree(9, create_binary_tree(8, NULL, NULL), NULL), NULL));

    searched = search(binary_search_tree, 3);
    if (searched != NULL)
    {
        printf("Searched: %d\n", searched->item);
    }

    binary_tree *not_binary_search_tree = create_binary_tree(4,
                                                             create_binary_tree(6,
                                                                                create_binary_tree(1, NULL, NULL),
                                                                                create_binary_tree(3, NULL, NULL)),
                                                             create_binary_tree(2,
                                                                                create_binary_tree(9, create_binary_tree(8, NULL, NULL), NULL), NULL));

    searched = search(not_binary_search_tree, 3);
    if (searched != NULL)
    {
        printf("Searched: %d\n", searched->item);
    }

    return 0;
}