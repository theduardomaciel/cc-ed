# Complexidade de um programa de computador

-   Suponhamos dois algoritmos que determinam se um dado número é primo ou não

### Algoritmo 1

```c
for i = 2 to n - 1
    if i divides n
        n is not prime
```

### Algoritmo 2

```c
for i = 2 to sqrt(n)
    if i divides n
        n is not prime
```

-   Considerando que cada divisão leve 1ms para ser realizada, temos que

| n                       | 1                              | 2                             |
| ----------------------- | ------------------------------ | ----------------------------- |
| 11                      | 9ms                            | 2ms                           |
| 101                     | 99ms                           | 9ms                           |
| 1000003 = 106 + 3       | 106ms ≃ 103sec ≃ 16.66min      | √(106 + 3) - 1 ≃ 103ms ≃ 1sec |
| 10000000019 = 1010 + 19 | 1010ms ≃ 107sec ≃ **115 dias** | 105ms ≃ 100seg ≃ **1.66min**  |

-   Percebe-se que com uma sutil mudança, a complexidade do algoritmo mudou drasticamente.

<table>
<tr>
<th>
1
</th>
<th>
2
</th>
</tr>
<td>
<pre>
for i = 2 to n - 1
    if i divides n
     n is not prime
</pre>
    (n - 2) times <br />
    <strong>O(n)</strong>
</td>

<td>
<pre>
for i = 2 to sqrt(n)
    if i divides n
        n is not prime
</pre>
    (√n - 1) times <br />
    <strong>O(√n)</strong>
</td>

</tr>
</table>

## Premissas

-   As constantes que multiplicam são ignoradas
-   As instruções dentro de um loop serão executadas quantas vezes o **máximo** permitido pelo controle de loop

```c
int sum_of_list(list, n)
{
    int total = 0; // C1 -> 1
    for (i = 0; i < n; i++) // C2 -> n + 1
        total = total + list[i]; // C3 -> n
    return total; // 1 (C4) -> 1
}
```

| Custo     | Quant. de tempo |
| --------- | --------------- |
| 1 ($C_1$) | 1               |
| 2 ($C_2$) | n + 1           |
| 2 ($C_3$) | n               |
| 1 ($C_4$) | 1               |

$$
t(n) = 1 + 2(n + 1) + 2n + 1 \\
t(n) = 4n + 4 \\ \ \\
t(n) = cn + c’ \\
$$

-   Tendo em vista que são os únicos que dependem de n, $c = C_2 + C_3$
-   $c’ = C_1 + C_2 + C_4$

## Declarações

-   É importante lembrar que constantes que multiplicam são ignoradas.
-   Em uma sequência de declarações [Declaração 1, Declaração 2, ..., Declaração $n$], o tempo total equivale a
    $$
    Tempo \ total =  t(s1) + t(s2) + ... + t(sn)
    $$
-   Se cada declaração for simples, o tem para cada uma dessas declarações é constante, assim como tempo total: $O(1)$

## If statements

-   O tempo é igual ao **maior** dos dois caminhos
-   Se o **Caminho 1** é $O(n)$ e o **Caminho 2** for $O(1)$, o pior caso de todo o `if-then-else statement` deve ser $O(n)$

```c
if (condition) {
    // Caminho 1 - O(n)
    sequência de declarações 1
} else {
    // Caminho 2 - O(1)
    sequência de declarações 2
}
```

## For loops

-   Como um loop executa $n$ vezes, as declarações dentro dele também irão executar $n$ vezes.
-   Assumindo que as declarações internas são $O(1)$, o tempo total para o loop é $n$, o qual tem $O(n).

```c
for (i = 1; i <= n; i++) {
    something that is O(1) // 1 + 1 + 1 + ... + 1 (n times)
}
```

## Nested for loops

-   O loop interno da função interna roda $k$ vezes.

```c
for (k = 1; k <= n; k++) { // roda n vezes
    for (i = 1; i <= k; i++) {  // roda k vezes
        something that is O(1)
    }
}
```

-   Mesmo estando dentro de um loop externo que roda $n$ vezes, não podemos assumir de cara que o loop interno rode $n$ vezes também.

```c
1 (first time) + 2 (second time) + ... * n (last time)
```

-   Mesmo que não possamos fazer isso, no fim das contas, a estimativa final permanece a mesma, tendo em vista que $k$ executa $(n+1) / 2$ vezes.

$$\sum_{i=1}^{n} i^2 = n(n+1)/2$$

que ainda é $O(n^2)$

-   Utilizando outro exemplo, temos

```c
for (i = 1; i <= n; i++) {
    for (j = 1; j <= i; j++) {
        for (k = 1; k <= i; k++) {
            something that is O(1)
        }
    }
}
```

-   A cada valor de $i$, os outros dois loops internos contribuem para $i^2$
    $$1^2 + 2^2 + 3^2 + ... + n^2$$

$$\sum_{i=1}^{n} i^2 = n(n+1)(2n + 1)/6$$

que ainda é $O(n^3)$

## Exercícios

### 1.

```c
for (i = 0; i < n; i++) {
    something that is O(1)
}
for (j = 0; j < m; j++) {
    something that is O(1)
}
```

### 2.

```c
for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
        something that is O(1)
    }
}
for (k = 0; k < n; k++) {
    something that is O(1)
}
```

### 3.

```c
for (i = 0; i < n; i++) {
    for (j = n; j > i; j--) {
        something that is O(1)
    }
}
```

### 4.

```c
for (i = 0; i < n; i++) {
    min = i;
    for (j = i + 1; j < n; j++)
        if (s[j] < s[min]) min = j;
    swap(&s[i], &s[min]);
}
```
