#include <iostream>
#include <ctype.h>
#include <conio.h>
using namespace std;

void gotoxy(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

void clrscr() {
    cout << "\033[2J\033[1;1H";
}

struct Aluno {
    int matricula;
    char nome[50];
    float nota1, nota2, media;
    Aluno *pProx;
};

/************* VARIAVEIS GLOBAIS *************/

char resp; int opcao, linha, col, matr_temp;
Aluno inicio, *pAux;

/************* FUNCAO PRINCIPAL *************/

int main() {

    /*** Inicio da lista ***/
    inicio.pProx = NULL;
    pAux = &inicio;

    do {
        clrscr();
        pAux->pProx = new Aluno();
        pAux = pAux->pProx;
        gotoxy(3, 5);
        cout << "PROGRAMA PARA GERENCIAR A MATRICULA, O NOME E AS NOTAS DE ";
        cout << "\n   UM ALUNO USANDO UMA LISTA SIMPLESMENTE ENCADEADA\n";

        cout << "\nMatricula: ";
        cin >> pAux->matricula;

        cout << "\nNome do Aluno: ";
        cin >> pAux->nome;

        cout << "\nNota 1: ";
        cin >> pAux->nota1;

        cout << "\nNota 2: ";
        cin >> pAux->nota2;

        pAux->media = (pAux->nota1 + pAux->nota2) / 2;
        pAux->pProx = NULL;

        cout << "Deseja continuar? Sim[S] ou Nao[N]";
        resp = toupper(getch());

    } while (resp == 'S' || resp == 's');

    /* Exibindo as notas da lista */
    clrscr();
    pAux = inicio.pProx;
    gotoxy(1, 10);
    cout << "Matricula";
    gotoxy(15, 10);
    cout << "Nome";
    gotoxy(50, 10);
    cout << "Nota1";
    gotoxy(60, 10);
    cout << "Nota2";
    gotoxy(70, 10);
    cout << "Media";
    linha = 12;
    while (pAux) {
        gotoxy(1, linha);
        cout << pAux->matricula;
        gotoxy(15, linha);
        cout << pAux->nome;
        gotoxy(50, linha);
        cout << pAux->nota1;
        gotoxy(60, linha);
        cout << pAux->nota2;
        gotoxy(70, linha);
        cout << pAux->media;
        pAux = pAux->pProx;
        linha++;
    }
    getchar();
    printf("\n\nPressione uma tecla para terminar >>>>");
    getchar();

    return 0;
}
