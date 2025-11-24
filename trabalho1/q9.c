#include<stdio.h>
#include <stdlib.h>

#define BARCOS 5

void q9();

int main(){
    //Questão Extra
    q9();
}

//Q9 = jogo de batalha naval
void tabuleiro(char tabuleiro[10][10], int opcao) {
    printf("   1   2   3   4   5   6   7   8   9   10\n");
    char c = 'A';

    for (int i = 0; i < 10; i++) {
        printf("%c  ", c);
        c++;
        
        for (int j = 0; j < 10; j++) {
            if(opcao == 2 && tabuleiro[i][j] == 'N')
                printf(" ");
            else
                printf("%c", tabuleiro[i][j]);

            if (j < 9) 
                printf(" | ");
        }

        printf("\n");
        printf("  ----------------------------------------\n");
    }
}

int validarEntrada(char tabuleiro[10][10], char celula[4], int *coluna, int *linha) {
    int valida = 1;

    if(*coluna < 0 || *coluna > 9){
      valida = 0;
    }else{
        if(celula[0] >= 'A' && celula[0] <= 'J')
            *linha = celula[0] - 'A';
        else if(celula[0] >= 'a' && celula[0] <= 'j')
            *linha = celula[0] - 'a';
        else
            valida = 0;
    }

    return valida;
}

void posicionarBarcos(char tabuleiro[10][10], char celulaInicio[4], char celulaFim[4], int tamBarco, int *validaInicio, int *validaFim, int *validaPosicao) {
    int colunaInicio = atoi(&celulaInicio[1]) - 1;
    int linhaInicio;

    *validaInicio = validarEntrada(tabuleiro, celulaInicio, &colunaInicio, &linhaInicio);

    int colunaFim, linhaFim;

    if(tamBarco != 1){
        colunaFim = atoi(&celulaFim[1]) - 1;

        *validaFim = validarEntrada(tabuleiro, celulaFim, &colunaFim, &linhaFim);
    }else{
        *validaFim = 1;
    }

    *validaPosicao = 0;
    if(*validaInicio == 1 && *validaFim == 1){
        if(tamBarco == 1){
            if(tabuleiro[linhaInicio][colunaInicio] != 'N'){
                tabuleiro[linhaInicio][colunaInicio] = 'N';
                *validaPosicao = 1;
            }
        }else{
            if(colunaInicio == colunaFim && linhaInicio < linhaFim){
                int i;
                for(i = linhaInicio; i <= linhaFim && tabuleiro[i][colunaInicio] == ' '; i++);

                if(i > linhaFim)
                    for(int i = linhaInicio; i <= linhaFim; i++){
                        tabuleiro[i][colunaInicio] = 'N';
                        *validaPosicao = 1;
                    }   
            }
            else if(colunaInicio == colunaFim && linhaInicio > linhaFim){
                int i;
                for(i = linhaFim; i <= linhaInicio && tabuleiro[i][colunaInicio] == ' '; i++);

                if(i > linhaInicio)
                    for(int i = linhaFim; i <= linhaInicio; i++){
                        tabuleiro[i][colunaInicio] = 'N';
                        *validaPosicao = 1;
                    }  
            }
            else if(linhaInicio == linhaFim && colunaInicio < colunaFim){
                int i;
                for(i = colunaInicio; i <= colunaFim && tabuleiro[linhaInicio][i] == ' '; i++);

                if(i > colunaFim)
                    for(int i = colunaInicio; i <= colunaFim; i++){
                        tabuleiro[linhaInicio][i] = 'N';
                        *validaPosicao = 1;
                    }  
            }
            else if(linhaInicio == linhaFim && colunaInicio > colunaFim){
                int i;
                for(i = colunaFim; i <= colunaInicio && tabuleiro[linhaInicio][i] == ' '; i++);

                if(i > colunaInicio)
                    for(int i = colunaFim; i <= colunaInicio; i++){
                        tabuleiro[linhaInicio][i] = 'N';
                        *validaPosicao = 1;
                    }  
            }
        }
    }
}

