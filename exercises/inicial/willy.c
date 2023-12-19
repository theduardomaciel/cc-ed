#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* 
    Willy estava brincando com seus sobrinhos quando propôs a seguinte brincadeira. 
    Dado um número n de no máximo 9 dígitos, ele deve calcular uma função. Mas ele não disse exatamente ao sobrinho como a função funciona. 
    Ao invés disso, ele lhe mostrou um exemplo e deu as dicas abaixo. Veja se você consegue ajudar o sobrinho do titio Willy e resolver a função.

    Exemplo: f(6718) = [(6) * 2 * 4] + [(7) * 3 * 3] + [(1) * 3 * 2] + [(8) * 2 * 1] =  133

    Observe que para cada dígito da entrada, se ele for par, deve ser multiplicado por 2. Se for ímpar, por 3. 

    Além disso, deve-se também multiplicá-lo pela posição do dígito, onde o dígito da unidade corresponde ao valor 1, a dezena ao valor 2, centena 3, e assim por diante.
        - Ou seja, o index + 1 (começa a partir de 1) dá iteração atual
*/

void get_number(int number, int currentSum, int index) {
    int digit = number % 10;
    
    // Primeiramente, calculamos se o dígito é par ou ímpar e aplicamos a regra
    int oddity_multiplier = 3;

    if (digit % 2 == 0) {
        oddity_multiplier = 2;
    }

    // A posição do dígito corresponde ao index
    currentSum += digit * oddity_multiplier * index;
    //printf("current = %d * %d * %d\n", digit, oddity_multiplier, index);

    if (number < 10) {
        printf("%d\n", currentSum);
        return;
    } else {
        return get_number(number / 10, currentSum, index + 1);
    }
}

void loop() {
    int number;
    scanf("%d", &number);

    if (number == 0) {
        return;
    } else {
        get_number(number, 0, 1);

        loop();
    }
}

int main() {
    loop();

	return 0;
}