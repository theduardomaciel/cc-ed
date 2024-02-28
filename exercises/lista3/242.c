#include <stdio.h>
#include <stdlib.h>

/*
    -> Descrição:

    As tabelas Hash, também conhecidas como tabelas de dispersão, armazenam elementos com base no valor absoluto de suas chaves e em técnicas de tratamento de colisões.
    Para o cálculo do endereço onde deve ser armazenada uma determinada chave, utiliza-se uma função denominada função de dispersão, que transforma a chave em um dos endereços disponíveis na tabela.

    Suponha que uma aplicação utilize uma tabela de dispersão com 13 endereços-base (índices de 0 a 12) e empregue a função de dispersão h(x) = x mod 13, em que x representa a chave do elemento cujo endereço-base deve ser calculado.

    Se a chave x for igual a 49, a função de dispersão retornará o valor 10, indicando o local onde esta chave deverá ser armazenada.
    Se a mesma aplicação considerar a inserção da chave 88, o cálculo retornará o mesmo valor 10, ocorrendo neste caso uma colisão. O Tratamento de colisões serve para resolver os conflitos nos casos onde mais de uma chave é mapeada para um mesmo endereço-base da tabela. Este tratamento pode considerar, ou o recálculo do endereço da chave ou o encadeamento externo ou exterior.

    O professor gostaria então que você o auxiliasse com um programa que calcula o endereço para inserções de diversas chaves em algumas tabelas, com funções de dispersão e tratamento de colisão por encadeamento exterior.

    -> Formato de entrada

    A entrada contém vários casos de teste. A primeira linha de entrada contém um inteiro N indicando a quantidade de casos de teste.

    Cada caso de teste é composto por duas linhas.
    - A primeira linha contém um valor M (1 ≤ M ≤ 100) que indica a quantidade de endereços-base na tabela (normalmente um número   primo) seguido por um espaço e um valor C (1 ≤ C ≤ 200) que indica a quantidade de chaves a serem armazenadas.
    - A segunda linha contém cada uma das chaves (com valor entre 1 e 200), separadas por um espaço em branco.

    É importante considerar que nessa tabela específica, uma mesma chave poderá ser inserida várias vezes.
    O elemento duplicado deve ser inserido no final da lista.
*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura para armazenar os elementos na tabela
typedef struct node
{
    int key;
    struct node *next;
} node;

// Estrutura para a tabela hash
typedef struct
{
    int size;
    node **table;
} hash_table;

// Função de dispersão
int hash_function(int key, int table_size)
{
    return key % table_size;
}

// Função para inicializar a tabela hash
hash_table create_hash_table(int size)
{
    hash_table ht;
    ht.size = size;
    ht.table = (node **)malloc(size * sizeof(node *));
    for (int i = 0; i < size; i++)
    {
        ht.table[i] = NULL;
    }
    return ht;
}

// Função para inserir um elemento na tabela com tratamento de colisões por *"Encadeamento Exterior"
void put(hash_table *ht, int key)
{
    int index = hash_function(key, ht->size);

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
        // No caso de colisão, encontramos o último nó na lista encadeada e adicionamos o novo nó
        node *current = ht->table[index];
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

// *Encadeamento Exterior é uma técnica de tratamento de colisões em hash tables.
// Em resumo, quando ocorre uma colisão (ou seja, duas chaves são mapeadas para o mesmo índice da tabela), em vez de substituir a chave existente, a técnica lida com isso criando uma lista encadeada na posição correspondente da tabela.

// Para inserir um novo elemento, basta percorrer a lista encadeada até o final e adicionar o novo elemento.
// Já para buscar e para remover um elemento, a função de dispersão é usada para encontrar o índice correspondente. Após isso, basta percorrer a lista encadeada até encontrar o elemento desejado e retorná-lo ou removê-lo.

// Função para imprimir a tabela
void print_table(const hash_table *ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        printf("%d -> ", i);
        node *current = ht->table[i];
        while (current != NULL)
        {
            printf("%d -> ", current->key);
            current = current->next;
        }
        printf("\\\n"); // Precisamos "escapar" a barra invertida para que ela seja impressa
    }
}

// Função para liberar a memória alocada pela tabela hash
void free_table(hash_table *ht)
{
    for (int i = 0; i < ht->size; i++)
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
}

int main()
{
    int num_test_cases;
    scanf("%d", &num_test_cases);

    while (num_test_cases--)
    {
        int table_size, num_keys;
        scanf("%d %d", &table_size, &num_keys);

        // Inicializamos a hash table
        hash_table ht = create_hash_table(table_size);

        // Inserimos as chaves na tabela
        for (int i = 0; i < num_keys; i++)
        {
            int key;
            scanf("%d", &key);
            put(&ht, key);
        }

        // printf("Hash table:\n");
        print_table(&ht);
        printf("\n");

        // Liberamos a memória alocada pela tabela hash
        free_table(&ht);
    }

    return 0;
}
