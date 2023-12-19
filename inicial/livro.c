#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void reverseLines(char pagina[1000][200], int start, int end)
{
    if (start >= end)
    {
        return;
    }

    char temp[200]; // Variável temporária para guardar o conteúdo de uma linha

    strcpy(temp, pagina[start]);        // Copiamos o conteúdo da linha inicial na variável temporária, para que não seja perdido
    strcpy(pagina[start], pagina[end]); // Copiamos o conteúdo da linha final na linha inicial, para que a linha inicial seja invertida
    strcpy(pagina[end], temp);          // Copiamos o conteúdo da variável temporária na linha final, para restaurar o conteúdo da linha inicial

    // Chamamos a função recursiva para inverter as linhas entre a linha inicial e a linha final
    reverseLines(pagina, start + 1, end - 1);
}

int main()
{
    char pagina[1000][200];
    int currentLine = 0;

    while (1)
    {
        char linha[200];
        fgets(linha, 200, stdin);

        // Verificamos se chegamos ao final da entrada
        if (linha[0] == '\n')
        {
            break;
        }

        // Se não tivermos nada na página, copiamos o conteúdo da primeira linha na página
        pagina[currentLine][0] = '\0';
        strcat(pagina[currentLine], linha);

        currentLine++;
    }

    // Chamamos a função recursiva para inverter as linhas
    reverseLines(pagina, 0, currentLine - 1);

    // Imprimimos a página invertida
    for (int i = 0; i < currentLine; i++)
    {
        printf("%s", pagina[i]);
    }

    return 0;
}