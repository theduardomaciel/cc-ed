#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*
    Descrição:

    Ambrósio está jogando um RPG chamado Shinobu's Saga e está prestes a enfrentar Leviathan, o chefe final do jogo. Porém, para chegar em Leviathan, Ambrósio precisa passar por várias masmorras. Nem sempre é possível chegar ao fim da masmorra, o que significa que essa masmorra não tem saída.

    As masmorras são compostas por n salas numeradas de 0 a n-1. Cada sala têm passagens que levam a outras salas. As salas também podem ter tesouros ou não.

    Ambrósio quer explorar toda a masmorra para pegar o máximo de tesouros. Então ele deseja saber se, dada uma masmorra, existe algum caminho partindo da entrada que chegue à saída e se é possível percorrer todas as salas dessa masmorra.


    Obs:
    -   A entrada de uma masmorra de n salas é sempre na sala 0 e a saída é sempre na sala n-1.
    -   As passagens de uma sala para outra são de mão única.
*/

/*
    Formato de entrada:

    A primeira linha da entrada consiste de dois inteiros S e P, separados por um espaço, onde S é o número de salas e P o número de passagens total da masmorra.
    Depois seguem S linhas, cada uma delas com mais dois inteiros A e B separados por um espaço, onde A representa a sala de origem e B a sala de destino.
    Esse par (A,B) representa uma passagem da sala A para a sala B. (0 < S <= 100 e 0 <= P < 9900)
*/

/*
    Formato de saída:

    A saída consiste de duas linhas.
    A primeira linha deve conter a mensagem "EXISTE CAMINHO" se existir caminho da entrada até a saída da masmorra e "NAO EXISTE CAMINHO" caso contrário.
    A segunda linha deve conter a mensagem "EH POSSIVEL PASSAR POR TODAS AS SALAS" se for possível percorrer todas as salas da masmorra e "NAO EH POSSIVEL PASSAR POR TODAS AS SALAS" caso contrário.
    Cada uma das mensagens deve terminar com uma quebra de linha.
*/

int main()
{
    int numSalas, numPassagens;
    scanf("%d %d", &numSalas, &numPassagens);

    int passagens[1000][2];
    for (int i = 0; i < numPassagens; i++)
    {
        scanf("%d %d", &passagens[i][0], &passagens[i][1]);
    }

    int visitado[1000];
    for (int i = 0; i < numSalas; i++)
    {
        visitado[i] = 0;
    }

    int entrada = 0;
    int saida = numSalas - 1;

    int caminho = 0;
    int todasSalas = 1;

    int salaAtual = entrada;
    visitado[salaAtual] = 1;

    // precisamos procurar por um caminho da entrada até a saída
    while (salaAtual != saida)
    {
        int achou = 0;
        for (int i = 0; i < numPassagens; i++)
        {
            // se a sala atual é a sala de origem da passagem e a sala de destino ainda não foi visitada
            if (passagens[i][0] == salaAtual && visitado[passagens[i][1]] == 0)
            {
                salaAtual = passagens[i][1];
                visitado[salaAtual] = 1;
                caminho = 1;
                achou = 1;
                break;
            }
        }

        // se não achamos nenhuma passagem para uma sala não visitada, não existe caminho
        if (achou == 0)
        {
            caminho = 0;
            break;
        }
    }

    // verificamos se todas as salas foram visitadas
    for (int i = 0; i < numSalas; i++)
    {
        if (visitado[i] == 0)
        {
            todasSalas = 0;
            break;
        }
    }

    if (caminho == 1)
    {
        printf("EXISTE CAMINHO\n");
    }
    else
    {
        printf("NAO EXISTE CAMINHO\n");
    }

    if (todasSalas == 1)
    {
        printf("EH POSSIVEL PASSAR POR TODAS AS SALAS\n");
    }
    else
    {
        printf("NAO EH POSSIVEL PASSAR POR TODAS AS SALAS\n");
    }

    return 0;
}