#include "cobra.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>

#define INTERVALO_DE_TEMPO 100

typedef struct jogador Jogador;

struct jogador {
    char nome[50];
    int pontuacao;
};

typedef struct ponto {
    int x;
    int y;
} Ponto;

typedef enum direcao {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} Direcao;

typedef struct no_corpo {
    struct ponto corpo;
    struct no_corpo *prox;
    struct no_corpo *ant;
} No_Corpo;

typedef struct cobra {
    No_Corpo *cabeca;
    No_Corpo *cauda;
    Direcao direcao;
} Cobra;

int altura = 25, largura = 37;

void comoJogar(void) {
    printf("Use as teclas W (cima), A (esquerda) , S (baixo) e D (direita) para "
           "mover a cobrinha. \n");
    printf("A cobrinha deve comer a comida para aumentar de tamanho. \n");
    printf("Se a cobrinha colidir com seu próprio corpo, o jogo acaba. \n");
}

Cobra *inicializarCobra(int xInicial, int yInicial, Direcao direcaoInicial) {
    Cobra *cobra = (Cobra *)malloc(sizeof(Cobra));
    if (cobra == NULL) {
        fprintf(stderr, "Erro ao inicializar o jogo. \n");
        exit(EXIT_FAILURE);
    }

    cobra->cabeca = (No_Corpo *)malloc(sizeof(No_Corpo));
    if (cobra->cabeca == NULL) {
        fprintf(stderr, "Erro ao inicializar o jogo. \n");
        exit(EXIT_FAILURE);
    }

    cobra->cauda = (No_Corpo *)malloc(sizeof(No_Corpo));
    if (cobra->cauda == NULL) {
        fprintf(stderr, "Erro ao inicializar o jogo. \n");
        exit(EXIT_FAILURE);
    }

    cobra->cabeca->corpo.x = xInicial;
    cobra->cabeca->corpo.y = yInicial;
    cobra->cabeca->prox = NULL;

    cobra->cauda->corpo.x = xInicial;
    cobra->cauda->corpo.y = yInicial;
    cobra->cabeca->ant = NULL;

    cobra->direcao = direcaoInicial;

    return cobra;
}

void mapa(void) {
    for (int j = 0; j < largura; j++) {
        printf("#");
    }
    printf("\n");
    for (int h = 0; h < altura; h++) {
        printf("#                                   #\n");
    }
    for (int j = 0; j < largura; j++) {
        printf("#");
    }
    printf("\n");
}

void moverCobra(Cobra *cobra) {
    if (_kbhit()) {
        int tecla = _getch(); // Recebe o caractere do teclado sem precisar pressionar Enter
        switch (tecla) {
        case 'w':
            cobra->direcao = UP;
            break;
        case 'a':
            cobra->direcao = LEFT;
            break;
        case 's':
            cobra->direcao = DOWN;
            break;
        case 'd':
            cobra->direcao = RIGHT;
            break;
        }
    }

    switch (cobra->direcao) {
    case UP:
        cobra->cabeca->corpo.y--;
        break;
    case DOWN:
        cobra->cabeca->corpo.y++;
        break;
    case RIGHT:
        cobra->cabeca->corpo.x++;
        break;
    case LEFT:
        cobra->cabeca->corpo.x--;
        break;
    }
}

void adicionarSegmento(Cobra *cobra) {
    if (!cobra)
        return;
    No_Corpo *novo = malloc(sizeof(No_Corpo));
    novo->prox = NULL;
    if (!novo)
        return;
    No_Corpo *aux = cobra->cabeca;
    while (aux->prox != NULL)
        aux = aux->prox;
    aux->prox = novo;
    cobra->cauda = novo;
}

