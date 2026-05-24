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

/******************** PRINCIPAL ********************/

int main() {
    Pilha pilhaA = {}, pilhaB = {}, pilhaResultado = {};

    push(&pilhaA, 10);
    push(&pilhaB, 20);
    push(&pilhaA, 30);
    pop(&pilhaA);
    imprimir(&pilhaB);

    return 0;
}

/******************** FUNÇÕES PILHA ********************/

void push(Pilha *s, int value) {
    No *novo = malloc(sizeof(No));
    if (!novo) { printf("Falha ao Alocar"); return; }

    novo->value = value;
    novo->next = s->topo;
    s->topo = novo;
}

int pop(Pilha *s) {
    if (!s->topo) { printf("Pilha Vazia\n"); return 0; }

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
        printf("\n%d\n", aux->value);
        aux = aux->next;
    }
}
