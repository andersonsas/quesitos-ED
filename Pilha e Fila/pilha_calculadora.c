#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

/******************** ESTRUTURAS ********************/

typedef struct no {
    int value;
    struct no *next;
} No;

typedef struct pilha {
    No *topo;
} Pilha;

/******************** GLOBAIS ********************/
COORD CursorPosition;
Pilha pilhaA = {}, pilhaB = {}, pilhaResultado = {};

/******************** PROTÓTIPO ********************/

void menu();
void gotoXY(int, int);
void push(Pilha *s, int i);
int pop(Pilha *s);
bool isEmpty(Pilha *s);
void clear(Pilha *s);
int lerTopo(Pilha *s);
void imprimir(Pilha *s);
void empilharDigitos(Pilha *s, int i);
void interfaceMenu();
void interfaceSomar();
void somar();

/******************** PRINCIPAL ********************/

int main() {
    menu();

    return 0;
}

void menu() {
    int option;

    do {
        interfaceMenu();
        scanf("%d", &option);
        switch (option) {
            case 1:
                somar();
                break;
            case 0:
                clear(&pilhaA);
                clear(&pilhaB);
                clear(&pilhaResultado);
                break;
            default:
                break;
        }
    } while (option);
    puts(""); system("pause");
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

int lerTopo(Pilha *s) {
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

void empilharDigitos(Pilha *s, int valor) {
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

/******************** INTERFACES ********************/

void somar() {
    system("cls");
    interfaceSomar();
    Pilha *A = &pilhaA, *B = &pilhaB, *R = &pilhaResultado;
    int num1, num2;

    gotoXY(35, 5); scanf("%d", &num1);
    gotoXY(35, 6); scanf("%d", &num2);

    empilharDigitos(A, num1);
    empilharDigitos(B, num2);

    int vai_um = 0;
    while (A->topo != NULL || B->topo != NULL || vai_um > 0) {
        int digito1 = pop(A);
        int digito2 = pop(B);
        int soma = digito1 + digito2 + vai_um;

        push(R, soma % 10);
        vai_um = soma / 10;
    }

    gotoXY(35, 7);
    while (!isEmpty(R)) {
        printf("%d", pop(R));
    }
    getchar(); gotoXY(15, 10); system("pause");
}

/******************** INTERFACES ********************/

void interfaceMenu() {
    int col = 15; system("cls");
    gotoXY(col, 4); printf("+ ---------------- MENU -------------- +");
    gotoXY(col, 5); printf("|      Somar dois numeros....[1]       |");
    gotoXY(col, 6); printf("|      Sair..................[0]       |");
    gotoXY(col, 7); printf("|      Digite a opcao:                 |");
    gotoXY(col, 8); printf("+ ------------------------------------ +");
    gotoXY(45, 7);
}

void interfaceSomar() {
    int col = 15; system("cls");
    gotoXY(col, 4); printf("+ ----- SOMA DE INTEIRO COM PILHA ----- +");
    gotoXY(col, 5); printf("|      Numero A  :                      |");
    gotoXY(col, 6); printf("|      Numero B  :                      |");
    gotoXY(col, 7); printf("|      Resultado :                      |");
    gotoXY(col, 8); printf("+ ------------------------------------- +");
}

void gotoXY(int x, int y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}