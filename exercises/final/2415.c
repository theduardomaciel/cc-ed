#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITO INT_MAX

/*
    Descrição:

    Dado um grafo direcionado G, faça um programa que retorne o tamanho do menor caminho em G partindo de um vértice S até um vértice E. (S e E são vértices de G).

    Por exemplo, no grafo abaixo:
    0 -> 1
    0 -> 3
    1 -> 2
    1 -> 3
    2 -> 3

    Partindo de 0 até 3 temos os caminhos:

    0 1 3 (tamanho = 2)
    0 3 (tamanho = 1)
    0 1 2 3 (tamanho = 3)

    Logo, o tamanho do menor caminho partindo de 0 até 3 é 1.
*/

/*
    Formato de entrada:

    A entrada consiste de uma linha contendo dois inteiros V e A, onde V representa o número de vértices do grafo G e A, o número de arestas. As próximas A linhas consistem de dois inteiros V1i e V2i (i = 1, 2, 3, ..., A) representando os vértices da i-ésima aresta. Por fim, mais dois inteiros S e E representando o vértice de início e o vértice de chegada.
*/

/*
    Formato de saída:

    Uma string com a mensagem "Tamanho do menor caminho de G: L", onde L é o valor do menor caminho seguido por uma quebra de linha.
*/

int main()
{
    int numVertices, numArestas;

    scanf("%d %d", &numVertices, &numArestas);

    int arestas[1000][2];
    for (int i = 0; i < numArestas; i++)
    {
        scanf("%d %d", &arestas[i][0], &arestas[i][1]);
    }

    int inicio, fim;
    scanf("%d %d", &inicio, &fim);

    // Inicializamos o array de distâncias e marcamos todos os vértices como não visitados
    int distancias[1000];
    int visitado[1000];

    for (int i = 0; i < numVertices; i++)
    {
        distancias[i] = INFINITO;
        visitado[i] = 0;
    }

    // A distância do vértice de início para ele mesmo é 0
    distancias[inicio] = 0;

    // Enquanto houver vértices não visitados
    while (1)
    {
        int menorDistancia = INFINITO;
        int menorVertice = -1;

        // Encontramos o vértice não visitado com a menor distância
        for (int i = 0; i < numVertices; i++)
        {
            if (!visitado[i] && distancias[i] < menorDistancia)
            {
                menorDistancia = distancias[i];
                menorVertice = i;
            }
        }

        // Se não encontramos nenhum vértice não visitado, saímos do loop
        if (menorVertice == -1)
        {
            break;
        }

        // Marcamos o vértice como visitado
        visitado[menorVertice] = 1;

        // Atualizamos as distâncias dos vértices adjacentes ao vértice atual
        for (int i = 0; i < numArestas; i++)
        {
            if (arestas[i][0] == menorVertice)
            {
                int verticeAdjacente = arestas[i][1];
                int peso = 1;

                if (distancias[menorVertice] + peso < distancias[verticeAdjacente])
                {
                    distancias[verticeAdjacente] = distancias[menorVertice] + peso;
                }
            }
        }
    }

    int menorCaminho = distancias[fim];

    printf("Tamanho do menor caminho de G: %d\n", menorCaminho);

    return 0;
}