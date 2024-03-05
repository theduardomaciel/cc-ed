#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 1000

typedef struct heap
{
    int size;
    int data[MAX_HEAP_SIZE];
} heap;

// Tipo Abstrato de Dados (ADT)

heap *create_heap();
void enqueue(heap *heap, int item);
int dequeue(heap *heap);
int get_parent_index(heap *heap, int i);
int get_left_index(heap *heap, int i);
int get_right_index(heap *heap, int i);
void max_heapify(heap *heap, int i);
int item_of(heap *heap, int i);
void heapsort(heap *heap);

// Implementations

int get_parent_index(heap *heap, int i)
{
    return i / 2;
}

int get_left_index(heap *heap, int i)
{
    return 2 * i;
}

int get_right_index(heap *heap, int i)
{
    return 2 * i + 1;
}

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

void swap_without_aux(int *a, int *b)
{
    *a = *a + *b; // Realiza a soma dos valores
    *b = *a - *b; // Subtrai o valor de b do valor de a
    *a = *a - *b; // Subtrai o valor de b do valor de a

    // *a = *a ^ *b;
    // *b = *a ^ *b;
    // *a = *a ^ *b;
}

/**
 * Obtém o item no índice especificado no heap.
 *
 * @param heap O heap.
 * @param i O índice do item a ser obtido.
 * @return O item no índice especificado.
 */
int item_of(heap *heap, int i)
{
    return heap->data[i];
}

void enqueue(heap *heap, int item)
{
    if (heap->size >= MAX_HEAP_SIZE)
    {
        printf("Heap overflow");
    }
    else
    {
        // Antes de inserir o item no heap, incrementamos o tamanho do heap
        heap->data[++heap->size] = item;

        int key_index = heap->size;                            // Índice do item que será inserido no heap
        int parent_index = get_parent_index(heap, heap->size); // Índice do pai do item que será inserido no heap

        // Realizamos o loop procurando o lugar correto do item no heap enquanto o valor do item for maior que o valor de seu pai
        //  O parent_index deve ser maior ou igual a 1, pois o índice 0 é reservado para o tamanho do heap
        while (parent_index >= 1 &&
               heap->data[key_index] > heap->data[parent_index])
        {
            // Trocamos os valores dos índices para manter a propriedade de max-heap
            swap(&heap->data[key_index], &heap->data[parent_index]);

            key_index = parent_index;
            parent_index = get_parent_index(heap, key_index);
        }
    }
}

// Quando chamada, assume que os subárvores à esquerda e à direita de i são max-heaps, mas o valor de i pode ser menor que seus filhos, violando a propriedade de max-heap
// A função max_heapify é a responsável por manter a propriedade de max-heap
void max_heapify(heap *heap, int i)
{
    int largest;
    int left_index = get_left_index(heap, i);
    int right_index = get_right_index(heap, i);

    // Para definir o maior valor, comparamos o valor do índice atual com o valor do índice da esquerda e direita
    if (left_index <= heap->size &&
        heap->data[left_index] > heap->data[i])
    {
        largest = left_index;
    }
    else
    {
        largest = i;
    }

    if (right_index <= heap->size &&
        heap->data[right_index] > heap->data[largest])
    {
        largest = right_index;
    }

    // Se o maior valor não for o valor do índice atual,
    if (heap->data[i] != heap->data[largest])
    {
        swap(&heap->data[i], &heap->data[largest]); // Trocamos os valores dos índices para manter a propriedade de max-heap
        max_heapify(heap, largest);                 // Chamamos a função max_heapify recursivamente com o índice do maior valor
    }
}

int dequeue(heap *heap)
{
    if (heap->size == 0)
    {
        printf("Heap underflow");
        return -1;
    }
    else
    {
        int item = heap->data[1]; // Guardamos o item a ser removido, que é o primeiro do heap (fila)

        heap->data[1] = heap->data[heap->size]; // Atribuímos o último item do heap para a primeira posição

        heap->size--; // Decrementamos o tamanho do heap, pois removemos um item

        max_heapify(heap, 1); // Chamamos a função max_heapify para manter a propriedade de max-heap

        return item;
    }
}

void heapsort(heap *heap)
{
    int i;
    for (i = heap->size; i >= 2; i--) // Começamos com i = heap->size e decrementamos até i = 2
    {
        // Trocamos os valores dos índices 1 e i para manter a propriedade de max-heap
        swap(&heap->data[1], &heap->data[i]);

        // Decrementamos o tamanho do heap, pois removemos um item
        heap->size--;

        // Chamamos a função max_heapify para manter a propriedade de max-heap
        // Essa função não irá incluir o último elemento do heap, pois o tamanho do heap foi decrementado
        max_heapify(heap, 1);
    }
}

int main()
{
    heap *heap = create_heap();
    enqueue(heap, 3);
    enqueue(heap, 4);
    enqueue(heap, 1);
    enqueue(heap, 10);
    enqueue(heap, 5);
    enqueue(heap, 2);
    enqueue(heap, 7);
    enqueue(heap, 6);
    enqueue(heap, 8);
    enqueue(heap, 9);
    heapsort(heap);
    for (int i = 0; i < heap->size; i++)
    {
        printf("%d\n", heap->data[i]);
    }
    return 0;
}