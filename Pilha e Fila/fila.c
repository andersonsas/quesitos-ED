#include <stdio.h>
#include <stdlib.h>

// Biblioteca para a função de atraso (sleep) compatível com Windows e Linux/Mac
#ifdef _WIN32
    #include <windows.h>
    #define DELAY(ms) Sleep(ms)
#else
    #include <unistd.h>
    #define DELAY(ms) usleep((ms) * 1000)
#endif

// Estrutura que representa um pacote (Nó da Fila)
typedef struct Node {
    int id_pacote;
    int tamanho_bytes;
    struct Node* prox;
} Node;

// Estrutura da Fila
typedef struct Queue {
    Node* inicio;
    Node* fim;
    int total_pacotes;
} Queue;

// Função para inicializar a fila
void inicializarFila(Queue* q) {
    q->inicio = NULL;
    q->fim = NULL;
    q->total_pacotes = 0;
}

// Função para verificar se a fila está vazia
int filaVazia(Queue* q) {
    return (q->inicio == NULL);
}

// Função para enfileirar (inserir) um pacote
void enfileirar(Queue* q, int id, int tamanho) {
    Node* novoPacote = (Node*)malloc(sizeof(Node));
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
Node* desenfileirar(Queue* q) {
    if (filaVazia(q)) {
        return NULL;
    }
    Node* pacoteRemovido = q->inicio;
    q->inicio = q->inicio->prox;
    
    if (q->inicio == NULL) {
        q->fim = NULL;
    }
    q->total_pacotes--;
    return pacoteRemovido;
}

int main() {
    Queue filaTransmissao;
    inicializarFila(&filaTransmissao);

    int tamanho_arquivo, tamanho_max_pacote;

    printf("=== SIMULADOR DE TRANSFERENCIA DE ARQUIVOS ===\n\n");
    printf("Informe o tamanho total do arquivo (em bytes): ");
    scanf("%d", &tamanho_arquivo);
    printf("Informe o tamanho maximo de cada pacote (em bytes): ");
    scanf("%d", &tamanho_max_pacote);

    if (tamanho_arquivo <= 0 || tamanho_max_pacote <= 0) {
        printf("Valores invalidos. O tamanho deve ser maior que zero.\n");
        return 1;
    }

    // 1. Fase de Divisão e Enfileiramento
    printf("\n--- Dividindo o arquivo em pacotes ---\n");
    int bytes_restantes = tamanho_arquivo;
    int id_atual = 1;

    while (bytes_restantes > 0) {
        int tamanho_atual = (bytes_restantes > tamanho_max_pacote) ? tamanho_max_pacote : bytes_restantes;
        enfileirar(&filaTransmissao, id_atual, tamanho_atual);
        bytes_restantes -= tamanho_atual;
        id_atual++;
    }

    int total_pacotes = filaTransmissao.total_pacotes;
    printf("O arquivo de %d bytes foi dividido em %d pacote(s).\n", tamanho_arquivo, total_pacotes);
    printf("Iniciando a transmissao pelo canal de comunicacao...\n\n");
    DELAY(1500); // Pausa de 1.5 segundos antes de começar

    // 2. Fase de Transmissão (Desenfileiramento)
    int pacotes_enviados = 0;
    while (!filaVazia(&filaTransmissao)) {
        Node* pacote = desenfileirar(&filaTransmissao);
        
        // Simulação visual da transferência
        printf("[Origem] Preparando Pacote %d (%d bytes)...\n", pacote->id_pacote, pacote->tamanho_bytes);
        DELAY(800);
        
        printf("   ---> [Canal] Transportando Pacote %d...\n", pacote->id_pacote);
        DELAY(1200); // Simula o tempo de rede
        
        printf("      ---> [Destino] Pacote %d recebido com sucesso!\n\n", pacote->id_pacote);
        DELAY(500);
        
        pacotes_enviados++;
        free(pacote); // Libera a memória do pacote que já chegou
    }

    // 3. Conclusão
    printf("=== TRANSMISSAO CONCLUIDA ===\n");
    printf("Todos os %d pacotes foram transferidos com sucesso do ponto de origem ao destino.\n", pacotes_enviados);

    return 0;
}