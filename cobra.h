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

/*Funções para implementação do jogo




1. Inicialização do jogo:
Função para inicializar o estado do jogo, incluindo a criação da cobra, configuração da posição inicial, comprimento, direção inicial, etc.

2. Atualização do jogo:
Função para atualizar o estado do jogo a cada iteração do loop principal do jogo. Isso inclui mover a cobra, verificar colisões, gerar itens (por exemplo, comida para a cobra), atualizar a pontuação, etc.

3. Manipulação da cobra:
Função para mover a cobra com base na direção atual.
Função para adicionar um novo segmento à cobra quando ela come um item (por exemplo, comida).
Função para remover o último segmento da cobra quando ela se move.

4. Manipulação da lista encadeada:
Função para criar um novo segmento da cobra e adicioná-lo à lista encadeada.
Função para remover o último segmento da cobra da lista encadeada.
Função para percorrer a lista encadeada e atualizar as posições dos segmentos da cobra.

5. Verificação de colisões:
Função para verificar se a cobra colidiu com as bordas da tela ou consigo mesma.

6. Controle de entrada:
Função para capturar a entrada do jogador (por exemplo, teclas de seta) e atualizar a direção da cobra.

7. Renderização do jogo:
Função para desenhar a cobra, itens e outras partes do jogo na tela.

8. Finalização do jogo:
Função para encerrar o jogo quando o jogador perder (por exemplo, cobra colidiu consigo mesma ou com as bordas da tela).

*/

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