void posicaoDosBarcos(char tabuleiro[10][10], int jogador) {
    for(int i = 1; i <= BARCOS; ){
        int tamBarco;

        if(i == 1)
            tamBarco = 4;
        else if(i == 2)
            tamBarco = 3;
        else if(i >= 3 && i < 6)
            tamBarco = 1;
        else
            tamBarco = 2;

        char celulaInicio[4] = "\0";
        char celulaFim[4] = "\0";

        if(tamBarco == 1){
            printf("Jogador %d, informe a posição do seu barco de tamanho %d: ", jogador, tamBarco);
            scanf("%3s", celulaInicio);
        }else{
            printf("Jogador %d, informe a posição inicial e final do seu barco de tamanho %d: ", jogador, tamBarco);
            scanf("%3s", celulaInicio);
            scanf("%3s", celulaFim);
        }

        int validaInicio, validaFim, validaPosicao;
        posicionarBarcos(tabuleiro, celulaInicio, celulaFim, tamBarco, &validaInicio, &validaFim, &validaPosicao);

        if(!validaInicio)
            printf("Posição inicial Inválida!\n");
        else if(!validaFim)
            printf("Posição final Inválida!\n");
        else if(!validaPosicao)
            printf("Posição Inválida!\n");
        else
            i++;
    }
}

void tiro(char tabuleiro[10][10], int jogador, int *valida){
    char celula[4] = "\0";

    printf("Jogador %d, informe a posição em que deseja atirar: ", jogador);
    scanf("%3s", celula);

    int coluna = atoi(&celula[1]) - 1;
    int linha;

    *valida = validarEntrada(tabuleiro, celula, &coluna, &linha);

    if(*valida == 1){
        if(tabuleiro[linha][coluna] == 'N')
            tabuleiro[linha][coluna] = 'O';
        else
            tabuleiro[linha][coluna] = 'X';
    }
}

void vitoria(char tabuleiro[10][10], int *vencedor){
    int contador = 0;

    for(int i = 0; i < 10; i++)
      for(int j = 0; j < 10; j++)
        if(tabuleiro[i][j] == 'N')
            contador++;

    if(contador == 0)   
        *vencedor = 1;
}

void q9()
{
    char tabuleiro1[10][10];
    char tabuleiro2[10][10];
    for(int i = 0; i < 10; i++)
      for(int j = 0; j < 10; j++){
        tabuleiro1[i][j] = ' ';
        tabuleiro2[i][j] = ' ';
      }

    posicaoDosBarcos(tabuleiro1, 1);
    posicaoDosBarcos(tabuleiro2, 2);
    
    int jogador = 1;
    int vencedor = 0;

    while(vencedor == 0){
        int valida = 1;
        int opcao;

        printf("Jogador %d, Digite a Opção:\n", jogador);
        printf("1 - Listar o Próprio Tabuleiro\n");
        printf("2 - Listar o Tabuleiro Adversário\n");
        printf("3 - Atirar\n");
        scanf("%d",&opcao);

        switch(opcao){
            case 1:{
                if(jogador == 1)
                    tabuleiro(tabuleiro1, opcao);
                else
                    tabuleiro(tabuleiro2, opcao);
                break;
            }
            case 2:{
                if(jogador == 1)
                    tabuleiro(tabuleiro2, opcao);
                else
                    tabuleiro(tabuleiro1, opcao);
                break;
            }
            case 3:{
                if(jogador == 1)
                    tiro(tabuleiro2, jogador, &valida);
                else
                    tiro(tabuleiro1, jogador, &valida);
                break;
            }
        }
        
        if(jogador == 1){
            vitoria(tabuleiro2, &vencedor);

            if(vencedor)
                printf("O Jogador 1 Venceu!");
        }else{
            vitoria(tabuleiro1, &vencedor);
            if(vencedor)
                printf("O Jogador 2 Venceu!");
        }

        if(valida){
            if(jogador == 1)
                jogador = 2;
            else
                jogador = 1;
        }
    }
}
