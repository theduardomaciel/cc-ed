#include <stdio.h>

/**
 * Calcula a área sob uma curva utilizando o método do retângulo.
 *
 * @param f Função que representa a curva.
 * @param a Limite inferior do intervalo.
 * @param b Limite superior do intervalo.
 * @return A área sob a curva.
 */
double area(double (*f)(double x), double a, double b)
{
    double sum, dt;
    int i;
    sum = 0.0;
    dt = (b - a) / 100.0;
    for (i = 0; i < 100; i++)
        sum += (*f)(i * dt + a) * dt;
    return sum;
}

/**
 * Calcula o quadrado de um número.
 *
 * @param x O número a ser elevado ao quadrado.
 * @return O quadrado do número.
 */
double square(double x)
{
    return x * x;
}

/**
 * Calcula o cubo de um número.
 *
 * @param x O número a ser elevado ao cubo.
 * @return O cubo do número.
 */
double cube(double x)
{
    return x * x * x;
}

int main()
{
    printf("Area = %f\n", area(square, 2, 3));
    printf("Area = %f\n", area(cube, 2, 3));

    return 0;
}

/*
    No código, calculamos a área sob uma curva usando a regra dos trapézios. A função area é a mais complexa.
    Ela recebe três argumentos: um ponteiro para uma função f, e dois números de ponto flutuante a e b.
    A função apontada por f deve receber um número de ponto flutuante e retornar um número de ponto flutuante.
    A função area calcula a área sob a curva definida pela função f entre a e b dividindo o intervalo em 100 segmentos e somando as áreas dos retângulos formados.

    As funções square e cube são funções simples que recebem um número de ponto flutuante e retornam o quadrado e o cubo desse número, respectivamente.

    A função main é a função que é executada quando o programa é iniciado. Ela chama a função area duas vezes, uma vez com a função square e uma vez com a função cube, e imprime os resultados. Os valores 2 e 3 são os limites de integração para o cálculo da área.

    Este código é um exemplo de como as funções podem ser passadas como argumentos para outras funções em C, o que é uma característica poderosa da linguagem que permite uma grande flexibilidade.
*/