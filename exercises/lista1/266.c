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
        Escreva uma função que ordena em ordem crescente uma lista encadeada sem criar uma nova lista.

    Formato de Entrada:
        Uma lista encadeada onde cada nó possui um número.

    Formato de Saída:
       Uma lista encadeada onde cada nó possui um número. Os nós devem estar em ordem crescente.

    Exemplo de Entrada:
        80 75 5 10 50 2 3 2 70 52 22 21

    Exemplo de Saída:
        2 2 3 5 10 21 22 50 52 70 75 80
*/

int main()
{
    node *head = create_linked_list();

    int value;
    while (scanf("%d", &value) != EOF)
    {
        head = add(head, value);
    }

    node *current = head;
    node *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        while (next != NULL)
        {
            // Verifica se o item do nó atual é maior que o item do próximo nó
            if (current->item > next->item)
            {
                // Se for, troca os itens dos nós, ou seja, o item seguinte que é menor vai para trás
                int temp = current->item;
                current->item = next->item;
                next->item = temp;
            }
            next = next->next;
        }
        current = current->next;
    }

    print_linked_list(head);

    return 0;
}