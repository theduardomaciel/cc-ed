#include <stdio.h>
#include <stdlib.h>

struct element
{
    int key;
    int value;
};

typedef struct element element;

struct hash_table
{
    element *table[11];
};

typedef struct hash_table hash_table;

// Abstract Data Type (ADT)

hash_table *create_hash_table();
void put(hash_table *ht, int key, int value);
int get(hash_table *ht, int key);
void remove_key(hash_table *ht, int key);
int contains_key(hash_table *ht, int key);
void print_hash_table(hash_table *ht);

// Implementation

hash_table *create_hash_table()
{
    hash_table *new_hash_table =
        (hash_table *)malloc(sizeof(hash_table));
    int i;
    for (i = 0; i < 11; i++)
    {
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;
}

void put(hash_table *ht, int key, int value)
{
    int h = key % 11;
    while (ht->table[h] != NULL)
    {
        if (ht->table[h]->key == key)
        {
            ht->table[h]->value = value;
            break;
        }
        h = (h + 1) % 11;
    }
    if (ht->table[h] == NULL)
    {
        element *new_element =
            (element *)malloc(sizeof(element));
        new_element->key = key;
        new_element->value = value;
        ht->table[h] = new_element;
    }
}

int get(hash_table *ht, int key)
{
    int h = key % 11;
    while (ht->table[h] != NULL)
    {
        if (ht->table[h]->key == key)
        {
            return ht->table[h]->value;
        }
        h = (h + 1) % 11;
    }
    return -100;
}

void remove_key(hash_table *ht, int key)
{
    int h = key % 11;
    while (ht->table[h] != NULL)
    {
        if (ht->table[h]->key == key)
        {
            ht->table[h]->key = -1;
            break; // Adicionado para interromper o loop
        }
        h = (h + 1) % 11;
    }
}

int contains_key(hash_table *ht, int key)
{
    int h = key % 11;
    while (ht->table[h] != NULL)
    {
        if (ht->table[h]->key == key)
        {
            return 1;
        }
        h = (h + 1) % 11;
    }
    return 0;
}

void print_hash_table(hash_table *ht)
{
    int i;
    for (i = 0; i < 11; i++)
    {
        if (ht->table[i] == NULL)
        {
            printf("N/A\n");
        }
        else
        {
            printf("%d\n", ht->table[i]->value);
        }
    }
}

int main()
{
    hash_table *ht = create_hash_table();
    put(ht, 3, 1000);
    put(ht, 14, 2000);
    put(ht, 15, 3000);
    put(ht, 92, 4000);

    printf("%d\n", get(ht, 3));
    printf("%d\n", get(ht, 14));

    remove_key(ht, 15);
    printf("%d\n", get(ht, 92));

    return 0;
}