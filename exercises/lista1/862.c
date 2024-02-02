#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// Nesse caso, vamos precisar inserir no fim da lista
node *add(node *head, int item)
{
    node *new_node = (node *)malloc(sizeof(node));

    new_node->item = item;
    new_node->next = NULL;

    if (head == NULL)
    {
        return new_node;
    }

    // Vamos percorrer a lista até o último elemento
    node *current = head; // current (ou temp) é um ponteiro que aponta para o mesmo lugar que head
    while (current->next != NULL)
    {
        current = current->next;
    }

    // Agora que encontramos o último elemento, podemos adicionar o novo nó
    current->next = new_node;

    return head;
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
    int i = 1;
    while (head != NULL)
    {
        printf("%d ", head->item);
        if (i >= 10)
        {
            printf(" ");
        }
        head = head->next;
        i++;
    }
    printf("\n");
}

/*
    Descrição:
        Escreva um algoritmo que dada uma lista encadeada contendo apenas valores 0 e 1, retorne as posições inicial e final da maior sequência de elementos 0 dentro da lista.

    Formato de Entrada:
        A entrada consiste de uma sequência de inteiros contendo 0 e 1. Caso a entrada contenha apenas um zero, a entrada encerra.

    Formato de Saída:
        Um inteiro contendo a posição do inicio da sequência, um espaço em branco e outro inteiro contendo a posição do fim da sequência.

    Exemplo de Entrada:
        01100010
        0

    Exemplo de Saída:
        3 5
*/

void get_largest_sequence(node *head)
{
    int start = -1, end = -1;
    int current_start = -1, current_end = -1;
    int position = 0;

    while (head != NULL)
    {
        // printf("item: %d\n", head->item);

        if (head->item == 0)
        {
            if (current_start == -1)
            {
                current_start = position;
            }
            current_end = position;
        }
        else
        {
            current_start = current_end = -1;
        }

        // printf("current_start: %d, current_end: %d\n", current_start, current_end);
        // printf("start: %d, end: %d\n", start, end);

        if (current_end - current_start > end - start || (start == -1 && end == -1))
        {
            start = current_start;
            end = current_end;
        }

        head = head->next;
        position++;
    }

    if (start != -1 && end != -1)
    {
        printf("%d %d\n", start ? start : 0, end ? end : 0);
    }
}

int main()
{
    node *list = create_linked_list();

    char input[100000];
    fgets(input, 100000, stdin);

    int size = 0;

    for (int i = 0; i < strlen(input); i++)
    {
        /* if (input[i] == '0' || input[i] == '1')
        {

        } */
        // printf("Adicionando %d à lista\n", input[i] - '0');
        list = add(list, input[i] - '0');
        size++;
    }

    getchar(); // Consumimos o zero que encerra a entrada

    /*
    // Contagem de trás pra frente
    for (int i = size; i >= 0; i--)
    {
        printf("%d ", i);
    } */

    /* for (int i = 0; i < size; i++)
    {
        printf("%d ", i);
    }
    printf("\n");

    print_linked_list(list); */

    get_largest_sequence(list);

    return 0;
}
