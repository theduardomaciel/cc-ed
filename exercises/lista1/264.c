#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node
{
    int item;
    node *next;
};
// ou, retira-se o "typedef" acima" acima, e utiliza-se, na definição do ponteiro "next", struct node *next;

// Abstract Data Type (ADT)

node *create_linked_list();
node *add(node *head, int item);
node *search(node *head, int item);
node *remove_item(node *head, int item);
void print_linked_list(node *head);

// -----------====================----------------

node *create_linked_list()
{
    return NULL;
}

node *add(node *head, int item)
{
    node *new_node = (node *)malloc(sizeof(node));
    // "malloc() returns a void pointer (void *), which indicates that it is a pointer to a region of unknown data type. Therefore, we must cast it to the correct data type so that we can use it in our program"
    new_node->item = item;
    new_node->next = head;
    return new_node;
}

node *search(node *head, int item)
{
    while (head != NULL)
    {
        if (head->item == item)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

node *remove_item(node *head, int item)
{
    node *previous = NULL;
    node *current = head;
    while (current != NULL && current->item != item)
    {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        return head;
    }
    if (previous == NULL)
    {
        head = current->next;
    }
    else
    {
        previous->next = current->next;
    }
    free(current);
    return head;
}

void print_linked_list(node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}

/*
    Descrição:
        Escreva uma função para inverter uma lista encadeada usando somente uma "passada" pela lista.

    Formato de Entrada:
        Uma lista encadeada.
        Cada nó da lista deve possuir um número.

    Formato de Saída:
       A mesma lista, mas em ordem inversa.

    Exemplo de Entrada:
        2 35 44 6 13 83 2 90 30

    Exemplo de Saída:
        30 90 2 83 13 6 44 35 2
*/

int main()
{
    node *head = create_linked_list();

    /* int item;
    scanf("%d", &item);
    head = add(head, item);

    while (getchar() != '\n')
    {
        int item;
        scanf("%d", &item);
        head = add(head, item);
    } */

    int value;

    // Ler valores até encontrar o fim de linha (FUNCIONA NO HUXLEY E NÃO FUNCIONA NO COMPILADOR LOCAL)
    while (scanf("%d", &value) != EOF)
    {
        head = add(head, value);
    }

    print_linked_list(head);

    return 0;
}