int verificarColisao(Cobra *cobra, int *altura, int *largura) {
    if (cobra->cabeca->corpo.x == 0 || cobra->cabeca->corpo.x == *largura - 1 ||
        cobra->cabeca->corpo.y == 0 || cobra->cabeca->corpo.y == *altura - 1) {
        return true;
    }
    No_Corpo *segmento = cobra->cabeca->prox;
    while (segmento != NULL) {
        if (segmento->corpo.x == cobra->cabeca->corpo.x &&
            segmento->corpo.y == cobra->cabeca->corpo.y) {
            return true;
        }
        segmento = segmento->prox;
    }
    return false;
}

Ponto *atualizarPosicaoAlimento() {
    Ponto *comida = (Ponto *)malloc(sizeof(Ponto));
    if (!comida) {
        printf("Erro ao alocar a comida.\n");
        return NULL;
    }
    comida->x = rand() % (largura - 2) + 1;
    comida->y = rand() % (altura - 2) + 1;
    return comida;
}

void verificarComerAlimento(Cobra *cobra, Ponto *comida, Jogador *jogador) {
    if ((comida->x == cobra->cabeca->corpo.x) &&
        (comida->y == cobra->cabeca->corpo.y)) {
        atualizarPosicaoAlimento(comida);
        adicionarSegmento(cobra);
        jogador->pontuacao = jogador->pontuacao + 5;
    }
}

Cobra *iniciarJogo() {
    int min = 2;
    int max = 30;
    int numero_aleatorio1, numero_aleatorio2;

    srand(time(NULL));

    numero_aleatorio1 = min + rand() % (max - min + 1);
    numero_aleatorio2 = min + rand() % (max - min + 1);

    Cobra *cobra = inicializarCobra(numero_aleatorio1, numero_aleatorio2, DOWN);

    Ponto *comida = atualizarPosicaoAlimento();

    int velocidade = INTERVALO_DE_TEMPO;

    Jogador *jogador = criarJogador("Jogador");

    while (!verificarFimDoJogo(&cobra, &altura, &largura)) {
        moverCobra(cobra);
        verificarColisao(cobra, &altura, &largura);
        verificarComerAlimento(cobra, comida, jogador);
        renderizarTabuleiro(cobra, *comida);
        Sleep(velocidade);
    }

    liberarMemoria(cobra);
    free(comida);
    liberarJogador(jogador);

    return cobra;
}

void renderizarTabuleiro(Cobra *cobra, Ponto comida) {
    int i, j;

    system("cls");

    for (j = 0; j < largura + 2; j++) {
        printf("#");
    }
    printf("\n");

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            if (j == 0) {
                printf("#");
            }

            if (i == cobra->cabeca->corpo.y && j == cobra->cabeca->corpo.x) {
                printf("O");
            } else {
                No_Corpo *segmento = cobra->cabeca->prox;
                while (segmento != NULL) {
                    if (i == segmento->corpo.y && j == segmento->corpo.x) {
                        printf("o");
                        break;
                    }
                    segmento = segmento->prox;
                }
                if (segmento == NULL) {
                    if (i == comida.y && j == comida.x) {
                        printf("*");
                    } else {
                        printf(" ");
                    }
                }
            }

            if (j == largura - 1) {
                printf("#\n");
            }
        }
    }

    for (j = 0; j < largura + 2; j++) {
        printf("#");
    }
    printf("\n");
    printf("Pressione (Q) para sair!\n");
}

Jogador *criarJogador(const char *nome) {
    Jogador *jogador = (Jogador *)malloc(sizeof(Jogador));
    if (jogador == NULL) {
        printf("\nErro ao criar jogador.\n");
        return NULL;
    }
    strcpy(jogador->nome, nome);
    jogador->pontuacao = 0;
    return jogador;
}

void liberarJogador(Jogador *jogador) { free(jogador); }

int verificarFimDoJogo(Cobra **cobra, int *altura, int *largura) {
    if (verificarColisao(*cobra, altura, largura)) {
        return true;
    }
    return false;
}

void liberarMemoria(Cobra *cobra) {
    No_Corpo *atual = cobra->cabeca;
    while (atual != NULL) {
        No_Corpo *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    cobra->cabeca = NULL;
    cobra->cauda = NULL;
}

