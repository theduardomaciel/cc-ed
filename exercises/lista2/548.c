#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// LISTA ENCADEADA ==============================================================

typedef struct list_node list_node;
struct list_node
{
    int item;
    list_node *next;
};

list_node *create_linked_list()
{
    return NULL;
}

int is_list_empty(list_node *head)
{
    return (head == NULL);
}

list_node *add(list_node *head, int item)
{
    list_node *new_node = (list_node *)malloc(sizeof(list_node));
    new_node->item = item;
    new_node->next = head;
    return new_node;
}

list_node *search(list_node *head, int item)
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

list_node *remove_item(list_node *head, int item)
{
    list_node *previous = NULL;
    list_node *current = head;
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

void print_linked_list(list_node *head)
{
    while (head != NULL)
    {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}

void print_linked_list_reverse(list_node *head)
{
    if (head == NULL)
    {
        return;
    }

    // Chamamos recursivamente a função para o próximo nó
    print_linked_list_reverse(head->next);

    // Se o nó atual não é o último, imprimimos um espaço
    // (ERA SÓ TER COLOCADO ESSE IF ANTES DE PRINTAR O NÚMERO, MAS NÃO, EU TINHA QUE TER COLOCADO DEPOIS, NÉ?)
    if (head->next != NULL)
    {
        printf(" ");
    }

    // Imprimimos os dados do nó atual
    printf("%d", head->item);
}

// PILHA ==============================================================

typedef struct stack_node stack_node;
struct stack_node
{
    list_node *item;
    stack_node *next;
};

typedef struct stack stack;
struct stack
{
    stack_node *top;
};

stack *create_stack()
{
    stack *new_stack = (stack *)malloc(sizeof(stack));
    new_stack->top = NULL;
    return new_stack;
}

int is_stack_empty(stack *stack)
{
    return (stack->top == NULL);
}

void push(stack *stack, list_node *item)
{
    stack_node *new_top = (stack_node *)malloc(sizeof(stack_node));
    new_top->item = item;
    new_top->next = stack->top;
    stack->top = new_top;
}

list_node *pop(stack *stack)
{
    if (is_stack_empty(stack))
    {
        printf("EMPTY STACK\n");
        return NULL;
    }
    else
    {
        stack_node *top = stack->top;
        list_node *item = top->item;

        stack->top = top->next;
        free(top);

        return item;
    }
}

list_node *peek(stack *stack)
{
    if (is_stack_empty(stack))
    {
        printf("EMPTY STACK\n");
        return NULL;
    }
    else
    {
        return stack->top->item;
    }
}

void print_stack(stack *stack)
{
    stack_node *current = stack->top;
    while (current != NULL)
    {
        print_linked_list(current->item);
        current = current->next;
    }
}

/*
    Descrição
        Implemente uma pilha na qual cada item seja um número variável de inteiros. Escolha uma estrutura de dados em C para essa pilha e elabore rotinas push e pop para ela.

    Formato de entrada
        Uma sequência de comandos POP ou PUSH.
        Seguida de uma lista de inteiros na linha seguinte, caso o comando seja PUSH.

    Formato de saída
        A cada comando POP, imprimir a lista de inteiros que estava no topo da pilha.
        Se a pilha estiver vazia, imprima: EMPTY STACK
*/

int main()
{
    stack *stack = create_stack();

    char command[100000]; // Falaram no grupo que era só aumentar (que dê certo agora, por favor 🙏)
    while (scanf("%s", command) != EOF)
    {
        if (strcmp(command, "PUSH") == 0)
        {
            // printf("PUSH\n");
            list_node *list = create_linked_list();

            char input[100];
            scanf(" %[^\n]", input);
            // Admito que não entendi muito bem como funciona o scanf com %[^\n] mas tamo aí
            // (tentei de MUITAS outras formas e nenhuma funcionou, acreditem em mim)
            // (o Linux crashou 2 vezes por sinal)

            // Convertemos os números da linha (string) para inteiros e adicionamos à lista
            // printf("Input: %s\n", input);
            int num;
            char *token = strtok(input, " ");
            while (token != NULL)
            {
                sscanf(token, "%d", &num);
                list = add(list, num);
                token = strtok(NULL, " ");
            }

            push(stack, list);
            // print_linked_list(list);
        }
        else if (strcmp(command, "POP") == 0)
        {
            // printf("POP\n");
            list_node *list = pop(stack);
            if (list != NULL)
            {
                print_linked_list_reverse(list);
                printf("\n");
                free(list); // Liberamos a memória da lista após imprimir
            }
        }

        // printf("Reiniciando loop...\n");
    }

    return 0;
}
