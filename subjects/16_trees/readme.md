# Árvores

## Introdução

Árvores são estruturas de dados que possuem uma raiz e nós. Cada nó pode ter zero ou mais nós filhos. A raiz é o nó que não possui um nó pai. Cada nó filho pode ter zero ou mais nós filhos, e assim por diante.

## Estrutura de Dados

```c
typedef struct s_node
{
    int value;
    struct s_node *left;
    struct s_node *right;
} Node;
```

## Definições

Seja T uma árvore, e n e m sejam nós de T...

1. n e m são `irmãos` se tiverem o mesmo pai.
2. Um nó é uma `folha` de T se não tiver filhos.
3. Um nó é um `nó interno` se não for uma folha.
4. Uma `aresta` de T conecta dois nós (pai e filho).
5. Um `caminho` em T é uma coleção de arestas que unem dois nós; o `comprimento` de um caminho consiste no número de arestas no caminho.
6. A `altura` de um nó é o comprimento do caminho `mais longo` do nó até uma folha.
7. A `profundidade` de um nó é o comprimento do caminho desse nó até a raiz.
8. A `altura de uma árvore` T é a altura da raiz, ou seja, o comprimento do caminho mais longo da raiz até uma folha.
9. Uma `subárvore` S, de T enraizada em n, é uma árvore feita a partir de T considerando n como a raiz de S e incluindo todos os descendentes de n.

## Tipos de Árvores

### Árvore Binária

Uma árvore binária é uma árvore em que cada nó tem no máximo dois filhos. Possui as seguintes propriedades:

1. Cada nó tem no máximo dois filhos.
2. Cada nó tem um pai, exceto a raiz.
3. Cada nó tem um valor.

Além disso, pode ser caracterizada como:

1. Árvore binária cheia (ou estrita): cada nó tem zero ou dois filhos.
2. Árvore binária completa: todas as folhas estão no mesmo nível.
3. Árvore binária perfeita: todas as folhas estão no mesmo nível e todos os nós têm dois filhos.

### Árvore de Busca Binária

Uma árvore binária de busca é uma árvore binária em que, para cada nó, todos os nós na subárvore esquerda têm valores menores que o valor do nó, e todos os nós na subárvore direita têm valores maiores que o valor do nó.

### Árvore AVL

Uma árvore AVL é uma árvore binária de busca balanceada. Para cada nó, as alturas das subárvores esquerda e direita diferem em no máximo 1.

### Árvore Rubro-Negra

Uma árvore rubro-negra é uma árvore binária de busca balanceada. Cada nó é colorido de preto ou vermelho, e as seguintes propriedades são mantidas:

1. A raiz é preta.
2. As folhas são pretas.
3. Se um nó é vermelho, então ambos os filhos são pretos.
4. Para cada nó, todos os caminhos da raiz até as folhas têm o mesmo número de nós pretos.

## Operações

### Inserção

Para inserir um valor `v` em uma árvore binária de busca `T`, fazemos o seguinte:

1. Se `T` é vazio, criamos um novo nó com valor `v` e o retornamos.
2. Se `v` é menor que o valor da raiz de `T`, inserimos `v` na subárvore esquerda de `T`.
3. Se `v` é maior que o valor da raiz de `T`, inserimos `v` na subárvore direita de `T`.

### Busca

Para buscar um valor `v` em uma árvore binária de busca `T`, fazemos o seguinte:

1. Se `T` é vazio, retornamos falso.
2. Se `v` é igual ao valor da raiz de `T`, retornamos verdadeiro.
3. Se `v` é menor que o valor da raiz de `T`, buscamos `v` na subárvore esquerda de `T`.

### Remoção

Para remover um valor `v` de uma árvore binária de busca `T`, fazemos o seguinte:

1. Se `T` é vazio, retornamos `T`.
2. Se `v` é menor que o valor da raiz de `T`, removemos `v` da subárvore esquerda de `T`.
3. Se `v` é maior que o valor da raiz de `T`, removemos `v` da subárvore direita de `T`.

### Implementações em C

Árvores podem ser implementadas de diversas formas. Abaixo, temos exemplos de implementações de árvores binárias e árvores de busca binárias.

### Árvore Binária

