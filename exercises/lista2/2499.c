#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void empilhar(stack *stack, int item)
{
    node *new_top = (node *)malloc(sizeof(node)); // Alocamos o espaço de memória para o novo nó
    new_top->item = item;                         // Setamos o item do novo nó
    new_top->next = stack->top;                   // Setamos o próximo nó do novo nó como o topo da pilha
    stack->top = new_top;                         // Setamos o topo da pilha como o novo nó
}

void desempilhar(stack *stack)
{
    if (is_empty(stack))
    {
        printf("Stack underflow\n");
    }
    else
    {
        node *top = stack->top; // Armazenamos o endereço do nó que será desempilhado
        stack->top = top->next; // Setamos o topo da pilha como o próximo nó
        free(top);              // Liberamos o nó que foi desempilhado
    }
}

void imprimir(stack *stack)
{
    node *current = stack->top; // Começamos pelo topo da pilha
    while (current != NULL)     // Enquanto não chegarmos ao fim da pilha
    {
        printf("%d", current->item); // Imprimimos o item do nó atual
        current = current->next;     // E avançamos para o próximo

        if (current != NULL)
        {
            // Se não chegamos ao fim da pilha, imprimimos um espaço
            printf(" ");
        }
    }
    printf("\n");
}

int main()
{
    int item;
    stack *pilha = create_stack();

    char *command = (char *)malloc(10 * sizeof(char));
    scanf("%s", command);

    while (strcmp(command, "Finalizar") != 0)
    {
        if (strcmp(command, "Empilhar") == 0)
        {
            scanf("%d", &item);
            empilhar(pilha, item);
        }
        else if (strcmp(command, "Desempilhar") == 0)
        {
            desempilhar(pilha);
        }
        else if (strcmp(command, "Imprimir") == 0)
        {
            imprimir(pilha);
        }

        scanf("%s", command);
    }

    return 0;
}