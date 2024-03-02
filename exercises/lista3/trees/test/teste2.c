#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to find the index of the closing parenthesis for a given opening parenthesis
int findIndex(char *str, int si, int ei)
{
    if (si > ei)
    {
        return -1;
    }
    char stack[ei - si + 1];
    int top = -1;
    for (int i = si; i <= ei; i++)
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

// Function to recursively build the tree from the string
struct Node *fromString(char *str, int si, int ei)
{
    if (si > ei)
    {
        return NULL;
    }
    char num[10]; // Assuming the maximum length of a number is 10 digits
    int numIndex = 0;
    while (si < strlen(str) && str[si] >= '0' && str[si] <= '9')
    {
        num[numIndex++] = str[si++];
    }
    num[numIndex] = '\0';
    struct Node *root = (struct Node *)malloc(sizeof(struct Node));
    root->data = atoi(num);
    root->left = NULL;
    root->right = NULL;
    int index = -1;
    if (si <= ei && str[si] == '(')
    {
        index = findIndex(str, si, ei);
    }
    if (index != -1)
    {
        root->left = fromString(str, si + 1, index - 1);
        root->right = fromString(str, index + 2, ei - 1);
    }
    return root;
}

// Function to construct binary tree from string
struct Node *treeFromString(char *s)
{
    return fromString(s, 0, strlen(s) - 1);
}

void print_pre_order(struct Node *bt)
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
    char s[] = "4(2(3)(1))(6(5))";
    struct Node *root = treeFromString(s);

    print_pre_order(root);

    return 0;
}
