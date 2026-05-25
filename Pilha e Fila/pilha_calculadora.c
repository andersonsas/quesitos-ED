#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/******************** ESTRUTURAS ********************/

typedef struct no {
    int value;
    struct no *next;
} No;

typedef struct pilha {
    No *topo;
} Pilha;

/******************** PROTÓTIPO ********************/

void push(Pilha *s, int i);
int pop(Pilha *s);
bool isEmpty(Pilha *s);
void clear(Pilha *s);
int ler_topo(Pilha *s);
void imprimir(Pilha *s);
void empilhar_digitos(Pilha *s, int i);

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

    clear(&pilhaA);
    clear(&pilhaB);
    clear(&pilhaResultado);
    puts(""); system("pause");
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
    if (isEmpty(s))  return 0;

    No *aux = s->topo;
    int value = s->topo->value;
    s->topo = s->topo->next;
    free(aux);

    return value;
}

bool isEmpty(Pilha *s) {
    return s->topo == NULL;
}

void clear(Pilha *s) {
    while (!isEmpty(s)) {
        pop(s);
    }
}

int ler_topo(Pilha *s) {
    if (isEmpty(s)) return -1;
    return s->topo->value;
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
