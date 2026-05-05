#include <iostream>
#include <conio.h>

using namespace std;

void gotoxy(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}

void clrscr() {
    cout << "\033[2J\033[1;1H";
}

/************* VARIAVEIS GLOBAIS *************/

char professor[50], disciplina[50], turma[10], resp;
int opcao, linha, col, matTemp;

struct Aluno {
    int matricula;
    char nome[50];
    float notas[3];
    Aluno *pProx;
};

Aluno inicio, *pAux, *pAnt;

/****************** FUNCAO CABECALHO ******************/

void cabecalho() {
    clrscr();
    gotoxy(3, 5);
    cout << "PROGRAMA PARA GERENCIAR MATRICULA, O NOME E AS NOTAS";
    gotoxy(3, 7);
    cout << "DE UM ALUNO USANDO UMA LISTA SIMPLESMENTE ENCADEADA\n";
}

/****************** FUNCAO MENU ******************/

void menu() {
    col = 15;
    gotoxy(col, 10);
    cout << "*************** Menu ****************";
    gotoxy(col, 11);
    cout << "* Exibir......[1] *";
    gotoxy(col, 12);
    cout << "* Inserir.....[2] *";
    gotoxy(col, 13);
    cout << "* Remover.....[3] *";
    gotoxy(col, 14);
    cout << "* Sair........[0] *";
    gotoxy(col, 15);
    cout << "* Digite a opcao: *";
    gotoxy(col, 16);
    cout << "*************************************";
    gotoxy(42, 15);
    cin >> opcao;
}

/******************** FUNCAO DIARIO *******************/

void diario() {
    gotoxy(3, 9);
    cout << "PREENCHER OS DADOS DO CABECALHO DO DIARIO";
    gotoxy(3, 11);
    cout << "Professor: ";
    cin >> professor;
    gotoxy(3, 13);
    cout << "Disciplina: ";
    cin >> disciplina;
    gotoxy(3, 15);
    cout << "Turma: ";
    cin >> turma;
}

/********************* FUNCAO EXIBIR *******************/

void exibir() {
    pAux = inicio.pProx; /* aponta para o inicio da lista */
    clrscr();
    gotoxy(1, 5);
    cout << "******************************** DIARIO *********************************";
    gotoxy(1, 7);
    cout << "Professor: " << professor;
    gotoxy(1, 8);
    cout << "Disciplina: " << disciplina;
    gotoxy(1, 9);
    cout << "Turma: " << turma;
    linha = 11;
    cout << "\n---------------------------------------------------------------------------";
    gotoxy(1, linha);
    cout << "Matricula";
    gotoxy(15, linha);
    cout << "Nome";
    gotoxy(50, linha);
    cout << "Nota1";
    gotoxy(60, linha);
    cout << "Nota2";
    gotoxy(70, linha);
    cout << "Media";
    linha = 13;
    cout << "\n---------------------------------------------------------------------------";
    while (pAux) {
        gotoxy(1, linha);
        cout << pAux->matricula;
        gotoxy(15, linha);
        cout << pAux->nome;
        gotoxy(50, linha);
        cout << pAux->notas[0];
        gotoxy(60, linha);
        cout << pAux->notas[1];
        gotoxy(70, linha);
        cout << pAux->notas[2];
        pAux = pAux->pProx;
        linha++;
    }
    cout << "\n---------------------------------------------------------------------------";
    printf("\nPressione Enter para continuar!");
    getch();
}

/********************* FUNCAO INSERIR *******************/

void inserir() {
    pAux = &inicio; /* aponta para o inicio da lista */
    while (pAux->pProx)
        pAux = pAux->pProx;
    do {
        clrscr();
        cout << "************************* CADASTRO DE ALUNO *************************";
        pAux->pProx = new(Aluno);
        pAux = pAux->pProx;
        gotoxy(1, 2);
        cout << "* Matricula: *";
        gotoxy(1, 3);
        cout << "* Nome do Aluno: *";
        gotoxy(1, 4);
        cout << "* Nota1: *";
        gotoxy(1, 5);
        cout << "* Nota2: *";
        cout << "\n*********************************************************************";
        gotoxy(20, 2);
        cin >> pAux->matricula;
        gotoxy(20, 3);
        cin >> pAux->nome;
        gotoxy(20, 4);
        cin >> pAux->notas[0];
        gotoxy(20, 5);
        cin >> pAux->notas[1];
        pAux->notas[2] = (pAux->notas[0] + pAux->notas[1]) / 2;
        pAux->pProx = NULL;
        cout << "\nContinuar inserindo dados? Sim[S] Nao[outra tecla]---->";
        resp = toupper(getch());
    } while (resp == 'S');
}

/********************* FUNCAO REMOVER *******************/

void remover() {
    resp = '0';
    clrscr();
    cout << "************************** REMOVER ALUNO ****************************";
    gotoxy(1, 2);
    cout << "* Matricula: *";
    gotoxy(1, 3);
    cout << "*********************************************************************";
    gotoxy(15, 2);
    cin >> matTemp;
    pAux = &inicio;
    while (pAux->matricula != matTemp && pAux->pProx != NULL) {
        pAnt = pAux;
        pAux = pAux->pProx;
    }
    if (pAux->matricula == matTemp) {
        gotoxy(20, 2);
        cout << "Remover " << pAux->nome << "? Sim[S] Nao[outra tecla]---->";
        resp = toupper(getch());
        if (resp == 'S') {
            pAnt->pProx = pAux->pProx;
            pAux->pProx = NULL;
            pAnt = NULL;
            delete(pAux);
        }
    } else {
        gotoxy(20, 2);
        cout << "Matricula inexistente";
        getch();
        pAnt = NULL;
        pAux = NULL;
    }
}

/****************** FUNCAO PRINCIPAL ******************/

int main() {
    inicio.pProx = NULL; /* lista vazia */
    cabecalho();
    diario();
    do {
        do {
            cabecalho();
            menu();
            if ((int)opcao < 0 || (int)opcao>3) {
                opcao = -1;
                gotoxy(50, 15);
                cout << "Opcao Invalida!";
            }
        } while (opcao == -1);
        switch (opcao) {
            case 0:
                break;
            case 1:
                exibir();
                break;
            case 2:
                inserir();
                break;
            case 3:
                remover();
                break;
            default:
                printf("\nOpcao invalida");
                getch();
        }
    } while (opcao != 0);
}
