#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definição das funções relacionadas ao jogo

// Definição da estrutura para o jogador

struct jogador {
  char nome[50]; // nome do jogador
  int pontuacao; // pontuação do jogador
  // outros atributos do jogador, se necessário
};

// Definição da estrutura para a cobra
typedef struct ponto {
  int x; // coordenada x do nó
  int y; // coordenada y do nó
} Ponto;

// Definição da estrutura para um nó da cobra
typedef struct no_corpo {
  struct ponto corpo;    // coordenada y do nó
  struct no_corpo *prox; // Da cabeça pra cauda
  struct no_corpo *ant;  // Da cauda pra cabeça
} No_Corpo;

typedef enum direcao {
  UP,
  DOWN,
  LEFT,
  RIGHT,
} Direcao;

typedef struct cobra {
  No_Corpo *cabeca;
  No_Corpo *cauda;
  Direcao direcao;
} Cobra;

// Definição da estrutura para a cobra
// struct cobra {
//  struct no_cobra *cabeca; // ponteiro para a cabeça da cobra (primeiro nó da
// lista encadeada)
//  char direcao;            // direção atual da cobra (w, s, a, d)
//};

// Definição da estrutura para a comida
// ponto comida = {.x = 5,.y = 7} exemplo de ponto

// Definição da estrutura para o jogo
struct jogo {

  Cobra no_cobra; // estrutura da cobra
  Ponto comida;   // estrutura da comida
  int velocidade; // velocidade da cobra
  int colisao;    // flag de colisão
};

void comoJogar(void) {
  printf("Use as teclas W (cima), A (esquerda) , S (baixo) e D (direita) para "
         "mover a cobrinha. \n");
  printf("A cobrinha deve comer a comida para aumentar de tamanho. \n");
  printf("Se a cobrinha colidir com seu próprio corpo, o jogo acaba. \n");
}

Cobra *inicializarCobra(int xInicial, int yInicial, Direcao direcaoInicial) {
  Cobra *nova_cobra = (Cobra *)malloc(sizeof(Cobra));
  if (nova_cobra == NULL) {
    fprintf(stderr, "Erro ao inicializar o jogo. \n");
    exit(EXIT_FAILURE);
  }

  nova_cobra->cabeca = (No_corpo *)malloc(sizeof(No_corpo));
  if (nova_cobra->cabeca == NULL) {
    fprintf(stderr, "Erro ao inicializar o jogo. \n");
    exit(EXIT_FAILURE);
  }

  nova_cobra->cabeca->corpo.x = xInicial;
  nova_cobra->cabeca->corpo.y = yInicial;
  nova_cobra->cabeca->prox = NULL;

  nova_cobra->direcao = direcaoInicial;

  return nova_cobra;
}

void mapa(void) {

  int altura = 30, largura = 30;
  for (int i = 0; i < altura; i++) {
    for (int j = 0; j < largura; j++) {
      if (i == 0 || i == largura - 1 || j == 0 || j == altura - 1) {
        printf("#");
      } else {
        printf(" ");
      }
    }
    printf("\n");
  }
}
void moverCobra() {}

void adicionarSegmento() {}

int verificarColisao(Cobra *cobra, int altura, int largura) {
  if(cobra->cabeca->corpo.x == 0 || cobra->cabeca->corpo.x == largura - 1 || cobra->cabeca->corpo.y == 0 || cobra->cabeca->corpo.y == altura -1) {
    return 1; //verifica colisão com as paredes
  }
  
  if() { // verifica colisão com o próprio corpo da cobrinha
  }

return 0; //sem colisão
}

void atualizarPosicaoAlimento() {
  Ponto comida = {
      .x = rand(),
      .y = rand()}; // ainda deve ser definido o range da função aleatória, para
                    // ser coerente com as dimensões do mapa
}

void verificarComerAlimento(
    Cobra cobra,
    Ponto comida) // essa função terá que ser executada continuamente, dentro de
                  // um while na main talvez.
{
  if ((comida.x == cobra.cabeca->corpo.x) &&
      (comida.y ==
       cobra.cabeca->corpo.y)) // se a cabeça atingir a comida, a comida é
                               // gerada novamente e é adicionado um nó na cobra
  {
    atualizarPosicaoAlimento();
    adicionarSegmento();
  }
}

void iniciarJogo() {}

void encerrarJogo() {}

void renderizarTabuleiro() {}

void lidarComEntradaUsuario() {}

void atualizarTela() {}

void exibirPontuacao() {}

int verificarFimDoJogo() {}