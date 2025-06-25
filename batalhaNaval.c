#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

// === Definições de constantes para o tabuleiro e navios ===
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5
#define TAM_HABILIDADE 5

// === Inicializa tabuleiro ===
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        for (int j = 0; j < TAMANHO_TABULEIRO; j++)
            tabuleiro[i][j] = AGUA;
}

// === Exibe o tabuleiro ===
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        printf("%c ", 'A' + i);
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            char c;
            switch (tabuleiro[i][j]) {
                case AGUA: c = '0'; break;
                case NAVIO: c = '3'; break;
                case HABILIDADE: c = '5'; break;
                default: c = '?';
            }
            printf("%c ", c);
        }
        printf("\n");
    }
}

// === Exibe matriz de habilidade ===
void exibirHabilidadeSeparada(int habilidade[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("   ");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++)
        printf("%c ", 'A' + i);
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (habilidade[i][j] == 1)
                printf("5 ");
            else
                printf("0 ");
        }
        printf("\n");
    }
}

// === Formas das habilidades ===
void construirCone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    
    // Zera a matriz
    for (int i = 0; i < TAM_HABILIDADE; i++)
        for (int j = 0; j < TAM_HABILIDADE; j++)
            matriz[i][j] = 0;

    // Preenche somente as 3 primeiras linhas
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (j >= meio - i && j <= meio + i)
                matriz[i][j] = 1;
        }
    }
}

void construirCruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = (i == meio || j == meio) ? 1 : 0;
        }
    }
}

void construirOctaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int meio = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int dif_i = (i > meio) ? i - meio : meio - i;
            int dif_j = (j > meio) ? j - meio : meio - j;
            matriz[i][j] = (dif_i + dif_j <= meio) ? 1 : 0;
        }
    }
}

// === Verifica se pode aplicar habilidade ===
int Habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
               int matriz[TAM_HABILIDADE][TAM_HABILIDADE],
               int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (matriz[i][j] == 1) {
                int linhaTab = origemLinha - offset + i;
                int colunaTab = origemColuna - offset + j;
                if (linhaTab < 0 || linhaTab >= TAMANHO_TABULEIRO || colunaTab < 0 || colunaTab >= TAMANHO_TABULEIRO)
                    return 0;
                if (tabuleiro[linhaTab][colunaTab] == NAVIO || tabuleiro[linhaTab][colunaTab] == HABILIDADE)
                    return 0;
            }
        }
    }
    return 1;
}

// === Aplica habilidade ===
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidadeSeparada[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int matriz[TAM_HABILIDADE][TAM_HABILIDADE],
                       int origemLinha, int origemColuna,
                       const char* nomeHabilidade) {
    int offset = TAM_HABILIDADE / 2;
    printf("Habilidade %s aplicada em (%d, %c)\n", nomeHabilidade, origemLinha, 'A' + origemColuna);

    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (matriz[i][j] == 1) {
                int linhaTab = origemLinha - offset + i;
                int colunaTab = origemColuna - offset + j;

                if (linhaTab >= 0 && linhaTab < TAMANHO_TABULEIRO &&
                    colunaTab >= 0 && colunaTab < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linhaTab][colunaTab] == AGUA) {
                        tabuleiro[linhaTab][colunaTab] = HABILIDADE;
                    }
                    habilidadeSeparada[linhaTab][colunaTab] = 1;
                }
            }
        }
    }
}

// === Posiciona navios ===
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
    printf("=== BATALHA NAVAL - INICIO ===\n");

    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializarTabuleiro(tabuleiro);

    // Posicionar navios
    posicionarNavioHorizontal(tabuleiro, 0, 0); // (0,A),(0,B),(0,C)
    posicionarNavioVertical(tabuleiro, 1, 8);   // (1,A),(2,A),(3,A)
    posicionarNavioDiagonalPrincipal(tabuleiro, 7, 0); // (7,A),(8,B),(9,C)
    posicionarNavioDiagonalSecundaria(tabuleiro, 7, 9); // (7,J),(8,I),(9,H)

    // Construir habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    int coneSeparado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};
    int cruzSeparado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};
    int octaedroSeparado[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // CONE centro (4,C)
    if (Habilidade(tabuleiro, cone, 4, 2))
        aplicarHabilidade(tabuleiro, coneSeparado, cone, 4, 2, "CONE");
    else
        printf("Habilidade CONE não aplicada: conflito com navio ou outra habilidade.\n");

    // CRUZ centro (2,E)
    if (Habilidade(tabuleiro, cruz, 2, 5))
        aplicarHabilidade(tabuleiro, cruzSeparado, cruz, 2, 5, "CRUZ");
    else
        printf("Habilidade CRUZ não aplicada: conflito com navio ou outra habilidade.\n");

    // OCTAEDRO centro (5,H)
    if (Habilidade(tabuleiro, octaedro, 5, 7))
        aplicarHabilidade(tabuleiro, octaedroSeparado, octaedro, 5, 7, "OCTAEDRO");
    else
        printf("Habilidade OCTAEDRO não aplicada: conflito com navio ou outra habilidade.\n");

    printf("\n=== TABULEIRO FINAL COMPLETO ===\n");
    exibirTabuleiro(tabuleiro);

    printf("\n=== BATALHA NAVAL - FIM ===\n");

    return 0;
}
