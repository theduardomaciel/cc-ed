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
        Dada duas listas encadeadas A e B, escreva uma função para verificar se B é um subconjunto de A.

    Formato de Entrada:
        A primeira linha de entrada será o tamanho da primeira lista (número inteiro).
        Em seguida, uma lista com "n" números inteiros.
        A terceira linha de entrada é o tamanho da segunda lista (número inteiro).
        Por fim, uma lista com "m" números inteiros.
        Nesse caso, m e n podem assumir valores iguais ou diferentes.

    Formato de Saída:
        0 caso não seja subconjunto; 1 caso seja.

    Exemplo de Entrada:
        7
        1 2 3 4 5 6 7
        5
        5 4 3 1 7

    Exemplo de Saída:
        1
*/

int main()
{
    node *A = create_linked_list();
    node *B = create_linked_list();

    int A_SIZE, B_SIZE;
    scanf("%d", &A_SIZE); // linha 1

    // Iteramos pelos elementos da lista A, adicionando-os à lista encadeada
    for (int i = 0; i < A_SIZE; i++)
    {
        int item;
        scanf("%d", &item); // linha 2
        A = add(A, item);
    }

    scanf("%d", &B_SIZE); // linha 3

    // Iteramos pelos elementos da lista B, adicionando-os à lista encadeada
    for (int i = 0; i < B_SIZE; i++)
    {
        int item;
        scanf("%d", &item); // linha 4
        B = add(B, item);
    }

    // printf("A: ");
    // print_linked_list(A);

    // printf("B: ");
    // print_linked_list(B);

    // Verificamos se os elementos da lista B estão contidos na lista A
    // Nem todos os elementos de A precisam estar em B, assim como certos elementos de B não precisam estar em A

    node *current = B;
    while (current != NULL)
    {
        if (search(A, current->item) == NULL)
        {
            printf("0\n");
            return 0;
        }
        current = current->next;
    }

    printf("1\n");

    return 0;
}