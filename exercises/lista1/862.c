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
            // Se não tivermos um início, setamos o início como a posição atual
            if (current_start == -1)
            {
                current_start = position;
            }

            // Por fim, atualizamos o fim
            current_end = position;
        }
        else
        {
            // Se encontramos um 1, resetamos os valores, pois a sequência de 0s acabou
            current_start = -1;
            current_end = -1;
            // ou current_start = current_end = -1;
        }

        // printf("current_start: %d, current_end: %d\n", current_start, current_end);
        // printf("start: %d, end: %d\n", start, end);

        // Se a sequência atual for maior que a maior sequência encontrada até agora, atualizamos os valores
        if ((current_end - current_start > end - start) || (start == -1 && end == -1))
        {
            start = current_start;
            end = current_end;
        }

        // Navegamos para o próximo elemento da lista
        head = head->next;
        position++;
    }

    printf("%d %d\n", start != -1 ? start : 0, end != -1 ? end : 0);
}

int main()
{
    node *list = create_linked_list();

    // Loopamos o input até que o usuário insira um "0" isolado no console
    char input[1000];

    // Obtemos o primeiro input
    scanf("%s", &input);

    // printf("input: %s\n", input);

    while (strcmp(input, "0") != 0)
    {
        // Adicionamos cada caractere da string de input na lista
        for (int i = 0; i < strlen(input); i++)
        {
            list = add(list, input[i] - '0');
        }
        // print_linked_list(list);

        // Obtemos a maior sequência de 0s
        get_largest_sequence(list);

        // Resetamos a lista
        list = create_linked_list();

        // Obtemos o próximo input
        scanf("%s", &input);
    }

    return 0;
}

/*
    // Contagem de trás pra frente
    for (int i = size; i >= 0; i--)
    {
        printf("%d ", i);
    }
*/
