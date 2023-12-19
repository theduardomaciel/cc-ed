#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

/* 
	Crie um programa que tenha apenas uma função, além da principal, que receberá como parâmetro um natural n (0 <= n <= 999999) e que devolverá "n - 3" se o dígito mais a esquerda de n for ímpar ou "n - 4" se o dígito mais a esquerda for par. 

	RESTRIÇÕES:
	(a) função recursiva; 
	(b) não deverá usar vetores e/ou ponteiros; 
	(c) não usar variáveis globais;
*/

int funcao(int n) {
	if (n < 10) {
        //printf("n = %d\n", n);
		if (n % 2 == 0) {
			return 4;
		} else {
			return 3;
		}
	} else {
		return funcao(n / 10);
	}
}

int main() {
	int n;
	scanf("%d", &n);

	// Imprimimos o resultado da função
	printf("%d\n", n - funcao(n));

	return 0;
}