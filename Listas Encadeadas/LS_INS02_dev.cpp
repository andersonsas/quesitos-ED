/* Prof.: Sergio Augusto C. Bezerra

   Programa MODULADO "LS_INS02_dev.CPP" para exemplificar uma lista simplesmente encadeada
*/

#include <stdio.h>
#include <new>    //<alloc.h>
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <windows.h>

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
void gotoXY(int x, int y);
/****************** VARIAVEIS GLOBAIS ******************/

char professor[50], disciplina[50], turma[10];
int opcao;
char resp;
int linha, col, matTemp;

struct Aluno {
    int matricula;   /* numeros de 1 a no maximo 40 */
    char nome[50];
    float notas[3];  /* valores das notas */
    struct Aluno *pProximo; /* ponteiro para o proximo aluno */
    struct Aluno *pAnterior;
};

Aluno inicio, *pAux;

/****************** FUNCAO CABECALHO ******************/
void cabecalho() {
    system("cls");
    gotoXY(3, 5);
    cout << "PROGRAMA PARA GERENCIAR A MATRICULA, O NOME E AS NOTAS";
    gotoXY(3, 7);
    cout << "DE UM ALUNO USANDO UMA LISTA SIMPLESMENTE ENCADEADA\n";
}

/****************** FUNCAO MENU ******************/
void menu() {
    col = 15;
    gotoXY(col, 10);
    cout << "*************** Menu ****************";
    gotoXY(col, 11);
    cout << "*      Exibir.............[1]       *";
    gotoXY(col, 12);
    cout << "*      Inserir............[2]       *";
    gotoXY(col, 13);
    cout << "*      Remover............[3]       *";
    gotoXY(col, 14);
    cout << "*      Inserir em Ordem...[4]       *";
    gotoXY(col, 15);
    cout << "*      Sair...............[0]       *";
    gotoXY(col, 16);
    cout << "*      Digite a opcao:              *";
    gotoXY(col, 17);
    cout << "*************************************";
    gotoXY(42, 16);
    cin >> opcao;
}

/******************** FUNCAO DIARIO *******************/
void diario() {
    gotoXY(3, 9);
    cout << "PREENCHER OS DADOS DO CABECALHO DO DIARIO";
    gotoXY(3, 11);
    cout << "Professor: ";
    fgets(professor, 99, stdin);
    gotoXY(3, 13);
    cout << "Disciplina: ";
    fgets(disciplina, 99, stdin);
    gotoXY(3, 15);
    cout << "Turma: ";
    fgets(turma, 99, stdin);

}


/********************* FUNCAO EXIBIR *******************/
void exibir() {
    if (inicio.pProximo != NULL) {
        pAux = inicio.pProximo; /* aponta para o inicio da lista */
        system("cls");
        gotoXY(1, 5);
        cout << "********************************  DIARIO *********************************";
        gotoXY(1, 7);
        cout << "Professor: " << professor;
        gotoXY(1, 8);
        cout << "Disciplina: " << disciplina;
        gotoXY(1, 9);
        cout << "Turma: " << turma;
        linha = 12;
        cout << "\n---------------------------------------------------------------------------";
        gotoXY(1, linha);
        cout << "Matricula";
        gotoXY(15, linha);
        cout << "Nome";
        gotoXY(50, linha);
        cout << "Nota1";
        gotoXY(60, linha);
        cout << "Nota2";
        gotoXY(70, linha);
        cout << "Media";
        linha = 14;
        cout << "\n---------------------------------------------------------------------------";
        while (pAux) {
            gotoXY(1, linha);
            cout << pAux->matricula;
            gotoXY(15, linha);
            cout << pAux->nome;
            gotoXY(50, linha);
            cout << pAux->notas[0];
            gotoXY(60, linha);
            cout << pAux->notas[1];
            gotoXY(70, linha);
            cout << pAux->notas[2];
            pAux = pAux->pProximo;
            linha++;
        }
        cout << "\n---------------------------------------------------------------------------\n";
        system("pause");
    } else {
        gotoXY(15, 18);
        cout << "ATENCAO: Alunos inexistentes! ";
        system("pause");
    }
}

/********************* FUNCAO INSERIR *******************/

