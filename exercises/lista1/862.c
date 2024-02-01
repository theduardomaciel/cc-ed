#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* void encontrarMaiorSequencia(node *head)
{
    int inicioAtual = -1, fimAtual = -1;
    int inicioMax = -1, fimMax = -1;
    int contador = 0;
    int posicao = 1;

    while (head != NULL)
    {
        if (head->item == 0)
        {
            if (inicioAtual == -1)
            {
                inicioAtual = posicao;
            }
            fimAtual = posicao;
            contador++;
        }
        else
        {
            if (contador > 0 && contador > (fimMax - inicioMax + 1))
            {
                inicioMax = inicioAtual;
                fimMax = fimAtual;
            }
            inicioAtual = -1;
            fimAtual = -1;
            contador = 0;
        }

        head = head->next;
        posicao++;
    }

    if (contador > 0 && contador > (fimMax - inicioMax + 1))
    {
        inicioMax = inicioAtual;
        fimMax = fimAtual;
    }

     printf("%d %d\n", inicioMax, fimMax);
} */

int main()
{
    node *list = create_linked_list();

    char input[100];
    fgets(input, 100, stdin);

    int size = 0;

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == '0' || input[i] == '1')
        {
            // printf("Adicionando %d à lista\n", input[i] - '0');
            list = add(list, input[i] - '0');
            size++;
        }
    }

    getchar(); // Consumimos o zero que encerra a entrada

    for (int i = size; i >= 0; i--)
    {
        printf("%d ", i);
    }
    printf("\n");

    print_linked_list(list);
    print_linked_list(list);

    node *current = list;

    int current_pos = 0;
    int start = 0, end = 0;
    int can_update_start = 0;
    int max_start = 0, max_end = 0;

    while (current != NULL)
    {
        if (current->item == 0 && can_update_start)
        {
            printf("Encontrado um (início) na posição %d\n", current_pos);
            start = current_pos;
            can_update_start = 0;
        }
        else if (current->item == 1 && !can_update_start)
        {
            printf("Encontrado um (fim) na posição %d\n", current_pos);
            end = current_pos - 1;
            can_update_start = 1;
            if (end - start >= max_end - max_start)
            {
                max_start = start;
                max_end = end;
                printf("Nova maior sequência de 0s: %d-%d\n", max_start, max_end);
            }
        }

        current_pos++;
        current = current->next;
    }

    encontrarMaiorSequencia(list);

    return 0;
}
