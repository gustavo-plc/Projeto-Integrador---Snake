#include "cobra.h"
#include <stdio.h>
#include <stdlib.h>


int main() {

  int escolha;

  // se a escolha for diferente de 5, ele continua... o que inicialmente é
  // verdade pois escolha é igual a 1
  do {
    printf("\n\n ----------------------- ");

    printf("\n 1 - NOVO JOGO ");
    printf("\n 2 - COMO JOGAR ");
    printf("\n 3 - RANKING ");
    printf("\n 4 - CRÉDITOS ");
    printf("\n 5 - SAIR DO JOGO ");
    printf("\n\n Escolha uma opção: ");
    scanf("%d", &escolha);

    // se for escolhida a opção 5, ele pula o while utilizando continue para
    // isso
    if (escolha == 5) {
      continue;
    }
    
  } while (escolha < 0 || escolha > 5);

    // estrutura switch
    switch (escolha) {

    case 1: {
  
    Cobra *jogo = iniciarJogo();

    system("pause");

    break;
    }

    case 2: {
      system("clear");
      printf("\n\n Opção escolhida: 2 ");
      comoJogar();
      break;
    }

    case 3: {
      system("clear");
      printf("\n\n Opção escolhida: 3 ");
      break;
    }

    case 4: {
      system("clear");
      printf("\n\n Opção escolhida: 4 ");
      break;
    }

    // opção padrão
    default: {
      system("clear");
  
      // caso o usuário digite um numero acima de 5, ele irá informar que nao
      // existe essa opção
      printf("\n\n Nenhuma opção foi escolhida ");
      break;
    }
    }

  if (escolha == 5)
    printf("\n\n Aguardamos você em breve para uma nova partida!");
}

// int main() {
//   // setlocale(LC_ALL, "en_US.UTF-8");
//   // setlocale(LC_ALL, "Portuguese_Brasil");

//   limpar_tela();
//   mover_cursor_xy(5, 5);
//   printf("Texto na posição 5,5");

//   return 0;
// }