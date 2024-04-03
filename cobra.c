#include "cobra.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define INTERVALO_DE_TEMPO 500 
//Intervalo de tempo entre cada movimento da cobra (em milissegundos)


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
  struct ponto corpo;    // coordenada do nó
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

int altura = 25, largura = 37;
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
  switch (getchar()) {
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
  No_Corpo *novo = malloc(sizeof(No_Corpo)); // criação de um nó avulso
  novo->prox = NULL; // como o novo nó criado é o último, ele apontará para
                     // NULL.
  if (!novo)         // se nó criado com sucesso, não entra no if
    return;
  No_Corpo *aux = cobra->cabeca;
  while (aux->prox != NULL)
    aux = aux->prox;
  aux->prox =
      novo; // o último nó apontará para o novo nó criado (que agora é o último)
  cobra->cauda = novo; // atualização da variável cauda para receber o endereço
                       // do último nó
}

boolean verificarColisao(Cobra *cobra, int altura, int largura) {
  if (cobra->cabeca->corpo.x == 0 || cobra->cabeca->corpo.x == largura - 1 ||
      cobra->cabeca->corpo.y == 0 || cobra->cabeca->corpo.y == altura - 1) {
    return true; // colisão com as paredes
  }
  No_Corpo *segmento = cobra->cabeca->prox;
  while (segmento != NULL) {
    if (segmento->corpo.x == cobra->cabeca->corpo.x &&
        segmento->corpo.y == cobra->cabeca->corpo.y) {
      return true; // colisão com o proprio corpo da cobrinha
    }
    segmento = segmento->prox;
  }
  return false; // sem colisão
}

void atualizarPosicaoAlimento() {
  Ponto comida = {
      .x = rand(),
      .y = rand()}; // ainda deve ser definido o range da função aleatória, para
                    // ser coerente com as dimensões do mapa
}

void verificarComerAlimento(Cobra cobra, Ponto comida, Jogador jogador) // essa função terá que ser executada continuamente, dentro de um while na main talvez.
{
  if ((comida.x == cobra.cabeca->corpo.x) && (comida.y == cobra.cabeca->corpo.y)) // se a cabeça atingir a comida, a comida é gerada novamente e é adicionado um nó na cobra
  {
    atualizarPosicaoAlimento();
    adicionarSegmento(cobra);
    jogador.pontuacao = jogador.pontuacao + 5;
  }
}

void iniciarJogo() {
    // Inicializar a cobra com uma posição inicial e direção inicial
    int min = 2; // Limites do mapa
    int max = 30; // Limites do mapa
    int numero_aleatorio1, numero_aleatorio2;

    // Definindo a semente com base no tempo atual
    srand(time(NULL));

    // Gerando números aleatórios para inicializar a posição da cobra
    numero_aleatorio1 = min + rand() % (max - min + 1);
    numero_aleatorio2 = min + rand() % (max - min + 1);

    // Inicializar a cobra
    Cobra cobra = inicializarCobra(numero_aleatorio1, numero_aleatorio2, DOWN);

    // Definir a posição inicial da comida
    atualizarPosicaoAlimento();

    // Configurar a velocidade inicial da cobra
    int velocidade = INTERVALO_DE_TEMPO;

    // Inicializar a pontuação do jogador
    Jogador jogador;
    jogador.pontuacao = 0;

    // Loop principal do jogo
    while (!verificarFimDoJogo()) {
        // Lógica da cobra e do jogo...

        // Aguarda o intervalo de tempo antes do próximo movimento da cobra
        Sleep(velocidade);
    }

    // Renderizar a tela final do jogo e exibir a pontuação
    renderizarTabuleiro();
    exibirPontuacao(jogador.pontuacao);
}


void encerrarJogo() {}

void renderizarTabuleiro() {}

void lidarComEntradaUsuario() {}

void atualizarTela() {}

void exibirPontuacao() {}

boolean verificarFimDoJogo() { // Essa função vai precisar sendo verificada sempre com um while na main
  
  if (verificarColisao) 
  {
    return true; // retorna true para fim do jogo
  }
  return false; // enquanto não tem colisão retorna false
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