void inserir() {
    Aluno *novo = new Aluno;

    pAux = &inicio; /* aponta para o inicio da lista */
    novo->pProximo = NULL;

    if (pAux->pProximo == NULL) { // se lista vazia
        pAux->pProximo = novo;
        pAux->pProximo->pAnterior = pAux;
    } else {
        while (pAux->pProximo) {
            pAux = pAux->pProximo;
        }
        pAux->pProximo = novo;
        novo->pAnterior = pAux;
    }
    pAux = novo;

    do {
        system("cls");
        cout << "************************* CADASTRO DE ALUNO *************************";
        //pAux->pProximo = new Aluno;
        //pAux = pAux->pProximo;
        gotoXY(1, 2);
        cout << "*  Matricula:                                                       *";
        gotoXY(1, 3);
        printf("*  Nome do Aluno:                                                   *");
        gotoXY(1, 4);
        cout << "*  Nota1:                                                           *";
        gotoXY(1, 5);
        cout << "*  Nota2:                                                           *";
        cout << "\n*********************************************************************";
        gotoXY(20, 2);
        cin >> pAux->matricula; getchar();
        gotoXY(20, 3);
        fflush(stdin);
        fgets(pAux->nome, 99, stdin);
        gotoXY(20, 4);
        cin >> pAux->notas[0];
        gotoXY(20, 5);
        cin >> pAux->notas[1];
        pAux->notas[2] = (pAux->notas[0] + pAux->notas[1]) / 2;

        cout << "\nContinuar inserindo dados? Sim[S] Nao[outra tecla]---->";
        cin >> resp;
        resp = toupper(resp);
    } while (resp == 'S');
}
/********************* FUNCAO REMOVER *******************/


/*
void remover() {
    do {
        resp = '0';
        system("cls");
        cout << "************************** REMOVER ALUNO ****************************";
        gotoXY(1, 2);
        cout << "*  Matricula:                                                       *";
        gotoXY(1, 3);
        cout << "*********************************************************************";
        gotoXY(15, 2);
        cin >> matTemp;
        pAux = &inicio;
        while (pAux->matricula != matTemp && pAux->pProx != NULL) {
            pAnt = pAux;
            pAux = pAux->pProx;
        }
        if (pAux->matricula == matTemp) {
            gotoXY(3, 5);
            cout << "ATENCAO: Remover " << pAux->nome << "? Sim[S] Nao[outra tecla]---->";
            cin >> resp;
            resp = toupper(resp);
            if (resp == 'S') {
                pAnt->pProx = pAux->pProx;
                pAux->pProx = NULL;
                pAnt = NULL;
                delete pAux;
            }
        } else {
            gotoXY(20, 2);
            cout << "Matricula inexistente";
            system("pause");
            pAnt = NULL;
            pAux = NULL;
        }
        gotoXY(3, 6);
        cout << "Continuar removendo dados? Sim[S] Nao[outra tecla]---->";
        cin >> resp;
        resp = toupper(resp);
    } while (resp == 'S');
}*/

/********************* FUNCAO INSERIR EM ORDEM *******************/
void inserirOrdem() {
    Aluno *pMenor, *pMaior;

    do {
        pMaior = &inicio; /* aponta para o inicio da lista */
        pMenor = pMaior;
        system("cls");
        cout << "************************* CADASTRO DE ALUNO *************************";
        pAux = new Aluno;
        gotoXY(1, 2);
        cout << "*  Matricula:                                                       *";
        gotoXY(1, 3);
        printf("*  Nome do Aluno:                                                   *");
        gotoXY(1, 4);
        cout << "*  Nota1:                                                           *";
        gotoXY(1, 5);
        cout << "*  Nota2:                                                           *";
        cout << "\n*********************************************************************";
        gotoXY(20, 2);
        cin >> pAux->matricula; getchar();
        gotoXY(20, 3);
        fflush(stdin);
        fgets(pAux->nome, 99, stdin);
        gotoXY(20, 4);
        cin >> pAux->notas[0];
        gotoXY(20, 5);
        cin >> pAux->notas[1];
        pAux->notas[2] = (pAux->notas[0] + pAux->notas[1]) / 2;
        pAux->pProximo = NULL;
        if (pMaior->pProximo == NULL) {
            pMaior->pProximo = pAux;
            pAux->pProximo = NULL;
        } else {
            pMaior = pMaior->pProximo;
            while (pAux->matricula > pMaior->matricula && pMaior->pProximo != NULL) {
                pMenor = pMaior;
                pMaior = pMaior->pProximo;
            }
            if (pAux->matricula > pMaior->matricula && pMaior->pProximo == NULL) {
                pMaior->pProximo = pAux;
                pAux->pProximo = NULL;
            } else {
                pMenor->pProximo = pAux;
                pAux->pProximo = pMaior;
            }
        }
        cout << "\nContinuar inserindo dados? Sim[S] Nao[outra tecla]---->";
        cin >> resp;
        resp = toupper(resp);
    } while (resp == 'S');
}

void gotoXY(int x, int y) {
    CursorPosition.X = x; // Locates column
    CursorPosition.Y = y; // Locates Row
    SetConsoleCursorPosition(console, CursorPosition); // Sets position for next thing to be printed
}


/****************** FUNCAO PRINCIPAL ******************/
int main() {

    int cont_tela = 1;

    inicio.pProximo = NULL; /* lista vazia */

    cabecalho();
    diario();
    cont_tela++;

    do {

        if (cont_tela > 1) {
            cabecalho();
            menu();
        }
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
                /* remover();
                break; */
            case 4:
                inserirOrdem();
                break;
            default:
                gotoXY(15, 18);
                cout << "ATENCAO: Opcao Invalida! ";
                system("pause");
        }

    } while (opcao != 0);

    return 0;
}
