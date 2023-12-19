# Eficiência de Algoritmos e Notação Big O

Esta seção aborda a eficiência de algoritmos e a notação Big O, conceitos cruciais para avaliar o desempenho e a escalabilidade dos algoritmos em diferentes cenários. <br />
Compreender esses tópicos é fundamental para projetar soluções eficientes e otimizadas.

## Conteúdo

### O que torna um algoritmo "melhor"?

-   Ao compararmos os seguintes trechos de códigos, responsáveis por realizar a soma de números até um dado `n`, percebe-se que um é melhor que o outro, pois requer **menos tempo** para executar!

```c
int sum_integers(int n)
{
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        sum = sum + i;
    }
    return sum;
}
```

```c
int sum_integers(int n)
{
    return (n + 1) * n / 2; // solução de Gauss
}
```

-   Por isso, devemos nos preocupar com dois recursos: **tempo** e **espaço**

![Eficiência da busca linear contra a busca binária](assets/linear_vs_binary.png)

<br />

> [!NOTE]
> No caso de problemas ou erros com algum comentário ou exemplo nesse repositório, abra um [issue](https://github.com/theduardomaciel/cc-ed/issues/new) ou [sugira uma sugestão](https://github.com/theduardomaciel/cc-ed/fork) para que o conteúdo esteja sempre o mais correto!

<br />

## Links úteis

-   [pendente]
