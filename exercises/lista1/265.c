#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node
{
    char item;
    int frequency;
    node *next;
};
// ou, retira-se o "typedef" acima" acima, e utiliza-se, na definição do ponteiro "next", struct node *next;

// Abstract Data Type (ADT)

node *create_linked_list();
node *add(node *head, char item);
node *search(node *head, char item);
node *remove_item(node *head, char item);

// -----------====================----------------

node *create_linked_list()
{
    return NULL;
}

node *add(node *head, char item)
{
    node *new_node = (node *)malloc(sizeof(node));
    // "malloc() returns a void pointer (void *), which indicates that it is a pointer to a region of unknown data type. Therefore, we must cast it to the correct data type so that we can use it in our program"
    new_node->item = item;
    new_node->frequency = 1;
    new_node->next = head;
    return new_node;
}

node *search(node *head, char item)
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

node *remove_item(node *head, char item)
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

/*
    Descrição:
        Suponha que um texto está armazenado em um array onde cada posição contém um caractere.
        O texto pode conter os 256 caracteres da tabela ASCII.
        Escreva uma função para criar uma lista encadeada onde cada nó possui o caractere e a sua frequência no texto.
        Para esta questão, !!!navegar pela lista que está sendo criada é proibido!!!.
        Lembre-se que para inserir um nó na lista, podemos ter O(1).

    Formato de Entrada:
        Um array onde cada posição possui uma letra do texto.

    Formato de Saída:
        Uma lista onde cada nó possui o caractere e sua frequência no texto.

    Exemplo de Entrada:
        hoje esta quente, logo esta umido.

    Exemplo de Saída:
        u 2
        t 3
        s 2
        q 1
        o 4
        n 1
        m 1
        l 1
        j 1
        i 1
        h 1
        g 1
        e 5
        d 1
        a 2
        . 1
        , 1
          5
*/

int main()
{
    char text[100];
    fgets(text, 100, stdin);

    node *head = create_linked_list();

    char characters_and_frequencies[256][2] = {0}; // 0: character, 1: frequency

    // Como é proibido navegar pela lista que está sendo criada, mapeamos os caracteres e suas frequências em uma matriz
    for (int i = 0; text[i] != '\0'; i++)
    {
        // Caso o caractere ainda não esteja na matriz, adicionamos ele
        if (characters_and_frequencies[text[i]][0] == 0)
        {
            characters_and_frequencies[text[i]][0] = text[i];
        }
        // E incrementamos a frequência
        characters_and_frequencies[text[i]][1]++;
    }

    // Criamos a lista
    for (int i = 0; text[i] != '\0'; i++) // não fazia ideia de que dá pra fazer isso
    {
        // Caso o caractere ainda não tenha sido adicionado à lista, adicionamos ele
        if (characters_and_frequencies[text[i]][0] != 0)
        {
            head = add(head, characters_and_frequencies[text[i]][0]);
            head->frequency = characters_and_frequencies[text[i]][1];
            characters_and_frequencies[text[i]][0] = 0;
        }
    }

    // Imprimimos a lista
    while (head != NULL)
    {
        printf("%c %d\n", head->item, head->frequency);
        head = head->next;
    }

    return 0;
}