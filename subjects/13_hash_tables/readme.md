# Hash Tables

## Introdução

Hash tables são estruturas de dados que permitem armazenar e recuperar dados de forma eficiente. Elas são uma das estruturas de dados mais importantes e amplamente utilizadas. Hash tables são usadas para implementar mapas, dicionários, conjuntos, bancos de dados, caches, etc.

## Representação

Uma hash table é uma coleção de pares chave-valor. Ela armazena um valor associado a uma chave. A chave é usada para calcular um índice que é usado para acessar o valor associado. A chave é mapeada para um índice usando uma função de hash.

Aqui está um exemplo de uma hash table:

| Índice | Chave | Valor |
| ------ | ----- | ----- |
| 0      | 12    | MAT   |
| 1      | 25    | FIS   |
| 2      | 37    | QUI   |
| 3      | 48    | BIO   |
| 4      | 59    | GEO   |
| 5      | 71    | HIS   |
| 6      | 82    | POR   |

## Função de Hash

Uma função de hash **é uma função que mapeia um conjunto de chaves para um conjunto de inteiros**.

- A função de hash `deve ser determinística`, ou seja, ela deve sempre retornar o mesmo valor para a mesma chave.
- A função de hash `deve ser rápida de calcular`.
- A função de hash ideal distribui as chaves de forma uniforme, ou seja, ela mapeia as chaves para os índices de forma uniforme.

## Colisões

Uma colisão ocorre quando **duas chaves são mapeadas para o mesmo índice**. Existem várias maneiras de lidar com colisões, como encadeamento, endereçamento aberto, rehashing, etc.

## Complexidade

A complexidade de tempo de uma hash table depende da função de hash, da forma como as colisões são tratadas e do fator de carga. Em média, a complexidade de tempo para inserir, remover e buscar um elemento em uma hash table é O(1).

| Operação | Complexidade |
| -------- | ------------ |
| Inserir  | O(1)         |
| Remover  | O(1)         |
| Buscar   | O(1)         |

## Implementação

A implementação de uma hash table pode ser feita usando arrays, listas encadeadas, árvores, etc. A implementação mais comum é usando arrays e listas encadeadas.

## Hash Table com Arrays

Uma hash table com arrays é uma hash table que usa arrays para armazenar os pares chave-valor. Cada índice da hash table é um par chave-valor. A chave é usada para calcular o índice.

Aqui está um exemplo de uma hash table com arrays:

```c
typedef struct HashTable {
    int size;
    int* keys;
    int* values;
} HashTable;

HashTable* createHashTable(int size) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->keys = (int*)malloc(sizeof(int) * size);
    hashTable->values = (int*)malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        hashTable->keys[i] = -1;
    }
    return hashTable;
}

int hash(int key, int size) {
    return key % size;
}

void insert(HashTable* hashTable, int key, int value) {
    int index = hash(key, hashTable->size);
    while (hashTable->keys[index] != -1) {
        index = (index + 1) % hashTable->size;
    }
    hashTable->keys[index] = key;
    hashTable->values[index] = value;
}

int search(HashTable* hashTable, int key) {
    int index = hash(key, hashTable->size);
    while (hashTable->keys[index] != key) {
        index = (index + 1) % hashTable->size;
        if (hashTable->keys[index] == -1) {
            return -1;
        }
    }
    return hashTable->values[index];
}

void remove(HashTable* hashTable, int key) {
    int index = hash(key, hashTable->size);
    while (hashTable->keys[index] != key) {
        index = (index + 1) % hashTable->size;
        if (hashTable->keys[index] == -1) {
            return;
        }
    }
    hashTable->keys[index] = -1;
    hashTable->values[index] = -1;
}
```

## Hash Table com Encadeamento

Uma hash table com encadeamento é uma hash table que usa listas encadeadas para lidar com colisões. Cada índice da hash table é uma lista encadeada. Quando duas chaves são mapeadas para o mesmo índice, elas são armazenadas na mesma lista encadeada.

Aqui está um exemplo de uma hash table com encadeamento:

```c
typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct HashTable {
    int size;
    Node** table;
} HashTable;

HashTable* createHashTable(int size) {
    HashTable* hashTable = (HashTable*)malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->table = (Node**)malloc(sizeof(Node*) * size);
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    return hashTable;
}

int hash(int key, int size) {
    return key % size;
}

void insert(HashTable* hashTable, int key, int value) {
    int index = hash(key, hashTable->size);
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = hashTable->table[index];
    hashTable->table[index] = newNode;
}

int search(HashTable* hashTable, int key) {
    int index = hash(key, hashTable->size);
    Node* current = hashTable->table[index];
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

void remove(HashTable* hashTable, int key) {
    int index = hash(key, hashTable->size);
    Node* current = hashTable->table[index];
    Node* previous = NULL;
    while (current != NULL) {
        if (current->key == key) {
            if (previous == NULL) {
                hashTable->table[index] = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
        previous = current;
        current = current->next;
    }
}
```

## Hash Table com Endereçamento Aberto

Uma hash table com endereçamento aberto é uma hash table que usa sondagem para lidar com colisões. Existem várias técnicas de sondagem, como sondagem linear, sondagem quadrática, sondagem dupla, etc. Quando duas chaves são mapeadas para o mesmo índice, a sondagem é usada para encontrar um novo índice.

## Referências

- [Hash Table - Wikipedia](https://en.wikipedia.org/wiki/Hash_table)
- [O que é hashing? - GeeksforGeeks](https://www.geeksforgeeks.org/what-is-hashing/)
- [Encadeamento - GeeksforGeeks](https://www.geeksforgeeks.org/separate-chaining-collision-handling-technique-in-hashing/)
- [Endereçamento Aberto - GeeksforGeeks](https://www.geeksforgeeks.org/open-addressing-collision-handling-technique-in-hashing/)
