#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define DELAY(ms) Sleep(ms)

// --- FUNÇÕES DE MANIPULAÇÃO DO CONSOLE ---

COORD CursorPosition;

void gotoXY(int x, int y) {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

// Esconde o cursor piscante para a animação ficar limpa
void esconderCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(console, &info);
}

// --- ESTRUTURAS DE DADOS (FILA) ---

// Estrutura que representa um pacote (Nó da Fila)
typedef struct Node {
    int id_pacote;
    int tamanho_bytes;
    struct Node *prox;
} Node;

// Estrutura da Fila
typedef struct Queue {
    Node *inicio;
    Node *fim;
    int total_pacotes;
} Queue;

// Função para inicializar a fila
void inicializarFila(Queue *q) {
    q->inicio = NULL;
    q->fim = NULL;
    q->total_pacotes = 0;
}

// Função para verificar se a fila está vazia
int filaVazia(Queue *q) {
    return (q->inicio == NULL);
}

// Função para enfileirar (inserir) um pacote
void enfileirar(Queue *q, int id, int tamanho) {
    Node *novoPacote = (Node *)malloc(sizeof(Node));
    if (novoPacote == NULL) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    novoPacote->id_pacote = id;
    novoPacote->tamanho_bytes = tamanho;
    novoPacote->prox = NULL;

    if (filaVazia(q)) {
        q->inicio = novoPacote;
    } else {
        q->fim->prox = novoPacote;
    }
    q->fim = novoPacote;
    q->total_pacotes++;
}

// Função para desenfileirar (remover) um pacote
Node *desenfileirar(Queue *q) {
    if (filaVazia(q)) {
        return NULL;
    }
    Node *pacoteRemovido = q->inicio;
    q->inicio = q->inicio->prox;

    if (q->inicio == NULL) {
        q->fim = NULL;
    }
    q->total_pacotes--;
    return pacoteRemovido;
}

// --- LÓGICA DE DESENHO VISUAL ---

// Desenha a fila de pacotes graficamente.
// direction = -1 (cresce para a esquerda, ex: Origem)
// direction = 1 (cresce para a direita, ex: Destino)
void desenharFila(Queue *q, int startX, int y, int direction) {
    Node *atual = q->inicio;
    int x = startX;

    // Limpa a área antes de redesenhar para evitar "fantasmas"
    // Limitado a 7 blocos para caber na tela padrão de 80 colunas
    for (int i = 0; i < 7; i++) {
        gotoXY(startX + (i * direction * 5), y);
        printf("    ");
    }

    int count = 0;
    while (atual != NULL && count < 7) {
        gotoXY(x, y);
        printf("[%02d]", atual->id_pacote);
        x += direction * 5; // Espaçamento de 5 colunas entre pacotes
        atual = atual->prox;
        count++;
    }
}

// --- FUNÇÃO PRINCIPAL ---

int main() {
    Queue filaOrigem, filaDestino;
    inicializarFila(&filaOrigem);
    inicializarFila(&filaDestino);

    int tamanho_arquivo, tamanho_max;

    printf("=== SIMULADOR DE REDE VISUAL ===\n\n");
    printf("Tamanho do arquivo (bytes): ");
    scanf("%d", &tamanho_arquivo);
    printf("Tamanho max. do pacote (bytes): ");
    scanf("%d", &tamanho_max);

    if (tamanho_arquivo <= 0 || tamanho_max <= 0) return 1;

    // Enfileira todos os pacotes na Origem
    int bytes_restantes = tamanho_arquivo;
    int id = 1;
    while (bytes_restantes > 0) {
        int tam_atual = (bytes_restantes > tamanho_max) ? tamanho_max : bytes_restantes;
        enfileirar(&filaOrigem, id, tam_atual);
        bytes_restantes -= tam_atual;
        id++;
    }

    system("cls"); // Limpa a tela para começar a animação

    // Coordenadas base do layout
    int y_animacao = 10;
    int startX_origem = 30; // Frente da fila de origem
    int startX_canal = 35;  // Início do movimento no canal
    int endX_canal = 60;    // Fim do movimento no canal
    int startX_destino = 65;// Frente da fila de destino

    //esconderCursor();
    // Desenha o cabeçalho fixo
    gotoXY(15, 6); printf("=== TRANSMISSAO EM ANDAMENTO ===");
    gotoXY(18, 8); printf("ORIGEM");
    gotoXY(45, 8); printf("CANAL");
    gotoXY(70, 8); printf("DESTINO");

    // Desenha o estado inicial
    desenharFila(&filaOrigem, startX_origem, y_animacao, -1);
    desenharFila(&filaDestino, startX_destino, y_animacao, 1);
    Sleep(1500); // Pausa dramática antes de começar

    // Fase de Transporte Visuais
    while (!filaVazia(&filaOrigem)) {
        // 1. Remove da Origem e atualiza a tela
        Node *pacote = desenfileirar(&filaOrigem);
        desenharFila(&filaOrigem, startX_origem, y_animacao, -1);

        // 2. Animação de deslocamento do pacote
        for (int cx = startX_canal; cx <= endX_canal; cx++) {
            if (cx > startX_canal) {
                gotoXY(cx - 1, y_animacao);
                printf(" "); // Apaga o rastro anterior do pacote
            }
            gotoXY(cx, y_animacao);
            printf("[%02d]", pacote->id_pacote); // Desenha nova posição
            Sleep(40); // Velocidade do pacote
        }

        // Apaga o pacote do final do canal
        gotoXY(endX_canal, y_animacao);
        printf("    ");

        // 3. Adiciona no Destino e atualiza a tela
        enfileirar(&filaDestino, pacote->id_pacote, pacote->tamanho_bytes);
        desenharFila(&filaDestino, startX_destino, y_animacao, 1);

        free(pacote); // Libera o nó temporário usado no transporte
    }

    // Fim
    gotoXY(15, 14);
    printf("=== TRANSFERENCIA CONCLUIDA! TODOS OS PACOTES ENTREGUES. ===\n\n");

    return 0;
}
