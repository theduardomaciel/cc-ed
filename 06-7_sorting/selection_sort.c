#include <stdio.h>

void selection_sort(int s[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
            if (s[j] < s[min])
                min = j;
        swap(&s[i], &s[min]);
    }
}

#define SIZE 6

int main()
{
    int v[] = {5, 2, 4, 6, 1, 3};

    for (int i = 0; i < SIZE; i++)
        printf("%d ", v[i]);

    selection_sort(v, SIZE);

    printf("\n");

    for (int i = 0; i < SIZE; i++)
        printf("%d ", v[i]);

    return 0;
}