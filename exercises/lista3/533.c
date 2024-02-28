#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
    -> Descrição:

    O objetivo deste exercício é implementar o TAD ("Tipo Abstrato de Dados") de uma Hash Table aberta usando listas encadeadas. Esse conjunto deve suportar as seguintes operações:

    1. ADD(S, k) = adiciona o elemento k ao conjunto S, retornando True se o elemento foi corretamente adicionado ou false se o elemento já pertencia ao conjunto.
    2. DEL(S, k) = remove o elemento k do conjunto S, retornando True se o elemento foi corretamente removido ou False se o elemento não pertencia ao conjunto.
    3. HAS(S, k) = retorna True se o elemento k pertence ao conjunto S ou false se o elemento não pertence ao conjunto.

    Os detalhes de implementação da Hash Table T são os seguintes:

    1. Tamanho da tabela: a tabela deve ter uma capacidade inicial m = 7.

    2. Função de dispersão: deve ser usada a heurística da divisão, i.e. h(k) = k mod m

    3. Inserção: os registros devem ser armazenadas em uma lista na posição correspondente.
    As inserções devem ser sempre realizadas no início da lista.

    4. Fator de carga: O fator de carga a = n / m deve ser mantido em a < 0.75.
    (n = número de elementos na tabela, m = capacidade da tabela)
    ps: a questão podia ser mais clara em determinar quem era n e quem era m, mas enfim, fé 🙏

    Assim que a >= 0.75, todos os elementos da tabela atual devem ser redistribuídos (rehashing) numa nova tabela de tamanho
    2 * m - 1 por ordem de posição na tabela corrente, ou seja, todos os elementos da lista em T[0] são realocados, do primeiro ao último elemento dessa lista, depois os da lista em T[1], na mesma ordem, e assim por diante até a lista T[m - 1].
    IMPORTANTE: essa verificação deve ser feita imediatamente *após* a inserção de cada novo elemento na tabela.
*/

/*
    -> Formato de entrada

    O arquivo de entrada consiste em uma sequência de w operações (conceitualmente numeradas de 0 a w-1), sendo uma por linha. As operações possíveis são as seguintes:

    ADD k = adiciona o elemento k
    DEL k = remove o elemento k
    HAS k = indica se o elemento k pertence ao conjunto
    PRT   = imprime alguns dados sobre a tabela

    Limites:
    1 <= w <= 100000
    0 <= k < 2^
*/

/*
    -> Formato de saída

    Para cada operação (numerada i=0,...,w-1) no arquivo de entrada, deve ser impresso o resultado correspondente sobre o conjunto, conforme descrito a seguir.

    a) ADD k: imprime a linha

    i r c

    onde
    i = número da operação
    r = resultado da operação (1=True, 0=False)
    c = número de comparações feitas (posições da lista visitadas) até a inserção (ou não) do valor correspondente, antes de um eventual rehashing


    b) DEL k: imprime a linha

    i r c

    onde
    i = número da operação
    r = resultado da operação (1=True, 0=False)
    c = número de comparações feitas (posições da lista visitadas) até a remoção (ou não) do valor correspondente


    c) HAS k: imprime a linha

    i r c

    onde
    i = número da operação
    r = resultado da operação (1=True, 0=False)
    c = número de comparações feitas (posições da lista visitadas) até a localização (ou não) do valor correspondente

    d) PRT: imprime a linha

    i m n l

    onde
    i = número da operação
    m = tamanho (capacidade da tabela)
    n = número de elementos da tabela (cardinalidade do conjunto)
    l = comprimento da maior lista da tabela (posição com mais elementos)
*/

typedef struct node
{
    int key;
    struct node *next;
} node;

typedef struct
{
    node **table;
    int capacity;
    int size;
} hash_table;

// Função de dispersão (heurística da divisão)
int hash_function(int key, int capacity)
{
    return key % capacity;
}

// Inicializa a Hash Table com capacidade inicial m = 7
hash_table *create_hash_table()
{
    hash_table *ht = (hash_table *)malloc(sizeof(hash_table));
    ht->capacity = 7;
    ht->size = 0;
    ht->table = (node **)malloc(ht->capacity * sizeof(node *));

    for (int i = 0; i < ht->capacity; i++)
    {
        ht->table[i] = NULL;
    }

    return ht;
}

// Insere um elemento na Hash Table
int ADD(hash_table *ht, int key, int *comparisons)
{
    int index = hash_function(key, ht->capacity);
    node *current = ht->table[index];

    *comparisons = 0;

    // Verificamos se o elemento já existe na lista
    while (current != NULL)
    {
        (*comparisons)++;

        if (current->key == key)
        {
            return 0; // Elemento já existe na lista, retornamos a operação sem sucesso
        }

        current = current->next;
    }

    // Elemento não existe na lista, podemos adicionar ao início
    node *newNode = (node *)malloc(sizeof(node));
    newNode->key = key;
    newNode->next = ht->table[index];

    ht->table[index] = newNode;
    ht->size++;

    return 1; // Elemento adicionado com sucesso
}

