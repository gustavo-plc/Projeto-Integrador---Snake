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
    unsigned int length;
} Cobra;


void comoJogar(void) {
    printf("\n\n1) Use as teclas W (cima), A (esquerda), S (baixo) e D (direita) para mover a cobra. \n");
    printf("\n2) O jogador ganha pontos quando a cobra come a comida, o que também faz ela aumentar de tamanho. \n");
    printf("\n3) O jogo acaba quando a cobra colide com o próprio corpo ou com as paredes do mapa. \n");
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

    cobra->cauda = cobra->cabeca;
    cobra->cabeca->corpo.x = xInicial;
    cobra->cabeca->corpo.y = yInicial;
    cobra->cabeca->prox = NULL;

    cobra->cauda->corpo.x = xInicial;
    cobra->cauda->corpo.y = yInicial;
    cobra->cabeca->ant = NULL;

    cobra->direcao = direcaoInicial;
    cobra->length = 1;

    return cobra;
}

int altura = 30, largura = 80;
char *mapaBuffer = NULL;


void renderizarTabuleiro(Cobra *cobra, Ponto comida, Jogador *jogador) {
    // Limpa o mapaBuffer
    memset(mapaBuffer, ' ', (largura + 2) * (altura + 2));

    // Posiciona a cabeça da cobra no mapaBuffer
    mapaBuffer[(cobra->cabeca->corpo.y) * (largura + 2) + cobra->cabeca->corpo.x] = 'O';

    // Posiciona o corpo da cobra no mapaBuffer
    No_Corpo *segmento = cobra->cabeca->prox;
    while (segmento != NULL) {
        mapaBuffer[(segmento->corpo.y) * (largura + 2) + segmento->corpo.x] = 'o';
        segmento = segmento->prox;
    }

    // Posiciona a comida no mapaBuffer
    mapaBuffer[(comida.y) * (largura + 2) + comida.x] = '*';

    // Imprime o mapaBuffer
    system("cls");
    for (int i = 0; i < altura + 2; i++) {
        for (int j = 0; j < largura + 2; j++) {
            char c = mapaBuffer[i * (largura + 2) + j];
            if (i == 0 || i == altura + 1 || j == 0 || j == largura + 1)
                printf("#");
            else
                printf("%c", c);
        }
        printf("\n");
    }

    exibirPontuacao(jogador);
    printf("Pressione (Q) para sair!\n");
}



void obterDirecao(Cobra *cobra) {
    if (_kbhit()) {
    int tecla = _getch();

    switch (tecla) {
    case 'w':
      if (cobra->direcao != DOWN)
        cobra->direcao = UP;
      break;
    case 'a':
      if (cobra->direcao != RIGHT)
        cobra->direcao = LEFT;
      break;
    case 's':
      if (cobra->direcao != UP)
        cobra->direcao = DOWN;
      break;
    case 'd':
      if (cobra->direcao != LEFT)
        cobra->direcao = RIGHT;
      break;
    }
  }
}

void moverCobra(Cobra *cobra) {
    No_Corpo *no_corpo = cobra->cauda;
    while(no_corpo->ant != NULL) {
        no_corpo->corpo.x = no_corpo->ant->corpo.x;
        no_corpo->corpo.y = no_corpo->ant->corpo.y;
        no_corpo = no_corpo->ant;
    }
    switch (cobra->direcao)
    {
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

void adicionarSegmento(Cobra *cobra, Ponto comida) {
    if (!cobra) return;
    No_Corpo *novo = malloc(sizeof(No_Corpo));
    if (!novo) return;
    novo->prox = cobra->cabeca;
    novo->ant = NULL;
    novo->corpo = comida;
    cobra->cabeca->ant = novo;
    cobra->cabeca = novo;
    cobra->length++;
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
    int x = cobra->cabeca->corpo.x;
    int y = cobra->cabeca->corpo.y;

    // Atualiza as coordenadas com base na direção da cobra
    switch(cobra->direcao) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }

    // Verifica se a cobra alcançou a comida
    if ((comida->x == x) && (comida->y == y)) {
        adicionarSegmento(cobra, *comida);
        free(comida); // Liberar a memória da comida atual
        *comida = *atualizarPosicaoAlimento(); // Gera uma nova posição para a comida
        jogador->pontuacao += 5;
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

    // Inicializar o mapaBuffer
    mapaBuffer = (char *)malloc(sizeof(char) * (largura + 3) * (altura + 3));
    if (!mapaBuffer) {
        printf("Erro ao alocar memória para o mapaBuffer.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < altura + 2; i++) {
        for (int j = 0; j < largura + 2; j++) {
            if (i == 0 || i == altura + 1 || j == 0 || j == largura + 1)
                mapaBuffer[i * (largura + 3) + j] = '#';
            else
                mapaBuffer[i * (largura + 3) + j] = ' ';
        }
    }

    while (!verificarFimDoJogo(&cobra, &altura, &largura)) {
        obterDirecao(cobra);
        moverCobra(cobra);
        verificarColisao(cobra, &altura, &largura);
        verificarComerAlimento(cobra, comida, jogador);
        renderizarTabuleiro(cobra, *comida, jogador);
        Sleep(velocidade);
    }

    liberarMemoria(cobra);
    free(comida);
    free(mapaBuffer);
    liberarJogador(jogador);

    return cobra;
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

