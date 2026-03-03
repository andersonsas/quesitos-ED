#include <stdio.h>

/*Exercício 7.1.
    Explique o significado de cada ocorrência de * no fragmento
    de código a seguir e indique qual a saída exibida na tela.
*/

int main(void) {
    // * como operador de declaração
    int *p, x = 5;

    // (*p) : Desreferenciação
    // (*=) : Multiplicação com atribuição
    // (* ) : Multiplicação
    // (*p) : Desreferenciação
    *p *= 2 * *p;
    
    // Saída 5
    printf("%d", x);
    getchar();
}