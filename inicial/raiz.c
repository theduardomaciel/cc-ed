#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/*
    Hoje na aula de matemática, Ambrósio aprendeu sobre Raiz Digital.

    A Raiz Digital de um inteiro não-negativo é o valor de digito único resultado do processo de iteração da soma de seus dígitos; cada iteração usando o valor resultante da soma dos dígitos da anterior para fazer a nova soma. O processo continua até chegar em um valor de único digito.

    Por exemplo, se a Raiz Digital de x for representada por S(x), temos que:

    S(7) = 7;

    S(49) = S(4+9) = S(13) = S(1+3) = S(4) = 4

    Como dever de casa, Ambrósio tem n tarefas do seguinte tipo: Encontre o k-º número positivo cujo a Raiz Digital é x
*/

int raiz_digital(int number)
{
    if (number < 10)
    {
        return number;
    }
    else
    {
        int sum = 0;
        while (number > 0)
        {
            sum += number % 10;
            number /= 10;
        }
        return raiz_digital(sum);
    }
}

int loop_raiz(int k, int x)
{
    int number = 0;
    int count = 0;
    while (count < k)
    {
        number++;
        if (raiz_digital(number) == x)
        {
            count++;
        }
    }
    return number;
}

int main()
{
    int amount;
    scanf("%d", &amount);

    for (int i = 0; i < amount; i++)
    {
        int k, x;
        scanf("%d %d", &k, &x);

        printf("%d\n", loop_raiz(k, x));
    }

    return 0;
}