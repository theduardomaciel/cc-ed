#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 25

typedef struct stack stack;
struct stack
{
    int current_size;
    int items[MAX_STACK_SIZE];
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
    new_stack->current_size = 0;
    return new_stack;
}

int is_empty(stack *stack)
{
    return (stack->current_size == 0);
}

void push(stack *stack, int item)
{
    if (stack->current_size == MAX_STACK_SIZE)
    {
        printf("Stack overflow\n");
    }
    else
    {
        stack->items[stack->current_size++] = item;
    }
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
        return stack->items[--stack->current_size];
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
        return stack->items[stack->current_size - 1];
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