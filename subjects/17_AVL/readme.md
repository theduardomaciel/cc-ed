# AVL Trees

Algoritmos publicados em 1962 por G. M. Adel’son-Velskii e Y. M. Landis
• Em sua homenagem, os elementos desta estrutura de dados são chamados de árvores AVL
• AVL é uma `árvore de busca binária` com auto-equilíbrio, em que **a diferença máxima na altura das subárvores direita e esquerda de qualquer nó é 1**.

### Procedimentos de Balanceamento

#### Adição

1. Adicionar o novo nó na árvore como em uma árvore de busca binária
2. Percorrer a árvore do nó recém-adicionado até a raiz, atualizando a altura dos nós e verificando se a árvore está balanceada
3. Se a árvore não estiver balanceada, aplicar uma das seguintes rotações:
   - Simples à direita
   - Simples à esquerda
   - Dupla à direita
   - Dupla à esquerda
4. Repetir o procedimento até a raiz

#### Remoção

1. Remover o nó da árvore como em uma árvore de busca binária
2. Após a remoção, percorrer a árvore do nó recém-removido até a raiz, atualizando a altura dos nós e verificando se a árvore está balanceada
3. Se a árvore não estiver balanceada, aplicar uma das seguintes rotações:
   - Simples à direita
   - Simples à esquerda
   - Dupla à direita
   - Dupla à esquerda
4. Repetir o procedimento até a raiz

### Rotações

#### Simples à direita

```
    A
   / \
  B   C
 / \
D   E
```

1. Atribuir a B a subárvore esquerda de A
2. Atribuir a E a subárvore direita de B
3. Atribuir a A a subárvore direita de B

#### Simples à esquerda

```
    A
   / \
  B   C
     / \
    D   E
```

1. Atribuir a C a subárvore direita de A
2. Atribuir a B a subárvore esquerda de C
3. Atribuir a A a subárvore esquerda de C

#### Dupla à direita

```
    A
   / \
  B   C
     / \
    D   E
```

1. Aplicar a rotação simples à esquerda em C
2. Aplicar a rotação simples à direita em A

#### Dupla à esquerda

```
    A
   / \
  B   C
 / \
D   E
```

1. Aplicar a rotação simples à direita em B
2. Aplicar a rotação simples à esquerda em A

### Complexidade

| Operação | Complexidade |
| -------- | ------------ |
| Busca    | O(log n)     |
| Inserção | O(log n)     |
| Remoção  | O(log n)     |

### Implementação

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int balance(Node *node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

Node *newNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node *insert(Node *node, int key) {
    if (node == NULL) {
        return newNode(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int b = balance(node);

    if (b > 1 && key < node->left->key) {
        return rightRotate(node);
    }

    if (b < -1 && key > node->right->key) {
        return leftRotate(node);
    }

    if (b > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (b < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node *minValueNode(Node *node) {
    Node *current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

Node *deleteNode(Node *root, int key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node *temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL) {
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int b = balance(root);

    if (b > 1 && balance(root->left) >= 0) {
        return rightRotate(root);
    }

    if (b > 1 && balance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && balance(root->right) <= 0) {
        return leftRotate(root);
    }

    if (b < -1 && balance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void preOrder(Node *node) {
    if (node != NULL) {
        printf("%d ", node->key);
        preOrder(node->left);
        preOrder(node->right);
    }
}

int main() {
    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Preorder traversal of the constructed AVL tree is\n");
    preOrder(root);

    root = deleteNode(root, 30);

    printf("\nPreorder traversal after deletion of 30\n");
    preOrder(root);

    return 0;
}
```

### Referências

- [Árvore AVL - Wikipedia](https://en.wikipedia.org/wiki/AVL_tree)
- [Inserção - GeeksforGeeks](https://www.geeksforgeeks.org/insertion-in-an-avl-tree/)
- [Remoção - GeeksforGeeks](https://www.geeksforgeeks.org/deletion-in-an-avl-tree/)
