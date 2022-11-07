/********** JOGO DA VELHA **********/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

/*** Variavel Global ***/
char jogo[3][3]; // Matriz do Jogo.

int l, c; // l = Linha | c = Coluna.

/*** Tabuleiro ***/
void inicializarMatriz() {
    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            jogo[l][c] = ' ';
    }
}

/*** Imprimir Tabuleiro ***/
void imprimir() {
    printf("\n\n\t 0   1   2\n\n");
    for(l = 0; l < 3; l++) {
        for(c = 0; c < 3; c++) {
            if(c == 0)
                printf("\t");
            printf(" %c ", jogo[l][c]);
            if(c < 2)
                printf("|");
            if(c == 2)
                printf("   %d", l);
        }
        printf("\n");
        if(l < 2)
            printf("\t-----------\n");
    }
}

/*** Funcao Para Validar Uma Coordenada ***/
int ehValida(int l, int c) {
    if (l >= 0 && l < 3 && c >= 0 && c < 3 && jogo[l][c] == ' ')
        return 1;
    else
        return 0;
}

/*** Funcao Para Definir Vitoria ***/

/** Jogador 'c' na Linha 'l'  **/
int ganhouPorLinha(int l, char c) {
    if (jogo[l][0] == c && jogo[l][1] == c && jogo[l][2] == c)
        return 1;
    else
        return 0;
}

/** Jogador 'c' Nas Linhas **/
int ganhouPorLinhas(char c) {
    int ganhou = 0;
    for (l = 0; l < 3; l++)
    {
        ganhou += ganhouPorLinha(l, c);
    }
    return ganhou;
}

/** Jogador 'j' Na Coluna 'c' **/
int ganhouPorColuna(int c, char j) {
    if (jogo[0][c] == j && jogo[1][c] == j && jogo[2][c] == j)
        return 1;
    else
        return 0;
}

/** Jogador 'j' Nas Colunas **/
int ganhouPorColunas(char j) {
    int ganhou = 0;
    for (c = 0; c < 3; c++)
    {
        ganhou += ganhouPorColuna(c, j);
    }
    return ganhou;
}

/** Jogador 'c' Na Diagonal Principal **/
int ganhouPorDiagPrin(char c) {
    if (jogo[0][0] == c && jogo[1][1] == c && jogo[2][2] == c)
        return 1;
    else
        return 0;
}

/** Jogador 'c' Na Diagonal Secundaria **/
int ganhouPorDiagSec(char c) {
    if (jogo[0][2] == c && jogo[1][1] == c && jogo[2][0] == c)
        return 1;
    else
        return 0;
}

/*** Funcao Para Pedir As Coordenadas ***/
void lerCoordenadas(char j) {
    int linha, coluna;

    printf("\nJogador %c digite linha e coluna: ", j);
    scanf("%d%d", &linha, &coluna);

    while (ehValida(linha, coluna) == 0) {
        printf("\nCoordenadas invalidas!\n\nJogador %c digite outra linha e coluna: ", j);
        scanf("%d%d", &linha, &coluna);
    }
    jogo[linha][coluna] = j;
}

/*** Funcao Que Retorna Posicoes Vazias ***/
int quantVazias() {
    int quantidade = 0;

    for (l = 0; l < 3; l++) {
        for (c = 0; c < 3; c++)
            if (jogo[l][c] == ' ')
                quantidade++;
    }
    return quantidade;
}

/*** Funcao Para Iniciar Jogo ***/
void jogar(int *qtd_jogador1, int *qtd_jogador2) {
    int jogador = 1, vitoriaX = 0, vitoria0 = 0;
    char jogador1 = 'X', jogador2 = '0';

    FILE *pont_arq;

    do {
        imprimir();
        if (jogador == 1) {
            lerCoordenadas(jogador1);
            jogador++;
            vitoriaX += ganhouPorLinhas(jogador1);
            vitoriaX += ganhouPorColunas(jogador1);
            vitoriaX += ganhouPorDiagPrin(jogador1);
            vitoriaX += ganhouPorDiagSec(jogador1);
        } else {
            lerCoordenadas(jogador2);
            jogador = 1;
            vitoria0 += ganhouPorLinhas(jogador2);
            vitoria0 += ganhouPorColunas(jogador2);
            vitoria0 += ganhouPorDiagPrin(jogador2);
            vitoria0 += ganhouPorDiagSec(jogador2);
        }
        system("CLS");
    } while (vitoriaX == 0 && vitoria0 == 0 && quantVazias() > 0);

    imprimir();

    if (vitoria0 == 1) {
        printf("\nParabens Jogador 2. Voce venceu!!!\n");
        *qtd_jogador2 += 1;
    } else if (vitoriaX == 1) {
        printf("\nParabens Jogador 1. Voce venceu!!!\n");
        *qtd_jogador1 += 1;
    } else {
        printf("\nDeu velha!!!\n");
    }

    /* Arquivos Com Os Ranking | Contendo o Jogador 1 e 2 Mais a Quantidade de Vitorias Deles  */
    pont_arq = fopen("arquivo1.txt", "w");

    fprintf(pont_arq, "O Jogador 1 ganhou %d vezes\n", *qtd_jogador1);
    fprintf(pont_arq, "O jogador 2 ganhou %d vezes", *qtd_jogador2);

    fclose(pont_arq);
}

/*** Menu ***/
int cabecalho() {
    int escolhido;

    printf("--- JOGO DA VELHA ---");
    printf("\n1- Jogar");
    printf("\n2- Ranking");
    printf("\n3- Créditos");
    printf("\n4- Sair\n\n");
    scanf("%d", &escolhido);
    return escolhido;
}

/*** Main ***/
int main() {
    
    setlocale(LC_ALL, "Portuguese");
    
	int opcao;
    int qtd_jogador1 = 0, qtd_jogador2 = 0;
    
	FILE *pont_arq;

    do {
        system("CLS");
        switch (cabecalho()) {
        case 1:
            do {
                system("CLS");
                inicializarMatriz();
                jogar(&qtd_jogador1, &qtd_jogador2);
                printf("\nDigite 1 para jogar novamente ou outro numero para sair: ");
                scanf("%d", &opcao);
            } while (opcao == 1);
            break;
        case 2:
            system("CLS");
            printf("--- RANKING ---\n\n");
            printf("O jogador 1 ganhou %d\n", qtd_jogador1);
            printf("O jogador 2 ganhou %d\n\n", qtd_jogador2);
            break;
        case 3:
            system("CLS");
            printf("--- CREDITOS ---\n\n");
            printf("Marco Antônio\n");
            printf("Vinicius Marinho\n");
            printf("Renan Barbosa\n");
            break;
        case 4:
            exit(0);
            break;
        default:
        	printf("Digite uma opção valida!");
        }
        printf("\nDigite 1 para retornar: ");
        scanf("%d", &opcao);
    } while (opcao == 1);

    return 0;
}

