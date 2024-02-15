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
        Em uma dada string, você deve indicar se os parênteses e colchetes estão balanceados.
        Diz-se que uma string está balanceada quando para cada parenteses ou colchetes abrindo, existe um equivalente fechando.
        Por exemplo, a string: (()[]) está balanceada, enquanto as strings ((()) e )( não estão balanceadas.

    Formato de entrada
        Você irá receber um número inteiro n indicando a quantidade de strings que virão a seguir. Depois, você receberá n strings, uma em cada linha.A string contém no máximo 255 caracteres e pode ser composta pelos caracteres ')', '(', ']', '[' e ' '.

        O caractere branco deve ser ignorado.
        Também é possível receber uma linha vazia.

    Formato de saída
        Para cada string, você deve imprimir 'Yes' , caso a string esteja balanceada e 'No' caso contrário.
        Se a string for vazia, você deve imprimir 'Yes'
*/

int main()
{
    int input_amount;
    scanf("%d", &input_amount);

    getchar(); // Consumir a nova linha (\n) que separa o número de strings da primeira string

    for (int i = 0; i < input_amount; i++)
    {
        char input[255];
        fgets(input, 255, stdin);

        stack *stack = create_stack();
        int is_balanced = 1;

        // printf("\nInput: %s =-= tamanho: %d\n", input, strlen(input));

        // Percorremos por cada caractere da string
        for (int j = 0; j < strlen(input); j++)
        {
            // Se encontrarmos um caractere de abertura, colocamos ele na pilha
            if (input[j] == '(' || input[j] == '[')
            {
                push(stack, input[j]);
            }
            // Se encontramos um caractere de fechamento, verificamos se o topo da pilha é um caractere de abertura correspondente
            else if (input[j] == ')' || input[j] == ']')
            {
                // Se, por algum motivo, a pilha estiver vazia, não existe nenhum caractere de abertura correspondente e, portanto, a string não está balanceada
                if (is_empty(stack))
                {
                    is_balanced = 0;
                    break;
                }

                // Obtemos o código ASCII do caractere de abertura (supostamente) correspondente ao caractere de fechamento
                int top = pop(stack);

                // Se o caractere de fechamento não corresponder ao caractere de abertura no topo da pilha (int "top"), a string não está balanceada
                if ((input[j] == ')' && top != '(') || (input[j] == ']' && top != '['))
                {
                    is_balanced = 0;
                    break;
                }
            }
        }

        // Para o balanceamento ser verdadeiro, a pilha deve estar vazia (todos os caracteres de fechamento encontraram seus correspondentes de abertura)
        if (is_empty(stack) && is_balanced)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }

    return 0;
}