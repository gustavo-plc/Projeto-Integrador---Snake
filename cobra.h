#ifndef COBRA_H
#define COBRA_H

//protótipos das estruturas

typedef struct jogador Jogador;
typedef struct ponto Ponto;
typedef struct no_corpo No_Corpo;
typedef struct cobra Cobra;
typedef struct jogo Jogo;


//descrição do cabeçalho das funções


//* Função no menu 


void verRecordes(void);
void comoJogar(void);
void mostrarCreditos(void);
void sairJogo(void);


// Cabeçalho da função para inicializar a cobra
Cobra* inicializarCobra();

// Cabeçalho da função para mover a cobra
void moverCobra();

// Cabeçalho da função para adicionar um novo segmento à cobra
void adicionarSegmento();

// Cabeçalho da função para verificar colisão da cobra
int verificarColisao(Cobra *cobra, int *altura, int *largura);

// Cabeçalho da função para atualizar a posição do alimento
Ponto *atualizarPosicaoAlimento();

// Cabeçalho da função para verificar se a cobra comeu o alimento
void verificarComerAlimento(Cobra *cobra, Ponto *comida, Jogador *jogador);

// Cabeçalho da função para iniciar o jogo
Cobra *iniciarJogo();

// Cabeçalho da função para encerrar o jogo
void encerrarJogo();

void exibirRanking();

void renderizarTabuleiro();

// Cabeçalho da função para lidar com entrada do usuário
void lidarComEntradaUsuario();

// Cabeçalho da função para atualizar a tela do jogo
void atualizarTela();

// Cabeçalho da função para exibir a pontuação
void exibirPontuacao();

// Cabeçalho da função para verificar se o jogo acabou
int verificarFimDoJogo();

// Cabeçalho da função para inicializar o tabuleiro
void inicializarTabuleiro();

Jogador *criarJogador(const char *nome);

void liberarJogador(Jogador *jogador);

// Cabeçalho da função para limpar a tela
void limparTela();

// Cabeçalho da função para controlar a velocidade do jogo
void controlarVelocidadeJogo();

// Cabeçalho da função para liberar a memória alocada
void liberarMemoria(Cobra *cobra);

// Cabeçalho da função para pausar o jogo
void pausarJogo();

// Cabeçalho da função para reiniciar o jogo
void reiniciarJogo();


#endif