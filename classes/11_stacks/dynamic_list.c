#include <stdio.h>
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

// Abstract Data Type (ADT)

stack *create_stack();
void push(stack *stack, int item);
int pop(stack *stack);
int peek(stack *stack);
int is_empty(stack *stack);

// -----------====================----------------

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

int main()
{
    int number = 2744;
    int digit;
    stack *stack = create_stack();
    printf("%d in Binary: ", number);

    while (number != 0)
    {
        digit = number % 2;
        push(stack, digit);
        number = number / 2;
    }

    while (!is_empty(stack))
    {
        printf("%d", pop(stack));
    }
    printf("\n");

    return 0;
}