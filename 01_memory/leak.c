void f()
{
    int *v;
    v = malloc(540 * sizeof(int));
    return;
}

// SHOULD NOT BE EXECUTED - MEMORY LEAK
// NÃO DEVE SER EXECUTADO - VAZAMENTO DE MEMÓRIA
int main()
{
    while (1)
    {
        f(); // Executar esse código resultará em um memory leak, pois não há liberação de memória com free()
    }
    return 0;
}