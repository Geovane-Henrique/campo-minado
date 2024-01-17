#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <windows.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "Portuguese_Brasil");

    int op, opLinha, opColuna, fim;
    int contador_minas = 0;

    do {
        char nome[30];

        printf(" __________________________________________________");
        printf("\n|                  Campo minado                    |\n");
        printf("|                                                  |\n");
        printf("|                                                  |\n");
        printf("|                                                  |\n");

        printf("|                 1.Iniciar parida                 |\n");
        printf("|                                                  |\n");
        printf("|                 2.Sair do game                   |\n");
        printf("|                                                  |\n");
        printf("|                                                  |\n");
        printf("|__________________________________________________|\n\n");

        printf("Escolha uma op%c%co: \n", 135, 131);
        scanf("%d", &op);
        printf("\n");
        
        if(op == 1) {
        	printf("Digite seu nome: \n");
        	scanf("%s", &nome);	
		}

        system("CLS");

        // Cria mapa externo
        char mapaView[7][13] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12',
                                '1', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
                                '2', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
                                '3', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
                                '4', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
                                '5', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?',
                                '6', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', '?', };

        // Cria mapa interno
        char mapa[6][12];

        for (int i = 0; i < 6; ++i) {
            for (int j = 0; j < 12; ++j) {
                mapa[i][j] = 'a';
            }
        }

        // Gera 10 minas aleatoriamente
        srand(static_cast<unsigned>(time(0)));
        for (int minas = 0; minas < 10; ++minas) {
            int linha = rand() % 6;
            int coluna = rand() % 12;

            // Impede que existam + de uma mina na mesma casa
        while (mapa[linha][coluna] == 'X') {
            linha = rand() % 6;
            coluna = rand() % 12;
            }

            // Insere a mina na casa
            mapa[linha][coluna] = 'X';
        }

        // 1.Seleciona as casas exemplo 0,0
        for (int horizontal = 0; horizontal < 6; ++horizontal) {
            for (int vertical = 0; vertical < 12; ++vertical) {
                if (mapa[horizontal][vertical] == 'a') {
                    int soma = 0;
                    // Verifica quantas minas tem ao redor num formato 3x3
                    for (int x = -1; x <= 1; ++x) {
                        for (int y = -1; y <= 1; ++y) {
                            int nLinha = horizontal + x;
                            int nColuna = vertical + y;

                            if (nLinha >= 0 && nLinha < 6 && nColuna >= 0 && nColuna < 12) {
                                soma += (mapa[nLinha][nColuna] == 'X') ? 1 : 0;
                            }
                        }
                    }
                    mapa[horizontal][vertical] = soma + '0';
                }
            }
        }

        switch (op) {
        case 1:
            do {
                contador_minas = 0;

                printf("\n\n");
                printf("  __________________________________________\n");
                printf(" |                                          |\n");
                printf(" |             OLHA A BOMBA!!!!             |\n");
                printf(" |                                          |\n");
                printf(" |                                          |");
                // Exibe o mapa externo
                printf("\n |  ");
                for (int l = 0; l < 7; ++l) {
                    for (int c = 0; c < 13; ++c) {
                        if (c >= 10 && l == 0) {
                            printf("1%c ", mapaView[l][c]);
                        } else {
                            printf(" %c ", mapaView[l][c]);
                        }
                    }
                    printf(" |\n |  ");
                }
                printf("                                        |\n");
                printf(" |                                          |\n");
                printf(" |__________________________________________|\n");

                printf("\n");
                printf("Digite a linha:\n");
                scanf("%d", &opLinha);
                printf("Digite uma coluna:\n");
                scanf("%d", &opColuna);

                int vlinha = opLinha, vcoluna = opColuna;
                int horizontal = opLinha, vertical = vcoluna;
                mapaView[opLinha][opColuna] = mapa[opLinha - 1][opColuna - 1];

                if (mapa[horizontal - 1][vertical - 1] == '0') {
                    for (int x = -1; x <= 1; ++x) {
                        for (int y = -1; y <= 1; ++y) {
                            int nLinha = vlinha + x;
                            int nColuna = vcoluna + y;

                            if (nLinha > 0 && nLinha < 7 && nColuna > 0 && nColuna < 13) {
                                mapaView[nLinha][nColuna] = mapa[nLinha - 1][nColuna - 1];
                            }
                        }
                    }
                }

                for (int i = 0; i < 7; ++i) {
                    for (int j = 0; j < 17; ++j) {
                        if (mapaView[i][j] != '?') {
                            contador_minas++;
                        }
                    }
                }

                system("cls");
            } while (mapaView[opLinha][opColuna] != 'X' && contador_minas < 81);

            if (contador_minas == 81) {
                printf("Parab%cns, voc%c venceu!\n", 130, 136);
                for (int l = 0; l < 6; ++l) {
                    for (int c = 0; c < 12; ++c) {
                        printf("%c ", mapa[l][c]);
                    }
                    printf("\n");
                }
            } else {
                printf("\n");
                printf("                    GAME OVER!!\n\n\n");
                printf("              HAHAAHAAHAHAHAHAAHAAHAHH\n\n\n");

                printf("                      %s          \n", nome);
                printf("                     _______   \n");
                printf("                    /       \\  \n");
                printf("                   /         \\ \n");
                printf("                  |   R.I.P.  |\n");
                printf("                  |           |\n");
                printf("                  |           |\n");
                printf("                  |           |\n");
                printf("                  |      |    |\n");
                printf("                  |   ___|___ |\n");
                printf("                  |      |    |\n");
                printf("                  |      |    |\n");
                printf("                  |      |    |\n");
                printf("                  |      |    |\n");
                printf("                  |      |    |\n");
                printf("                  |      |    |\n");
                printf("                  |           |\n");
                printf("                  |           |\n");
                printf("                   \\         / \n");
                printf("                    \\_______/  \n\n");
            }

            break;

        case 2:
            printf("Obrigado por jogar! Encerrando o jogo...\n");
            fim = 0;
            break;

        default:
            break;
        }

        if (op != 2) {
            printf("1. Continuar\n\n");
            scanf("%d", &fim);
            system("cls");
        }

    } while (fim == 1);

    return 0;
}

