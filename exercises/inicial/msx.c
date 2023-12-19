#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void to_uppercase(char frase[], int final)
{
	if (final == -1)
		return;
	if (frase[final] >= 'a' && frase[final] <= 'z')
	{
		frase[final] = frase[final] - ('a' - 'A');
	}
	to_uppercase(frase, final - 1);
}

int main()
{
	char *frase = NULL;

	while (1)
	{
		// Lemos a linha
		char *linha = (char *)malloc(75 * sizeof(char));
		fgets(linha, 75, stdin);

		// Verificamos se chegamos ao fim da entrada
		if (strcmp(linha, "the end!\n") == 0)
		{
			frase[strlen(frase) - 1] = '\0'; // Removemos o \n da última linha
			break;
		}

		// Verificamos se é a primeira linha, se sim, alocamos a memória
		if (frase == NULL)
		{
			frase = (char *)malloc(strlen(linha) + 1);
			strcpy(frase, linha);
		}
		else
		{
			// Caso não seja, realocamos a memória para a nova frase (adicionando memória para a nova linha)
			char *temp = (char *)realloc(frase, strlen(frase) + strlen(linha) + 1);
			if (temp != NULL)
			{
				free(frase);
				frase = temp;
				strcat(frase, linha);
			}
		}

		free(linha);
	}

	// Chamamos a função recursiva para transformar a frase em maiúscula
	to_uppercase(frase, strlen(frase) - 1);

	// Imprimimos a frase
	puts(frase);

	// Liberamos a memória
	free(frase);

	return 0;
}