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
    element **table;
    int size;
};

typedef struct hash_table hash_table;

// Abstract Data Type (ADT)

hash_table *create_hash_table();
void put(hash_table *ht, int key, int value);
int get(hash_table *ht, int key);
void remove_key(hash_table *ht, int key);
int contains_key(hash_table *ht, int key);
void print_hash_table(hash_table *ht);
void destroy_hash_table(hash_table *ht);

// Implementation

hash_table *create_hash_table()
{
    hash_table *new_hash_table = (hash_table *)malloc(sizeof(hash_table));
    new_hash_table->size = 11; // Initial size, you can adjust as needed
    new_hash_table->table = (element **)malloc(new_hash_table->size * sizeof(element *));

    for (int i = 0; i < new_hash_table->size; i++)
    {
        new_hash_table->table[i] = NULL;
    }
    return new_hash_table;
}

void print_hash_table(hash_table *ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        if (ht->table[i] != NULL)
        {
            printf("(%d, %d) ", ht->table[i]->key, ht->table[i]->value);
        }
        else
        {
            printf("NULL ");
        }
    }
    printf("\n");
}

// Function to check if the table needs to be resized
int should_resize(hash_table *ht)
{
    int count = 0;
    for (int i = 0; i < ht->size; i++)
    {
        if (ht->table[i] != NULL)
        {
            count++;
        }
    }

    // Resize if more than half of the slots are occupied
    return count > ht->size / 2;
}

void resize_hash_table(hash_table *ht)
{
    int new_size = ht->size * 2; // Dobrar o tamanho da tabela hash

    element **new_table = (element **)malloc(new_size * sizeof(element *));
    for (int i = 0; i < new_size; i++)
    {
        new_table[i] = NULL;
    }

    // Rehashing dos elementos existentes
    for (int i = 0; i < ht->size; i++)
    {
        if (ht->table[i] != NULL)
        {
            int h = ht->table[i]->key % new_size;
            while (new_table[h] != NULL)
            {
                h = (h + 1) % new_size;
            }
            new_table[h] = ht->table[i];
        }
    }

    free(ht->table);
    ht->table = new_table;
    ht->size = new_size;
}

void put(hash_table *ht, int key, int value)
{
    int h = key % ht->size;
    int initial_h = h;

    do
    {
        if (ht->table[h] == NULL || ht->table[h]->key == key)
        {
            // If the slot is empty or contains the same key, update the value
            if (ht->table[h] == NULL)
            {
                element *new_element = (element *)malloc(sizeof(element));
                new_element->key = key;
                new_element->value = value;
                ht->table[h] = new_element;
            }
            else
            {
                ht->table[h]->value = value;
            }

            // Check if the table is more than half full and resize if needed
            if (should_resize(ht))
            {
                resize_hash_table(ht);
            }

            return;
        }

        h = (h + 1) % ht->size;

    } while (h != initial_h);
}

int get(hash_table *ht, int key)
{
    int h = key % ht->size;
    while (ht->table[h] != NULL)
    {
        if (ht->table[h]->key == key)
        {
            return ht->table[h]->value;
        }
        h = (h + 1) % ht->size;
    }
    return -1;
}

void remove_key(hash_table *ht, int key)
{
    int h = key % ht->size;
    while (ht->table[h] != NULL && ht)
    {
        if (ht->table[h]->key == key)
        {
            ht->table[h]->key = -1;
            ht->table[h]->value = -1;
        }
        h = (h + 1) % ht->size;
    }
}

int contains_key(hash_table *ht, int key)
{
    int h = key % ht->size;
    while (ht->table[h] != NULL)
    {
        if (ht->table[h]->key == key)
        {
            return 1;
        }
        h = (h + 1) % ht->size;
    }
    return 0;
}

void destroy_hash_table(hash_table *ht)
{
    for (int i = 0; i < ht->size; i++)
    {
        if (ht->table[i] != NULL)
        {
            free(ht->table[i]);
        }
    }
    free(ht->table);
    free(ht);
}

int main()
{
    hash_table *ht = create_hash_table();
    put(ht, 3, 1000);
    print_hash_table(ht);

    put(ht, 14, 2000);
    print_hash_table(ht);

    put(ht, 15, 3000);
    print_hash_table(ht);

    put(ht, 92, 4000);
    print_hash_table(ht);

    printf("3 -> %d\n", get(ht, 3));
    printf("14 -> %d\n", get(ht, 14));

    remove_key(ht, 15);
    print_hash_table(ht);

    printf("%d\n", get(ht, 92));

    destroy_hash_table(ht);

    return 0;
}
