/*
    Codifique a função minimax(v,n,a,b), que recebe um vetor v
    contendo n números reais e devolve em a e b, respectivamente, os valores
    mínimo e máximo entre aqueles armazenados em v.
*/

#include <stdio.h>

void minimax(int v[], int n, int *a, int *b) {
    int i;
    *a = *b = v[0];
    for (int i = 1; i < n; i++) {
        *a = v[i] < *a ? v[i] : *a;
        *b = v[i] > *b ? v[i] : *b;
    }
}

int main() {
    int n = 8;    
    int v[] = {8, 3, 6, -3, 2, 9, 1, 12};
    int a, b;

    minimax(v, n, &a, &b);

    printf("Máximo e Mínimo do Vetor\n");
    printf("minimo: %d \n", a);
    printf("maximo: %d \n", b);

    getchar();
    return 0;
}