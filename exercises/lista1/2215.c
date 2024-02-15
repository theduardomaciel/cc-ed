#include <stdio.h>
#include <string.h>
#include <math.h>
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
    // int size = 0;
    while (head != NULL)
    {
        printf("%d ", head->item);
        head = head->next;
        // size++;
    }
    // printf("Size: %d\n", size);
    printf("\n");
}

/*
    Descrição
    Suponha dois números inteiros positivos representados por uma lista encadeada, em que cada nó armazena um único dígito.
    Escreva um programa para receber dois números representados desse modo e retornar a soma, também armazenada em uma lista encadeada.

        Obs1: Seu programa deve sempre ler e imprimir os dígitos de cada número do mais significativo para o menos significativo.
        A entrada pode conter zeros à esquerda; porém, no resultado calculado, a lista não deve incluir zeros à esquerda.

        Obs2: A referência para o início da lista deve ser padronizada: deve apontar sempre, ou para o dígito mais significativo, ou para o menos significativo, de todas as instâncias de listas utilizadas, de acordo com o padrão definido.

        Obs3: O símbolo '+' determina o término da entrada do primeiro número, enquanto que '=' determina o término da entrada do segundo número.

        Obs4: Caso uma lista que deveria representar um número esteja vazia, deve ser impressa na tela a mensagem 'Lista vazia!' no momento de sua impressão.

    Exemplo:

    Entrada:    2 1 3
                +
                2 4 2
                =
    Saída:      4 5 5

    Exemplo 2:

    Entrada     0 1 3
                +
                0 0 9
                =
    Saída:      2 2
*/

int main()
{
    node *number1 = create_linked_list();
    node *number2 = create_linked_list();

    char n = getchar();
    while (n != '+')
    {
        // Ignoramos caracteres que possam atrapalhar, como espaços, quebras de linha e tabs
        if (n == ' ' || n == '\n' || n == '\t')
        {
            n = getchar();
            continue;
        }

        // printf("n de 1: %d\n", n - '0');

        number1 = add(number1, n - '0');
        n = getchar();
    }

    n = getchar(); // Ignoramos o sinal de adição

    while (n != '=')
    {
        // printf("Atual: %c\n", n);

        //  Ignoramos caracteres que possam atrapalhar, como espaços, quebras de linha e tabs
        if (n == ' ' || n == '\n' || n == '\t')
        {
            n = getchar();
            continue;
        }

        // printf("n de 2: %d\n", n - '0');

        number2 = add(number2, n - '0');
        n = getchar();
    }

    /* printf("Lista 1: ");
    print_linked_list(number1);

    printf("\nLista 2: ");
    print_linked_list(number2);
    printf("\nFim\n"); */

    int carry = 0;
    node *result = create_linked_list();

    if (is_empty(number1) && is_empty(number2))
    {
        printf("Lista vazia!\n");
        return 0;
    }

    while (!is_empty(number1) || !is_empty(number2))
    {
        int sum = carry; // Inicializamos a soma com o valor do vai-um (carry)

        // Caso o primeiro número ainda não esteja vazio, somamos o valor desse número ao valor da soma e avançamos para o próximo número
        if (!is_empty(number1))
        {
            sum += number1->item;
            number1 = number1->next;
        }

        // Fazemos o mesmo para o segundo número
        if (!is_empty(number2))
        {
            sum += number2->item;
            number2 = number2->next;
        }

        // Atualizamos o vai-um (carry) e adicionamos o valor da soma à lista resultante
        carry = sum / 10;
        result = add(result, sum % 10);
    }

    // Caso ainda haja um carry, adicionamos ele à lista resultante
    if (carry)
    {
        result = add(result, carry);
    }

    // Caso haja zeros à esquerda, removemos eles
    while (result->next != NULL && result->item == 0)
    {
        // Caso queiramos liberar a memória, armazenamos uma variável temporária para o nó que será removido
        node *temp = result;

        result = result->next; // Atualizamos a referência do início da lista, removendo o nó que queremos

        free(temp); // Liberamos a memória do nó removido
    }

    if (is_empty(result))
    {
        printf("Lista vazia!\n");
    }
    else
    {
        print_linked_list(result);
    }

    return 0;
}