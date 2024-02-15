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

typedef struct stack stack;
struct stack
{
    node *top;
};

stack *create_stack()
{
    stack *new_stack = (stack *)malloc(sizeof(stack));
    new_stack->top = NULL;
    return new_stack;
}

int is_empty(stack *stack)
{
    return (stack->top == NULL);
}

void push(stack *stack, int item)
{
    node *new_top = (node *)malloc(sizeof(node));
    new_top->item = item;
    new_top->next = stack->top;
    stack->top = new_top;
}

int pop(stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack underflow\n");
        return -1;
    }
    else
    {
        node *top = stack->top;
        int item = top->item;

        stack->top = top->next;
        free(top);

        return item;
    }
}

int peek(stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack underflow\n");
        return -1;
    }
    else
    {
        return stack->top->item;
    }
}

/*
    Descrição
        Você foi convidado para participar do Mozilla Spring Camp, e uma das missões dadas aos participantes foi implementar o funcionamento dos botões de back e forward de um navegador de internet, mostre que você é digno de um estágio na Mozilla.

    Formato de entrada
        Um conjunto de ações, onde:
            ENTER = Entrou em um site
            BACK = Volta uma página
            FORWARD = Avançar uma página

    Formato de saída
        Você deve indicar quantas ações ficaram na pilha de BACK e quantas ações ficaram na pilha de FORWARD.
*/

int stack_size(stack *stack)
{
    int size = 0;
    while (stack->top != NULL)
    {
        size++;
        pop(stack);
    }

    return size;
}

int main()
{
    char action[100];

    stack *back = create_stack();
    stack *forward = create_stack();

    int has_visited = 0;

    while (scanf("%s", action) != EOF)
    {
        if (strcmp(action, "ENTER") == 0)
        {
            if (has_visited)
            {
                // printf("Um site foi acessado (+1 para o back)\n");
                push(back, 1);
                forward->top = NULL; // Caso o usuário acesse um site após voltar, a pilha de forward é resetada
            }
            else
            {
                has_visited = 1;
            }
        }
        else if (strcmp(action, "BACK") == 0)
        {
            if (!is_empty(back))
            {
                // printf("Uma página foi retornada (+1 para o forward, -1 para o back)\n");
                push(forward, pop(back));
            }
        }
        else if (strcmp(action, "FORWARD") == 0)
        {
            if (!is_empty(forward))
            {
                // printf("Uma página foi avançada (+1 para o back, -1 para o forward)\n");
                push(back, pop(forward));
            }
        }
    }

    printf("BACK: %d\n", stack_size(back));
    printf("FORWARD: %d\n", stack_size(forward));

    return 0;
}