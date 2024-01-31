#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node
{
    void *item;
    node *next;
};

// Abstract Data Type (ADT)

node *create_linked_list();
node *add(node *head, void *item);
node *search(node *head, void *item, int (*equal)(void *item1, void *item2));
node *remove_item(node *head, void *item);
int is_empty(node *head);

// -----------====================----------------

node *create_linked_list()
{
    return NULL;
}

int is_empty(node *head)
{
    return (head == NULL);
}

node *add(node *head, void *item)
{
    node *new_node = (node *)malloc(sizeof(node));
    // malloc() returns a void pointer (void *), which indicates that it is a pointer to a region of unknown data type. Therefore, we must cast it to the correct data type so that we can use it in our program.
    new_node->item = item;
    new_node->next = head;
    return new_node;
}

node *search(node *head, void *item, int (*equal)(void *item1, void *item2))
{
    {
        while (head != NULL)
        {
            if ((*equal)(head->item, item))
            {
                return head;
            }
            head = head->next;
        }
        return NULL;
    }
}

node *remove_item(node *head, void *item)
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

// ------------------------------------------------

void print_linked_list_of_integers(node *head)
{
    while (head != NULL)
    {
        printf("%d\n", *((int *)head->item));
        head = head->next;
    }
}

void print_linked_list_of_strings(node *head)
{
    while (head != NULL)
    {
        printf("%s\n", (char *)head->item);
        head = head->next;
    }
}

// ------------------------------------------------

int main()
{
    node *list = create_linked_list();

    list = add(list, (void *)10);

    int b = 20;
    list = add(list, &b);

    int c = 30;
    list = add(list, &c);

    printf("Complete list: \n");
    print_linked_list_of_integers(list);

    return 0;
}