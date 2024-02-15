#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Armazena o primeiro item da fila
typedef struct _stack STACK;

// Armazena o conteúdo do nó e um ponteiro para o proximo nó da fila
typedef struct _node NODE;

struct _stack
{
    NODE *head;
};
struct _node
{
    int element;
    NODE *next;
};

// Cria uma stack com o a head NULL
STACK *Create_stack();

// Recebe um elemento e cria e retorna um novo node com o elemento passado
NODE *create_node(int element);

// Verifica se a pilha está vazia
int IS_EMPTY(STACK *stack);

// Recebe uma pilha e retorna o elemento que está no topo da pilha
int POP(STACK *stack);

// Recebe uma pilha e um inteiro e retorna a nova pilha com um novo node adicionado em seu topo
void PUSH(STACK *stack, int element);

// Recebe a pilha e a operação a ser feita e faz a operação da calculadora
void result(STACK *stack, char operation);

// Recebe uma pilha vazia e quantas strings serão lidas
// Lê as n strings que vão seguir e resolver as expressões
void Calculadora(STACK *calculadora, int size);

int main()
{
    STACK *calculadora = Create_stack();
    int k;
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 1: %d\n", POP(calculadora));
    scanf("%d", &k);
    Calculadora(calculadora, k);
    printf("Coordenada 2: %d\n", POP(calculadora));
}

/*
    As coordenadas estavam em NOTAÇÃO POLONESA INVERSA (notação pós-fixa).
    Você terá as funções de uma calculadora RPN. Tal calculadora utiliza uma pilha para calcular o resultado de uma notação polonesa inversa.

    Formato de entrada
        A entrada consiste em um numero n, correspondendo a quantidade de componentes da expressão.
        Em seguida vão ser inserida n linhas correspondente a cada componente da expressão.
        E depois o processo se repete novamente.

    Formato de saída
        A saída consiste no resultado da expressão que foi calculada.

        Coordenada 1: n
        Coordenada 2: n1

        Onde n e n1 são os resultados das duas expressões calculadas.
*/

STACK *Create_stack()
{
    STACK *new_stack = (STACK *)malloc(sizeof(STACK)); // Alocamos o espaço de memória para a nova pilha
    new_stack->head = NULL;                            // Setamos o topo da pilha como NULL
    return new_stack;
}

NODE *create_node(int element)
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE)); // Alocamos o espaço de memória para o novo nó
    new_node->element = element;                   // Setamos o item do novo nó
    new_node->next = NULL;                         // Setamos o próximo nó do novo nó como NULL
    return new_node;
}

int IS_EMPTY(STACK *stack)
{
    return (stack->head == NULL);
}

int POP(STACK *stack)
{
    if (IS_EMPTY(stack))
    {
        return -1;
    }
    else
    {
        int element = stack->head->element; // Armazenamos o elemento do nó que será desempilhado
        NODE *temp = stack->head;           // Armazenamos o endereço do nó que será desempilhado

        stack->head = stack->head->next; // Setamos o topo da pilha como o próximo nó
        free(temp);
        return element;
    }
}

void PUSH(STACK *stack, int element)
{
    NODE *new_node = create_node(element); // Cria um novo nó com o elemento passado
    new_node->next = stack->head;          // Setamos o próximo nó do novo nó como o atual (antes da adição) topo da pilha
    stack->head = new_node;                // Setamos o topo da pilha como o novo nó
}

// Recebe a pilha e a operação a ser feita e faz a operação da calculadora
void result(STACK *stack, char operation)
{
    // Cuidado com a ordem das variáveis a e b para não acabar em um resultado errado (negativo, por exemplo)
    // Como alternativa, podemos considerar "b" como "operando2" e "a" como "operando1"
    int b = POP(stack);
    int a = POP(stack);

    // printf("Desempilhando %d e %d e fazendo a operação %c\n", a, b, operation);

    int result;

    switch (operation)
    {
    case '+':
        result = a + b;
        break;
    case '-':
        result = a - b;
        break;
    case '*':
        result = a * b;
        break;
    case '/':
        result = a / b;
        break;
    }

    // printf("Empilhando %d\n", result);
    PUSH(stack, result);
}

// Recebe uma pilha vazia e quantas strings serão lidas
// Lê as n strings que vão seguir e resolver as expressões
void Calculadora(STACK *calculadora, int size)
{
    char expression[10000];

    // Lemos as n operações e resolvemos elas
    for (int i = 0; i < size; i++)
    {
        scanf("%s", expression);

        char *ptr;
        int number = strtol(expression, &ptr, 10); // Convertemos a string para um número inteiro

        if (*ptr == '\0') // Verificamos se a conversão deu certo
        {
            // Se o caractere for um operando, empilhamos ele, ou seja, colocamos no topo da pilha
            PUSH(calculadora, number);
        }
        else
        {
            // Se for um operador, desempilhamos os dois últimos elementos da pilha e fazemos a operação
            for (int j = 0; j < strlen(expression); j++)
            {
                result(calculadora, expression[j]);
            }
        }
    }
}