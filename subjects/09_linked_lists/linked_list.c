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
int is_empty(node *head);
void print_linked_list(node *head);

// -----------====================----------------

node *create_linked_list()
{
    return NULL;
}

int is_empty(node *head)
{
    return (head == NULL);
}

node *add(node *head, int item)
{
    node *new_node = (node *)malloc(sizeof(node));
    // malloc() returns a void pointer (void *), which indicates that it is a pointer to a region of unknown data type. Therefore, we must cast it to the correct data type so that we can use it in our program.
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

void print_linked_list_recursively(node *head)
{
    if (!is_empty(head))
    {
        printf("%d\n", head->item);
        print_linked_list(head->next);
    }
}

int main()
{
    node *list = create_linked_list();

    list = add(list, 3);
    list = add(list, 9);
    list = add(list, 27);
    list = add(list, 81);
    list = add(list, 243);

    printf("Complete list: \n");
    print_linked_list(list);

    return 0;
}