// Remove um elemento da Hash Table
int DEL(hash_table *ht, int key, int *comparisons)
{
    int index = hash_function(key, ht->capacity); // Calculamos o índice correspondente da chave fornecida
    node *current = ht->table[index];             // Inicializamos a lista correspondente a esse índice
    node *prev = NULL;                            // Inicializamos um ponteiro para o nó anterior

    *comparisons = 0;

    // Percorremos a lista e verificamos se o elemento está presente
    while (current != NULL)
    {
        (*comparisons)++;

        if (current->key == key) // Se o elemento estiver presente, removemos
        {
            if (prev == NULL)
            {
                // Se o elemento a ser removido for o primeiro da lista,
                // precisamos setar o ponteiro da tabela do elemento que vamos remover para o elemento seguinte
                ht->table[index] = current->next;
            }
            else
            {
                // Caso contrário, simplesmente atualizamos o ponteiro do nó anterior
                prev->next = current->next;
            }

            free(current);
            ht->size--;
            return 1; // Elemento removido com sucesso
        }

        prev = current;
        current = current->next;
    }

    return 0; // Elemento não encontrado
}

// Verifica se um elemento pertence à Hash Table
int HAS(hash_table *ht, int key, int *comparisons)
{
    int index = hash_function(key, ht->capacity); // Calculamos o índice correspondente da chave fornecida
    node *current = ht->table[index];             // Inicializamos a lista correspondente a esse índice

    *comparisons = 0;

    // Percorremos a lista e verificamos se o elemento está presente
    while (current != NULL)
    {
        (*comparisons)++;

        if (current->key == key)
        {
            return 1; // Elemento encontrado
        }

        current = current->next;
    }

    return 0; // Elemento não encontrado
}

// Retorna o comprimento da maior lista na Hash Table
int get_max_length(hash_table *ht)
{
    int max = 0;

    // Em resumo, percorremos a tabela e contamos o comprimento de cada lista
    // Se encontrarmos uma lista maior que a atual, atualizamos o valor de max
    for (int i = 0; i < ht->capacity; i++)
    {
        int actualListLength = 0;
        node *current = ht->table[i];

        while (current != NULL)
        {
            actualListLength++;
            current = current->next;
        }

        if (actualListLength > max)
        {
            max = actualListLength;
        }
    }

    return max;
}

// Redimensiona a Hash Table (rehashing) quando a carga é maior ou igual a 0.75
void resize(hash_table *ht)
{
    int newCapacity = 2 * ht->capacity - 1;
    node **newTable = (node **)malloc(newCapacity * sizeof(node *));

    // Primeiramente, inicializamos a nova tabela com todos os elementos iguais a NULL
    for (int i = 0; i < newCapacity; i++)
    {
        newTable[i] = NULL;
    }

    // Em seguida, percorremos a tabela atual e realocamos todos os elementos na nova tabela
    for (int i = 0; i < ht->capacity; i++)
    {
        node *current = ht->table[i];

        while (current != NULL)
        {
            node *next = current->next;
            int newIndex = hash_function(current->key, newCapacity); // Calculamos o novo índice

            current->next = newTable[newIndex]; // Adicionamos o elemento no início da lista
            newTable[newIndex] = current;       // Atualizamos a referência para o novo elemento
            current = next;                     // Avançamos para o próximo elemento
        }
    }

    free(ht->table); // Liberamos a memória alocada para a tabela antiga
    ht->table = newTable;
    ht->capacity = newCapacity;
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
    hash_table *ht = create_hash_table();

    int operationNumber = 0;

    char operation[4];
    int key, result, comparisons;

    while (scanf("%s", operation) > 0)
    {
        // Se a operação for "PRT", imprimimos os dados sobre a tabela e pula para a próxima iteração
        if (operation[0] == 'P')
        {
            printf("%d %d %d %d\n", operationNumber, ht->capacity, ht->size, get_max_length(ht));
            operationNumber++;
            continue;
        }
        else
        {
            // Caso contrário, lemos a chave atual e realizamos a operação correspondente
            scanf("%d", &key);

            switch (operation[0])
            {
            case 'A':
                result = ADD(ht, key, &comparisons);

                // Ao adicionar um novo elemento, precisamos verificar se é necessário redimensionar a tabela (fazer o rehashing)
                // Para isso, verificamos se o fator de carga a = n / m é maior ou igual a 0.75
                // n = número de elementos na tabela
                // m = capacidade da tabela
                if ((float)ht->size / ht->capacity >= 0.75)
                {
                    // printf("Rehashing on index %d\n", operationNumber);
                    resize(ht);
                }
                break;
            case 'D':
                result = DEL(ht, key, &comparisons);
                break;
            case 'H':
                result = HAS(ht, key, &comparisons);
                break;
            default:
                break;
            }

            printf("%d %d %d\n", operationNumber, result, comparisons);
            operationNumber++;
        }
    }

    free_table(ht);

    return 0;
}