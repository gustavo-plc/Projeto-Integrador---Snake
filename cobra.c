#include "cobra.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>


#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define INTERVALO_DE_TEMPO 500 
//Intervalo de tempo entre cada movimento da cobra (em milissegundos)


// definição das funções relacionadas ao jogo

// Definição da estrutura para o jogador

typedef struct jogador Jogador;

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
    if (_kbhit()) { // Se houver entrada do teclado
        char tecla = _getch(); // Recebe o caractere do teclado sem precisar pressionar Enter
        
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

int verificarColisao(Cobra *cobra, int *altura, int *largura) {
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

Ponto *atualizarPosicaoAlimento() {
    Ponto *comida = (Ponto *)malloc(sizeof(Ponto));
    if (!comida) {
        printf("Erro ao alocar a comida.\n");
        return NULL;
    }
    comida->x = rand() % (largura - 2) + 1;  // Limita a comida dentro do mapa, excluindo as bordas
    comida->y = rand() % (altura - 2) + 1;   // Limita a comida dentro do mapa, excluindo as bordas
    return comida;
}


void verificarComerAlimento(Cobra *cobra, Ponto *comida, Jogador *jogador) // essa função terá que ser executada continuamente, dentro de um while na main talvez.
{
  if ((comida->x == cobra->cabeca->corpo.x) && (comida->y == cobra->cabeca->corpo.y)) // se a cabeça atingir a comida, a comida é gerada novamente e é adicionado um nó na cobra
  {
    atualizarPosicaoAlimento(comida);
    adicionarSegmento(cobra);
    jogador->pontuacao = jogador->pontuacao + 5;
  }
}

Cobra *iniciarJogo() {
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
    Cobra *cobra = inicializarCobra(numero_aleatorio1, numero_aleatorio2, DOWN);

    // Definir a posição inicial da comida

    Ponto *comida = atualizarPosicaoAlimento();

    // Configurar a velocidade inicial da cobra
    int velocidade = INTERVALO_DE_TEMPO;

    // Inicializar o jogador e sua pontuação
    Jogador *jogador = criarJogador("Jogador");


    // Loop principal do jogo
    while (!verificarFimDoJogo) {
        // Lógica da cobra e do jogo...
        moverCobra(cobra);
        verificarColisao(cobra, &altura, &largura);
        verificarComerAlimento(cobra, comida, jogador);

        // Aguarda o intervalo de tempo antes do próximo movimento da cobra
        Sleep(velocidade);
    }

    renderizarTabuleiro(cobra, *comida);
    exibirPontuacao(jogador->pontuacao);

    // Liberar a memória alocada para a cobra, a comida e o jogador
    liberarMemoria(cobra);
    free(comida);
    liberarJogador(jogador);

    return cobra;
}

void encerrarJogo() {}

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

void renderizarTabuleiro(Cobra *cobra, Ponto comida) {
    int i, j;

    // Limpar a tela do console
    system("cls || clear");

    // Desenhar as bordas superiores
    for (j = 0; j < largura + 2; j++) {
        printf("#");
    }
    printf("\n");

    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            if (j == 0) {
                printf("#"); // Desenhar a parede esquerda
            }

            // Verificar se a posição atual contém a cabeça da cobra
            if (i == cobra->cabeca->corpo.y && j == cobra->cabeca->corpo.x) {
                printf("O"); // Desenhar a cabeça da cobra
            } else {
                No_Corpo *segmento = cobra->cabeca->prox;
                while (segmento != NULL) {
                    if (i == segmento->corpo.y && j == segmento->corpo.x) {
                        printf("o"); // Desenhar o corpo da cobra
                        break;
                    }
                    segmento = segmento->prox;
                }
                if (segmento == NULL) {
                    if (i == comida.y && j == comida.x) {
                        printf("*"); // Desenhar a comida
                    } else {
                        printf(" "); // Desenhar espaço vazio
                    }
                }
            }

            if (j == largura - 1) {
                printf("#\n"); // Desenhar a parede direita
            }
        }
    }

    // Desenhar as bordas inferiores
    for (j = 0; j < largura + 2; j++) {
        printf("#");
    }
    printf("\n");
    printf("Pressione (Q) para sair!\n");
}

void lidarComEntradaUsuario() {}

void atualizarTela() {}

void exibirPontuacao() {}

void liberarJogador(Jogador *jogador) {
    free(jogador);
}

int verificarFimDoJogo() { // Essa função vai precisar sendo verificada sempre com um while na main
  
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