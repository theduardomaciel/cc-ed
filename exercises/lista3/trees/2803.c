#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/*
-> Descrição
    Sua tarefa é simples: dadas várias árvores em notação de parênteses, concatene a primeira árvore com as demais fornecidas.
    Por exemplo, as árvores (1(2()())(3()())) e (3(4()())(5()())) são as representações em notação de parênteses das árvores mostradas abaixo:

      1       3
     / \     / \
    2   3   4   5

    O resultado da concatenação da segunda árvore com a primeira será (1(2()())(3(4()())(5()()))):

          1
         / \
        2   3
           / \
          4   5

    Obs:
        - A primeira árvore informada é a matriz.
        - A segunda árvore informada deve ser concatenada com a matriz. A árvore resultante dessa concatenação será sua nova matriz.
        - A terceira árvore informada (se houver) será concatenada com a nova matriz obtida no passo anterior gerando uma nova matriz e assim por diante...
        - É garantido que todas as árvores fornecidas têm nós de valores distintos (exceto as raízes).

-> Formato de entrada
    A entrada consiste de várias linhas.
    Cada linha contendo uma String que é a representação de uma árvore em notação de parênteses.
    As entradas se encerram ao ser fornecida a String "()".

-> Formato de saída
    A saída deve ser uma String com a representação em notação de parênteses da matriz resultante de todas as concatenações de árvores.
*/

int main()
{
    return 0;
}