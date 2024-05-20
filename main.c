#include "cobra.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>


int main() {
 
  SetConsoleOutputCP(CP_UTF8);
  int escolha;

  while (1) {
        printf("\n\n ----------------------- ");
        printf("\n 1 - NOVO JOGO ");
        printf("\n 2 - COMO JOGAR ");
        printf("\n 3 - RANKING ");
        printf("\n 4 - CRÉDITOS ");
        printf("\n 5 - SAIR DO JOGO ");
        printf("\n\n Escolha uma opção: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1: {
                Cobra *jogo = iniciarJogo();
                system("pause");
                break;
            }

            case 2: {
                system("cls");
                printf("\n\nREGRAS DO JOGO \n");
                comoJogar();
                printf("\nPressione qualquer tecla para voltar ao menu inicial.\n\n");
                _getch(); // Aguarda o usuário pressionar qualquer tecla
                break;
            }

            case 3: {
                system("cls");
                exibirRanking();
                break;
            }

            case 4: {
                system("cls");
                printf("\n\nJOGO DESENVOLVIDO POR: \n\n");
                printf("\nDavi Mendes Paraiso Carvalho \n");
                printf("\nGustavo Parreira Lima Cunha \n");
                printf("\nLucas Montalvão Ramires \n");
                printf("\nRafael Rodrigues Barbosa \n");
                printf("\n\nPressione qualquer tecla para voltar ao menu inicial.\n\n");
                _getch(); // Aguarda o usuário pressionar qualquer tecla
                break;
            }

            case 5: {
                printf("\nAguardamos você em breve para uma nova partida!\n");
                return 0; // Saia do programa
            }

            default: {
                system("cls");
                printf("\n\n Nenhuma opção foi escolhida ");
                break;
            }
        }
    }

    return 0;
}