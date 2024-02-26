# Algoritmos de Busca

Esta seção abrange códigos e exemplos relacionados a algoritmos de busca em diferentes paradigmas de programação, como C e Haskell. Os algoritmos de busca são fundamentais para localizar informações em conjuntos de dados, como arrays, e compreender sua implementação é essencial para desenvolver soluções eficientes.

## Conteúdo

### Implementações:

Esta seção contém exemplos práticos de algoritmos de busca implementados em linguagem C e em Haskell, destacando as características funcionais dessas linguagens e oferecendo alternativas de abordagem.

## Linear search (busca linear ou sequencial)

-   É um algoritmo simples em que um array é percorrido, a fim de encontrar um item de interesse.
-   Consiste em checar cada elemento, em sequência, até que o item desejado seja encontrado.

```c
int linear_search(int *v, int size, int element)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (v[i] == element)
        {
            return i;
        }
    }
    return -1;
}
```

| Melhor caso                                | Pior caso                                                      |
| ------------------------------------------ | -------------------------------------------------------------- |
| Quando o elemento está na primeira posição | Quando o elemento não é encontrado (ou está na última posição) |
| Somente uma (1) comparação é necessária    | n comparações são necessárias                                  |
| O tempo de execução é constante (c)        | O tempo de execução é proporcional ao tamanho do array         |

## Busca binária

-   Ao escolher algumas posições de forma estratégica, diminuímos a quantidade de posições que precisam ser checadas.
-   Para funcionar, **a lista deve estar ordenada**
-   O algoritmo seleciona como pivô (index), sempre, o meio da array
-   A partir desse pivô, o valor do elemento `array[index]` é verificado:
    1. Se o elemento procurado for MAIOR (>) que `array[index]`, uma nova busca é iniciada, dessa vez **a partir do meio do array**
    2. Se o elemento procurado for MENOR (<) que `array[index]`, uma nova busca é iniciada, dessa vez **até o meio do array**

> ![WARNING]
> Cuidado com o cálculo do pivô central que divide o array em duas partes!
> Para evitar o _overflow_ com números muito grandes, deve-se fazer o seguinte cálculo: `start + (end - start) / 2`

### ⏳ Complexidade

| Tamanho do array | Tempo para encontrar 1 elemento |
| ---------------- | ------------------------------- |
| 1                | 1                               |
| 3                | 2                               |
| 7                | 1 + 2 = 3                       |
| 15               | 1 + 3 = 4                       |
| 31               | 1 + 4 = 5                       |
| 2^t - 1          | t                               |

-   Diferente da busca linear, que possui `O(n)`, o Big O da busca binária é: `O(log(n)`

<br />

> [!NOTE]
> No caso de problemas ou erros com algum comentário ou exemplo nesse repositório, abra um [issue](https://github.com/theduardomaciel/cc-ed/issues/new) ou [sugira uma sugestão](https://github.com/theduardomaciel/cc-ed/fork) para que o conteúdo esteja sempre o mais correto!

<br />

## Links úteis

-   [pendente]