```c
Node *create_node(int value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(Node **root, int value)
{
    if (*root == NULL)
    {
        *root = create_node(value);
    }
    else if (value < (*root)->value)
    {
        insert(&(*root)->left, value);
    }
    else
    {
        insert(&(*root)->right, value);
    }
}

Node *search(Node *root, int value)
{
    if (root == NULL || root->value == value)
    {
        return root;
    }
    if (value < root->value)
    {
        return search(root->left, value);
    }
    return search(root->right, value);
}

Node *remove_node(Node *root, int value)
{
    if (root == NULL)
    {
        return root;
    }
    if (value < root->value)
    {
        root->left = remove_node(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = remove_node(root->right, value);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = min_value_node(root->right);
        root->value = temp->value;
        root->right = remove_node(root->right, temp->value);
    }
    return root;
}
```

### Árvore de Busca Binária

```c
Node *min_value_node(Node *node)
{
    Node *current = node;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

Node *max_value_node(Node *node)
{
    Node *current = node;
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

Node *successor(Node *node)
{
    if (node->right != NULL)
    {
        return min_value_node(node->right);
    }
    Node *parent = node->parent;
    while (parent != NULL && node == parent->right)
    {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

Node *predecessor(Node *node)
{
    if (node->left != NULL)
    {
        return max_value_node(node->left);
    }
    Node *parent = node->parent;
    while (parent != NULL && node == parent->left)
    {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

Node *create_node(int value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(Node **root, int value)
{
    if (*root == NULL)
    {
        *root = create_node(value);
    }
    else if (value < (*root)->value)
    {
        insert(&(*root)->left, value);
    }
    else
    {
        insert(&(*root)->right, value);
    }
}

Node *search(Node *root, int value)
{
    if (root == NULL || root->value == value)
    {
        return root;
    }
    if (value < root->value)
    {
        return search(root->left, value);
    }
    return search(root->right, value);
}

Node *remove_node(Node *root, int value)
{
    if (root == NULL)
    {
        return root;
    }
    if (value < root->value)
    {
        root->left = remove_node(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = remove_node(root->right, value);
    }
    else
    {
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }
        Node *temp = min_value_node(root->right);
        root->value = temp->value;
        root->right = remove_node(root->right, temp->value);
    }
    return root;
}

```

## Travessias (traversals)

Uma árvore pode ser percorrida de diversas formas. As principais formas de percorrer uma árvore são:

### Em-ordem (in-order)

1. Percorre a subárvore esquerda.
2. Visita a raiz.
3. Percorre a subárvore direita.

> Usando a analogia do lápis no papel, deve-se sempre percorrer os nós por baixo.

### Pré-ordem (pre-order)

1. Visita a raiz.
2. Percorre a subárvore esquerda.
3. Percorre a subárvore direita.

> Usando a analogia do lápis no papel, deve-se sempre percorrer os nós pela esquerda.

### Pós-ordem (post-order)

1. Percorre a subárvore esquerda.
2. Percorre a subárvore direita.
3. Visita a raiz.

> Usando a analogia do lápis no papel, deve-se sempre percorrer os nós pela direita.

#### Exemplos

Dada a árvore abaixo:

```
    1
   / \
  2   3
 / \
4   5
```

A travessia em-ordem resulta em `4 2 5 1 3`.

A travessia pré-ordem resulta em `1 2 4 5 3`.

A travessia pós-ordem resulta em `4 5 2 3 1`.

#### Implementações em C

```c
void in_order_traversal(Node *root)
{
    if (root != NULL)
    {
        in_order_traversal(root->left);
        printf("%d ", root->value);
        in_order_traversal(root->right);
    }
}

void pre_order_traversal(Node *root)
{
    if (root != NULL)
    {
        printf("%d ", root->value);
        pre_order_traversal(root->left);
        pre_order_traversal(root->right);
    }
}

void post_order_traversal(Node *root)
{
    if (root != NULL)
    {
        post_order_traversal(root->left);
        post_order_traversal(root->right);
        printf("%d ", root->value);
    }
}
```

## Referências

- [Árvores - Wikipedia](<https://en.wikipedia.org/wiki/Tree_(data_structure)>)
- [Árvore Binária - GeeksforGeeks](https://www.geeksforgeeks.org/binary-tree-data-structure/)
- [Árvore de Busca Binária - GeeksforGeeks](https://www.geeksforgeeks.org/binary-search-tree-data-structure/)
- [Árvore Rubro-Negra - GeeksforGeeks](https://www.geeksforgeeks.org/red-black-tree-set-1-introduction-2/)
