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

// === Função para exibir o tabuleiro com colunas de A a J ===
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%c ", 'A' + i);
    }
    printf("\n");

    // === Impressão do conteúdo da matriz linha por linha ===
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// === Posiciona navio horizontalmente com validação ===
int posicionarNavioHorizontal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (tabuleiro[linha][coluna + i] != AGUA) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha][coluna + i] = NAVIO;
        printf("Navio horizontal: (%d, %c)\n", linha, 'A' + coluna + i);
    }
    return 1;
}

// === Posiciona navio verticalmente com validação ===
int posicionarNavioVertical(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (tabuleiro[linha + i][coluna] != AGUA) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna] = NAVIO;
        printf("Navio vertical: (%d, %c)\n", linha + i, 'A' + coluna);
    }
    return 1;
}

// === Posiciona navio em diagonal principal (↘) ===
int posicionarNavioDiagonalPrincipal(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna + TAMANHO_NAVIO > TAMANHO_TABULEIRO) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (tabuleiro[linha + i][coluna + i] != AGUA) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna + i] = NAVIO;
        printf("Navio diagonal: (%d, %c)\n", linha + i, 'A' + coluna + i);
    }
    return 1;
}

// === Posiciona navio em diagonal secundária (↙) ===
int posicionarNavioDiagonalSecundaria(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna) {
    if (linha + TAMANHO_NAVIO > TAMANHO_TABULEIRO || coluna - (TAMANHO_NAVIO - 1) < 0) return 0;
    for (int i = 0; i < TAMANHO_NAVIO; i++)
        if (tabuleiro[linha + i][coluna - i] != AGUA) return 0;

    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        tabuleiro[linha + i][coluna - i] = NAVIO;
        printf("Navio diagonal: (%d, %c)\n", linha + i, 'A' + (coluna - i));
    }
    return 1;
}

int main() {
    // === Início do programa ===
    printf("=== BATALHA NAVAL - INICIO ===\n");

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // === Coordenadas fixas dos quatro navios ===
    int linhaH = 2, colunaH = 1;
    int linhaV = 5, colunaV = 4;
    int linhaD1 = 3, colunaD1 = 0;      
    int linhaD2 = 0, colunaD2 = 9;      

    // === Posicionamento com validação ===
    if (!posicionarNavioHorizontal(tabuleiro, linhaH, colunaH)) {
        printf("Erro ao posicionar navio horizontal!\n");
        return 1;
    }
    if (!posicionarNavioVertical(tabuleiro, linhaV, colunaV)) {
        printf("Erro ao posicionar navio vertical!\n");
        return 1;
    }
    if (!posicionarNavioDiagonalPrincipal(tabuleiro, linhaD1, colunaD1)) {
        printf("Erro ao posicionar navio diagonal!\n");
        return 1;
    }
    if (!posicionarNavioDiagonalSecundaria(tabuleiro, linhaD2, colunaD2)) {
        printf("Erro ao posicionar navio diagonal!\n");
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