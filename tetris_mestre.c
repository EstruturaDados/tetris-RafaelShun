/*
-------------------------------------------------------------------------------
--- Tetris Stack: Fila de Peças Futuras (Nível Mestre) ---
-------------------------------------------------------------------------------
Requisitos principais:
- Fila circular de 10 peças futuras (MAX_PEÇAS_MESTRE = 10)
- Permite visualizar as próximas 10 peças
- Permite trocar a ordem de duas peças na fila
- Permite remover qualquer peça da fila (não só a da frente)
- Permite inserir uma peça de tipo específico (escolhido pelo usuário)
- Histórico das peças jogadas
- Menu com as novas opções
-------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// -----------------------------------------------------------------------------
// --- Constantes Globais ---
// -----------------------------------------------------------------------------
#define MAX_PEÇAS_MESTRE 10 // Fila de 10 elementos
#define TAM_TIPO 2 // Tamanho de 2 para o char e o terminador nulo
#define MAX_HISTORICO 100 // Histórico de até 100 peças jogadas

// -----------------------------------------------------------------------------
// --- Structs ---
// -----------------------------------------------------------------------------
typedef struct {
    char nome; // Tipo da peça ('I', 'O', 'T', 'L', etc.)
    int id;    // Identificador numérico único
} Peca;

// -----------------------------------------------------------------------------
// --- Variáveis Globais ---
// -----------------------------------------------------------------------------
Peca fila[MAX_PEÇAS_MESTRE]; // Fila circular
int frente = 0;
int fim = 0;
int contador_pecas = 0;
int proximo_id = 0;

Peca historico[MAX_HISTORICO]; // Histórico de peças jogadas
int contador_historico = 0;

// -----------------------------------------------------------------------------
// --- Protótipos das Funções ---
// -----------------------------------------------------------------------------
void limparBufferEntrada();
void gerarPeca(Peca *novaPeca);
void inicializarFila();
void exibirFila();
void exibirHistorico();
void jogarPeca();
void inserirPeca();
void inserirPecaTipo();
void trocarPecas();
void removerPecaPosicao();
int menuAcoes();

// -----------------------------------------------------------------------------
// --- Função Principal (main) ---
// -----------------------------------------------------------------------------
int main() {
    int opcao;
    srand(time(NULL));
    inicializarFila();
    printf("--- Tetris Stack: Fila de Peças Futuras (Nível Mestre) ---\n");
    do {
        exibirFila();
        exibirHistorico();
        opcao = menuAcoes();
        switch (opcao) {
            case 1:
                jogarPeca();
                break;
            case 2:
                inserirPeca();
                break;
            case 3:
                inserirPecaTipo();
                break;
            case 4:
                trocarPecas();
                break;
            case 5:
                removerPecaPosicao();
                break;
            case 0:
                printf("\nSaindo do sistema de controle de peças (Mestre).\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
                limparBufferEntrada();
                break;
        }
    } while (opcao != 0);
    return 0;
}

// -----------------------------------------------------------------------------
// --- Implementação das Funções ---
// -----------------------------------------------------------------------------

void gerarPeca(Peca *novaPeca) {
    const char tipos[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    int indiceAleatorio = rand() % (sizeof(tipos) / sizeof(char));
    novaPeca->nome = tipos[indiceAleatorio];
    novaPeca->id = proximo_id++;
}

void inicializarFila() {
    printf("Configurando a fila de peças futuras (Mestre)...\n");
    for (int i = 0; i < MAX_PEÇAS_MESTRE; i++) {
        Peca novaPeca;
        gerarPeca(&novaPeca);
        fila[fim] = novaPeca;
        fim = (fim + 1) % MAX_PEÇAS_MESTRE;
        contador_pecas++;
    }
}

void exibirFila() {
    printf("\n--- VISUALIZAÇÃO DA FILA DE PEÇAS FUTURAS (Mestre) ---\n");
    printf("Capacidade Máxima: %d | Peças Atuais: %d\n", MAX_PEÇAS_MESTRE, contador_pecas);
    if (contador_pecas == 0) {
        printf("Fila vazia.\n");
        return;
    }
    printf("Fila: [FRENTE] -> ");
    int i = frente;
    int elementos_exibidos = 0;
    while (elementos_exibidos < contador_pecas) {
        printf("[%c %d]", fila[i].nome, fila[i].id);
        i = (i + 1) % MAX_PEÇAS_MESTRE;
        elementos_exibidos++;
        if (elementos_exibidos < contador_pecas) {
            printf(" -> ");
        }
    }
    printf(" <- [FIM]\n");
}

void exibirHistorico() {
    printf("\n--- HISTÓRICO DE PEÇAS JOGADAS ---\n");
    if (contador_historico == 0) {
        printf("Nenhuma peça jogada ainda.\n");
        return;
    }
    printf("Peças jogadas: ");
    for (int i = 0; i < contador_historico; i++) {
        printf("[%c %d]", historico[i].nome, historico[i].id);
        if (i < contador_historico - 1) printf(" -> ");
    }
    printf("\n");
}

void jogarPeca() {
    if (contador_pecas == 0) {
        printf("\nERRO: A fila está vazia. Não há peça para jogar.\n");
        return;
    }
    Peca pecaJogada = fila[frente];
    frente = (frente + 1) % MAX_PEÇAS_MESTRE;
    contador_pecas--;
    if (contador_historico < MAX_HISTORICO) {
        historico[contador_historico++] = pecaJogada;
    }
    printf("\n[JOGADA] Peça de tipo '%c' (ID %d) removida e jogada.\n", pecaJogada.nome, pecaJogada.id);
}

void inserirPeca() {
    if (contador_pecas == MAX_PEÇAS_MESTRE) {
        printf("\nERRO: A fila está cheia. Jogue uma peça antes de inserir.\n");
        return;
    }
    Peca novaPeca;
    gerarPeca(&novaPeca);
    fila[fim] = novaPeca;
    fim = (fim + 1) % MAX_PEÇAS_MESTRE;
    contador_pecas++;
    printf("\n[INSERÇÃO] Nova peça de tipo '%c' (ID %d) adicionada ao final da fila.\n", novaPeca.nome, novaPeca.id);
}

void inserirPecaTipo() {
    if (contador_pecas == MAX_PEÇAS_MESTRE) {
        printf("\nERRO: A fila está cheia. Jogue uma peça antes de inserir.\n");
        return;
    }
    char tipo;
    printf("Digite o tipo da peça ('I', 'O', 'T', 'L', 'J', 'S', 'Z'): ");
    limparBufferEntrada();
    scanf(" %c", &tipo);
    Peca novaPeca;
    novaPeca.nome = tipo;
    novaPeca.id = proximo_id++;
    fila[fim] = novaPeca;
    fim = (fim + 1) % MAX_PEÇAS_MESTRE;
    contador_pecas++;
    printf("\n[INSERÇÃO] Nova peça de tipo '%c' (ID %d) adicionada ao final da fila.\n", novaPeca.nome, novaPeca.id);
}

void trocarPecas() {
    if (contador_pecas < 2) {
        printf("\nERRO: É necessário pelo menos 2 peças para trocar.\n");
        return;
    }
    int pos1, pos2;
    printf("Digite as posições das peças para trocar (1 a %d): ", contador_pecas);
    if (scanf("%d %d", &pos1, &pos2) != 2 || pos1 < 1 || pos2 < 1 || pos1 > contador_pecas || pos2 > contador_pecas) {
        printf("\nPosições inválidas.\n");
        limparBufferEntrada();
        return;
    }
    int idx1 = (frente + pos1 - 1) % MAX_PEÇAS_MESTRE;
    int idx2 = (frente + pos2 - 1) % MAX_PEÇAS_MESTRE;
    Peca temp = fila[idx1];
    fila[idx1] = fila[idx2];
    fila[idx2] = temp;
    printf("\n[TROCA] Peças nas posições %d e %d trocadas.\n", pos1, pos2);
}

void removerPecaPosicao() {
    if (contador_pecas == 0) {
        printf("\nERRO: A fila está vazia.\n");
        return;
    }
    int pos;
    printf("Digite a posição da peça para remover (1 a %d): ", contador_pecas);
    if (scanf("%d", &pos) != 1 || pos < 1 || pos > contador_pecas) {
        printf("\nPosição inválida.\n");
        limparBufferEntrada();
        return;
    }
    int idx = (frente + pos - 1) % MAX_PEÇAS_MESTRE;
    Peca pecaRemovida = fila[idx];
    // Desloca as peças para preencher o espaço
    for (int i = idx; i != fim; i = (i + 1) % MAX_PEÇAS_MESTRE) {
        int next = (i + 1) % MAX_PEÇAS_MESTRE;
        fila[i] = fila[next];
        if (next == fim) break;
    }
    fim = (fim - 1 + MAX_PEÇAS_MESTRE) % MAX_PEÇAS_MESTRE;
    contador_pecas--;
    if (contador_historico < MAX_HISTORICO) {
        historico[contador_historico++] = pecaRemovida;
    }
    printf("\n[REMOÇÃO] Peça de tipo '%c' (ID %d) removida da posição %d.\n", pecaRemovida.nome, pecaRemovida.id, pos);
}

int menuAcoes() {
    int opcao;
    printf("\nOpções de ação (Mestre):\n");
    printf("1. Jogar peça (dequeue)\n");
    printf("2. Inserir nova peça (enqueue aleatório)\n");
    printf("3. Inserir peça de tipo específico\n");
    printf("4. Trocar ordem de duas peças\n");
    printf("5. Remover peça de qualquer posição\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    if (scanf("%d", &opcao) != 1) {
        return -1;
    }
    return opcao;
}

void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
