#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
-> Descrição
    Implemente uma tabela hash utilizando a técnica do encadeamento para tratar colisões. Assim, cada posição da tabela T deve armazenar uma lista encadeada, que armazena os elementos inseridos (k) na referida posição ( T[h(k)] ), [[[[organizados de modo crescente]]]].

    A função hash a ser utilizada deve ser o método da divisão (h(k) = k % m).

    O seu programa deve contemplar as seguintes operações:

    1)inserir (elemento deve ser inserido em ordem crescente na lista da posição T[h(k)]). Inserções duplicadas são válidas;

    2)remover;

    3)imprimir, em que as listas encadeadas de cada posição da tabela devem ser impressas em ordem crescente, de T[0] à T[m-1];

    4)procurar, que deve procurar um elemento na tabela e informar: (i) o número de elementos presentes na tabela, (ii) se o elemento em questão foi encontrado ou não, e (iii) quantos elementos da tabela foram acessados (inclusive ele próprio) até que o elemento fosse encontrado. Esses dados servem para refletir, por meio da comparação entre o número de elementos presentes na tabela e o número de elementos acessados, a eficiência da tabela hash para buscar elementos.
*/

/*
-> Formato de Entrada:
    Primeira linha da entrada: valor de 'm'
    a k: inserção do elemento "k"
    r k: remoção do elemento "k"
    i: imprimir tabela hash
    f: finalizar programa
*/

/*
-> Formato de Saída:
    [] Impressão do resultado da busca:
        BUSCA POR ?
        número de elementos da tabela hash: ?
        elemento ? encontrado!
        número de elementos acessados na tabela hash: ?

    [] Impressão da tabela hash: (exemplo com m = 29)
        [0]:Lista vazia!
        [1]:1=>30=>59=>
        [2]:2=>2=>31=>31=>
        [3]:3=>32=>61=>
        [4]:4=>4=>4=>4=>33=>
        [5]:5=>5=>
        [6]:35=>
        [7]:36=>
        [8]:8=>8=>66=>
        [9]:9=>67=>67=>
        ...
*/

typedef struct node
{
    int key;
    struct node *next;
} node;

// Estrutura para a tabela hash
typedef struct
{
    int size;
    int capacity; // talvez "m" seja um nome melhor
    node **table;
} hash_table;

// Função de dispersão (heurística da divisão)
int hash_function(int key, int capacity)
{
    return key % capacity;
}

// Inicializa a Hash Table
hash_table *create_hash_table(int capacity)
{
    hash_table *ht = (hash_table *)malloc(sizeof(hash_table));
    ht->capacity = capacity;
    ht->size = 0;
    ht->table = (node **)malloc(capacity * sizeof(node *));

    for (int i = 0; i < capacity; i++)
    {
        ht->table[i] = NULL;
    }

    return ht;
}

// Insere um elemento na Hash Table (em ordem crescente)
void inserir(hash_table *ht, int key)
{
    int index = hash_function(key, ht->capacity);

    // Criação do novo nó
    node *new_node = (node *)malloc(sizeof(node));
    new_node->key = key;
    new_node->next = NULL;

    // Se não houver colisão, inserimos diretamente
    if (ht->table[index] == NULL)
    {
        ht->table[index] = new_node;
    }
    else
    {
        // Caso contrário, encontramos a posição correta para inserir o novo nó em ordem crescente
        node *current = ht->table[index];
        node *previous = NULL;

        // Percorremos a lista até encontrar a posição correta
        while (current != NULL && current->key < key)
        {
            previous = current;
            current = current->next;
        }

        // Inserimos o novo nó na posição correta
        if (previous == NULL)
        {
            new_node->next = ht->table[index];
            ht->table[index] = new_node;
        }
        else
        {
            previous->next = new_node;
            new_node->next = current;
        }
    }

    ht->size++;
}

// Remove um elemento da Hash Table
void remover(hash_table *ht, int key)
{
    int index = hash_function(key, ht->capacity); // Calculamos o índice correspondente da chave fornecida
    node *current = ht->table[index];             // Inicializamos a lista correspondente a esse índice
    node *previous = NULL;                        // Inicializamos um ponteiro para o nó anterior

    // Percorremos a lista e verificamos se o elemento está presente
    while (current != NULL)
    {
        if (current->key == key) // Se o elemento estiver presente, removemos
        {
            if (previous == NULL)
            {
                // Se o elemento a ser removido for o primeiro da lista,
                // precisamos setar o ponteiro da tabela do elemento que vamos remover para o elemento seguinte
                ht->table[index] = current->next;
            }
            else
            {
                // Caso contrário, simplesmente atualizamos o ponteiro do nó anterior
                previous->next = current->next;
            }

            free(current);

            ht->size--;
            return; // Elemento removido com sucesso
        }

        previous = current;
        current = current->next;
    }
}

// Retorna o número de elementos presentes na tabela, se o elemento foi encontrado e o número de elementos acessados
int procurar(hash_table *ht, int key, int *comparisons)
{
    int index = hash_function(key, ht->capacity); // Calculamos o índice correspondente da chave fornecida
    node *current = ht->table[index];

    int count = 0;

    while (current != NULL)
    {
        // printf("current->key: %d\n", current->key);
        count++;

        if (current->key == key)
        {
            *comparisons = count;
            return 1;
        }

        current = current->next;
    }

    *comparisons = count;
    return 0;
}

void imprimir(hash_table *ht)
{
    printf("imprimindo tabela hash:\n");

    for (int i = 0; i < ht->capacity; i++)
    {
        printf("[%d]:", i);

        node *current = ht->table[i];

        if (current == NULL)
        {
            printf("Lista vazia!\n");
        }
        else
        {
            while (current != NULL)
            {
                printf("%d=>", current->key);
                current = current->next;
            }
            printf("\n");
        }
    }
}

// Libera a memória alocada para uma Hash Table
// (mesmo não sendo necessário pra questão, é bom pra deixar guardado)
void free_table(hash_table *ht)
{
    for (int i = 0; i < ht->capacity; i++)
    {
        node *current = ht->table[i];

        while (current != NULL)
        {
            node *next = current->next;
            free(current);
            current = next;
        }
    }

    free(ht->table);
    free(ht);
}

int main()
{
    int m;
    scanf("%d", &m);

    hash_table *ht = create_hash_table(m);

    int k;
    int comparisons;

    char op;
    scanf(" %c", &op);

    while (op != 'f')
    {
        // printf("op: %c\n", op);

        if (op != 'i')
        {
            getchar();
            scanf("%d", &k);
        }

        switch (op)
        {
        case 'a':
            // printf("k: %d\n", k);
            inserir(ht, k);
            break;

        case 'r':
            remover(ht, k);
            break;

        case 'i':
            imprimir(ht);
            break;

        case 'p':
            printf("BUSCA POR %d\n", k);
            int found = procurar(ht, k, &comparisons);

            printf("numero de elementos da tabela hash: %d\n", ht->size);

            if (found)
            {
                printf("elemento %d encontrado!\n", k);
            }
            else
            {
                printf("elemento nao encontrado!\n");
            }

            printf("numero de elementos acessados na tabela hash: %d\n", comparisons);
            break;

        case 'f':
            break;
        }

        scanf(" %c", &op);
    }

    return 0;
}