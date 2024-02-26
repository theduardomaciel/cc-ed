#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *v;
    v = malloc(60 * sizeof(int));

    if (v == NULL)
    {
        printf("Could not allocate memory !");
    }
    else
    {
        printf("%d\n", v); // Ao printarmos, o que é exibido é o endereço de memória
    }

    free(v); // Após o uso, devemos liberar a memória alocada

    return 0;
}