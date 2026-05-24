#include <stdio.h>
#include <stdlib.h>

/******************** ESTRUTURAS ********************/

typedef struct no {
    int value;
    struct no *next;
} No;

typedef struct pilha {
    No *topo;
} Pilha;

/******************** PROTÓTIPO ********************/

void push(Pilha *, int);
int pop(Pilha *);
void imprimir(Pilha *);
void empilhar_digitos(Pilha *, int);

/******************** PRINCIPAL ********************/

int main() {
    Pilha pilhaA = {}, pilhaB = {}, pilhaResultado = {};

    int digito1, digito2;
    puts("Digite dois numeros inteiros.");
    scanf("%d", &digito1);
    scanf("%d", &digito2);

    empilhar_digitos(&pilhaA, digito1);
    empilhar_digitos(&pilhaB, digito2);

    printf("%d", digito1);
    printf(" + ");
    printf("%d", digito2);
    printf(" = ");

    int vai_um = 0;
    while (pilhaA.topo != NULL || pilhaB.topo != NULL || vai_um > 0) {
        int digito1 = pop(&pilhaA);
        int digito2 = pop(&pilhaB);
        int soma = digito1 + digito2 + vai_um;

        push(&pilhaResultado, soma % 10);
        vai_um = soma / 10;
    }

    imprimir(&pilhaResultado);
    return 0;
}

/******************** FUNÇÕES PILHA ********************/

void push(Pilha *s, int value) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) { printf("Falha ao Alocar"); return; }

    novo->value = value;
    novo->next = s->topo;
    s->topo = novo;
}

int pop(Pilha *s) {
    if (!s->topo) { return 0; }

    No *aux = s->topo;
    int value = s->topo->value;
    s->topo = s->topo->next;
    free(aux);

    return value;
}

void imprimir(Pilha *s) {
    No *aux = s->topo;
    if (!aux) { printf("Pilha Vazia"); return; }

    while (aux) {
        printf("%d", aux->value);
        aux = aux->next;
    }
}

void empilhar_digitos(Pilha *s, int valor) {
    if (valor == 0) {
        push(s, 0);
        return;
    }
    char num_str[16];
    itoa(valor, num_str, 10);

    for (int i = 0; num_str[i] != '\0'; i++) {
        push(s, num_str[i] - '0');
    }
}
