#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int elem;      // For list
    char name[16]; // For list_names
    int index;     // For list_names
    struct node *next;
} node;

typedef struct directed_acyclic_graph
{
    int size;
    int *visited;
    node **adj_list;
} directed_acyclic_graph;

directed_acyclic_graph *create_graph(int size)
{
    directed_acyclic_graph *g = (directed_acyclic_graph *)malloc(sizeof(directed_acyclic_graph));
    if (g == NULL)
    {
        fprintf(stderr, "Memory allocation error for graph structure.\n");
        exit(EXIT_FAILURE);
    }

    g->size = size;
    g->adj_list = (node **)malloc(size * sizeof(node *));
    g->visited = (int *)malloc(size * sizeof(int));
    if (g->adj_list == NULL || g->visited == NULL)
    {
        fprintf(stderr, "Memory allocation error for graph members.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < size; i++)
    {
        g->adj_list[i] = NULL;
        g->visited[i] = 1;
    }

    return g;
}

int verify_names(const char *name1, const char *name2)
{
    int i = 0;

    while (name1[i] != '\0' && name2[i] != '\0')
    {
        if ((int)name1[i] > (int)name2[i])
            return 0;
        else if ((int)name1[i] < (int)name2[i])
            return 1;

        i++;
    }

    return (name1[i] == '\0') ? 0 : 1;
}

node *add_node_name(node *head, const char name[16], int index)
{
    node *new_node = (node *)malloc(sizeof(node));

    new_node->index = index;
    strcpy(new_node->name, name);
    new_node->next = NULL;

    if (head == NULL)
        return new_node;

    node *current = head;
    node *prev = NULL;

    while (current != NULL && verify_names(current->name, name))
    {
        prev = current;
        current = current->next;
    }

    if (prev == NULL)
    {
        new_node->next = current;
        head = new_node;
    }
    else
    {
        prev->next = new_node;
        new_node->next = current;
    }

    return head;
}

void print_list(node *head)
{
    node *temp = head;

    while (temp != NULL)
    {
        printf("%d ", temp->elem);
        temp = temp->next;
    }
}

void print_list_names(node *head)
{
    node *temp = head;

    while (temp != NULL)
    {
        printf("%s\n", temp->name);
        temp = temp->next;
    }
}

node *remove_node(node *head, int elem)
{
    if (head == NULL)
        return head;

    node *current = head;
    node *prev = NULL;

    while (current != NULL && current->elem != elem)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return head;

    if (prev == NULL)
        head = head->next;
    else
        prev->next = current->next;

    free(current);

    return head;
}

node *remove_node_names(node *head, int elem)
{
    if (head == NULL)
        return head;

    node *current = head;
    node *prev = NULL;

    while (current != NULL && current->index != elem)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
        return head;

    if (prev == NULL)
        head = head->next;
    else
        prev->next = current->next;

    free(current);

    return head;
}

int index_of_name(node *head, const char name[])
{
    node *temp = head;

    while (temp != NULL && (strcmp(temp->name, name) != 0))
        temp = temp->next;

    return (temp != NULL) ? temp->index : -1;
}

void dfs(directed_acyclic_graph *g, node *in, int size)
{
    while (in != NULL)
    {
        node *temp_in = in;
        node *out = NULL;

        while (temp_in != NULL)
        {
            int index = index_of_name(in, temp_in->name);

            if (g->adj_list[index] == NULL)
                out = add_node_name(out, temp_in->name, index);

            temp_in = temp_in->next;
        }

        print_list_names(out);

        temp_in = out;

        while (temp_in != NULL)
        {
            // Remove edges and nodes in one pass
            for (int i = 0; i < size; i++)
            {
                g->adj_list[i] = remove_node(g->adj_list[i], temp_in->index);
            }
            in = remove_node_names(in, temp_in->index);
            temp_in = temp_in->next;
        }
    }
}

void add_edge(directed_acyclic_graph *g, int v, int u)
{
    node *new_node = (node *)malloc(sizeof(node));

    if (new_node == NULL)
    {
        fprintf(stderr, "Memory allocation error for new_node in add_edge.\n");
        exit(EXIT_FAILURE);
    }

    new_node->elem = u;
    new_node->index = 0; // You can set it to any appropriate value
    new_node->next = g->adj_list[v];
    g->adj_list[v] = new_node;
}

int main()
{
    int n, size = 0;

    while (scanf("%d", &n) != EOF)
    {
        directed_acyclic_graph *g = create_graph(n);
        node *names_list = NULL;
        char name1[16], name2[16];

        for (int i = 0; i < n; i++)
        {
            scanf("%s %s", name1, name2);

            int index1 = index_of_name(names_list, name1);

            if (index1 == -1)
            {
                names_list = add_node_name(names_list, name1, size);
                index1 = size;
                size++;
            }

            int index2 = index_of_name(names_list, name2);

            if (index2 == -1)
            {
                names_list = add_node_name(names_list, name2, size);
                index2 = size;
                size++;
            }

            add_edge(g, index1, index2);
        }

        dfs(g, names_list, size);

        // Free allocated memory before exiting
        for (int i = 0; i < size; i++)
        {
            node *current = g->adj_list[i];
            while (current != NULL)
            {
                node *temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(g->adj_list);
        free(g->visited);
        free(g);
    }

    return 0;
}
