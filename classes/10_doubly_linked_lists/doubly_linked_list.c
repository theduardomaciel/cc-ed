#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node
{
    int item;
    node *next;
    node *previous;
};

// Abstract Data Type (ADT)
node *create_doubly_linked_list();
node *add(node *head, int item);
node *search(node *head, int item);
node *remove_item(node *head, int item);
int is_empty(node *head);
void print_doubly_linked_list_forward(node *head);
void print_doubly_linked_list_backward(node *tail);

// -----------====================----------------

node *create_doubly_linked_list()
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
    new_node->item = item;
    new_node->next = head;
    new_node->previous = NULL;

    if (head != NULL)
        head->previous = new_node;

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
    node *current = head;

    while (current != NULL && current->item != item)
        current = current->next;

    if (current == NULL)
        return head;

    if (head == current)
    {
        head = current->next;
    }
    else
    {
        current->previous->next = current->next;
    }

    if (current->next != NULL)
    {
        current->next->previous = current->previous;
    }

    free(current);

    return head;
}

void print_doubly_linked_list_backward(node *tail)
{
    if (tail != NULL)
    {
        printf("%d ", tail->item);
        print_doubly_linked_list_backward(tail->previous);
    }
    printf("\n");
}

void print_doubly_linked_list_forward(node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    node *head = create_doubly_linked_list();
    head = add(head, 10);
    head = add(head, 20);
    head = add(head, 30);
    head = add(head, 40);
    head = add(head, 50);
    head = add(head, 60);
    head = add(head, 70);
    head = add(head, 80);
    head = add(head, 90);
    head = add(head, 100);

    print_doubly_linked_list_forward(head);
    printf("\n");

    head = remove_item(head, 100);
    head = remove_item(head, 90);
    head = remove_item(head, 80);
    head = remove_item(head, 30);
    head = remove_item(head, 20);
    head = remove_item(head, 10);

    printf("Removed 100, 90, 80, 30, 20, 10\n");
    print_doubly_linked_list_forward(head);

    printf("Searching for 100: ");
    printf("Value: %d\n", search(head, 100) ? search(head, 100)->item : -1);

    printf("Searching for 50: ");
    printf("Value: %d\n", search(head, 50) ? search(head, 50)->item : -1);

    return 0;
}