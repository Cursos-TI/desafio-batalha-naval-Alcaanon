#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

// === Definições de constantes para o tabuleiro e navios ===
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AGUA 0

// === Função para inicializar o tabuleiro com água (valor 0) ===
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// === Função para exibir o tabuleiro formatado no console com colunas de A a J ===
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");  // Espaço inicial para alinhar com os números das linhas

    // === Cabeçalho das colunas com letras de A a J ===
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    // === Impressão do conteúdo da matriz linha por linha ===
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);  // Número da linha

        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);  // 0 = água | 3 = navio
        }
        printf("\n");
    }
}

// === Função para posicionar um navio horizontalmente ===
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;  // Valida se o navio cabe na linha

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != AGUA)
            return 0; // Verifica se não há sobreposição
    }

    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
        printf("Navio horizontal: (%d, %c)\n", linha, 'A' + coluna + i);
    }

    return 1;
}

// === Função para posicionar um navio verticalmente ===
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;  // Valida se o navio cabe na coluna

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != AGUA)
            return 0; // Verifica se não há sobreposição
    }

    // Posiciona o navio
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
        printf("Navio vertical: (%d, %c)\n", linha + i, 'A' + coluna);
    }

    return 1;
}

int main() {

    // === Início do programa ===
    printf("=== BATALHA NAVAL - INICIO ===\n");

    // === Declaração do tabuleiro 10x10 ===
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // === Coordenadas iniciais definidas diretamente no código ===
    int linhaH = 2, colunaH = 4;  // Exemplo: linha 2, coluna E
    int linhaV = 5, colunaV = 7;  // Exemplo: linha 5, coluna H

    // === Inicializa o tabuleiro com água (0) ===
    inicializarTabuleiro(tabuleiro);

    // === Posiciona o navio horizontal com validação ===
    if (!posicionarNavioHorizontal(tabuleiro, linhaH, colunaH)) {
        printf("Erro ao posicionar navio horizontal!\n");
        return 1;
    }

    // === Posiciona o navio vertical com validação ===
    if (!posicionarNavioVertical(tabuleiro, linhaV, colunaV)) {
        printf("Erro ao posicionar navio vertical!\n");
        return 1;
    }

    // === Exibe o tabuleiro final com os navios posicionados ===
    printf("\n=== TABULEIRO FINAL ===\n");
    exibirTabuleiro(tabuleiro);

    // === Fim do programa ===
    printf("\n=== BATALHA NAVAL - FIM ===\n");

    return 0;
}
// === FIM DO PROGRAMA ===