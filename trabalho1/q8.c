#include<stdio.h>

void q8();

int main(){
    //Questão Extra
    q8();
}

//Q8 = jogo da velha
int vitoria(char jogoDaVelha[3][3]) {
  for(int i = 0; i < 3; i++)
    if(jogoDaVelha[i][0] == 'X' && jogoDaVelha[i][1] == 'X' && jogoDaVelha[i][2] == 'X')
      return 1;
      
  for(int i = 0; i < 3; i++)
    if(jogoDaVelha[0][i] == 'X' && jogoDaVelha[1][i] == 'X' && jogoDaVelha[2][i] == 'X')
      return 1;

  if(jogoDaVelha[0][0] == 'X' && jogoDaVelha[1][1] == 'X' && jogoDaVelha[2][2] == 'X')
    return 1;

  if(jogoDaVelha[0][2] == 'X' && jogoDaVelha[1][1] == 'X' && jogoDaVelha[2][0] == 'X')
    return 1;

  for(int i = 0; i < 3; i++)
    if(jogoDaVelha[i][0] == 'O' && jogoDaVelha[i][1] == 'O' && jogoDaVelha[i][2] == 'O')
      return 2;
      
  for(int i = 0; i < 3; i++)
    if(jogoDaVelha[0][i] == 'O' && jogoDaVelha[1][i] == 'O' && jogoDaVelha[2][i] == 'O')
      return 2;

  if(jogoDaVelha[0][0] == 'O' && jogoDaVelha[1][1] == 'O' && jogoDaVelha[2][2] == 'O')
    return 2;

  if(jogoDaVelha[0][2] == 'O' && jogoDaVelha[1][1] == 'O' && jogoDaVelha[2][0] == 'O')
    return 2;

  return 0;
}

void tabuleiro(char jogoDaVelha[3][3]) {
    printf("   1   2   3\n");
    printf("A  %c | %c | %c\n", jogoDaVelha[0][0], jogoDaVelha[0][1], jogoDaVelha[0][2]);
    printf("  ------------\n");
    printf("B  %c | %c | %c\n", jogoDaVelha[1][0], jogoDaVelha[1][1], jogoDaVelha[1][2]);
    printf("  ------------\n");
    printf("C  %c | %c | %c\n", jogoDaVelha[2][0], jogoDaVelha[2][1], jogoDaVelha[2][2]);
}

 void preencherTabuleiro(char jogoDaVelha[3][3], int jogador, char celula[3]) {
    int coluna = celula[1] - '1';
    int linha;

    if(coluna < 0 || coluna > 2){
      printf("Célula Inválida!\n");
      return;
    } 

    if(celula[0] == 'a' || celula[0] == 'A') 
      linha = 0;
    else if(celula[0] == 'b' || celula[0] == 'B') 
      linha = 1;
    else if(celula[0] == 'c' || celula[0] == 'C') 
      linha = 2;
    else{
      printf("Célula Inválida!\n");
      return;
    }

    if(jogoDaVelha[linha][coluna] != ' '){
      printf("Célula Inválida!\n");
      return;
    }

    jogoDaVelha[linha][coluna] = (jogador == 1) ? 'X' : 'O';
 }

void q8()
{
    char jogoDaVelha[3][3];
    for(int i = 0; i < 3; i++)
      for(int j = 0; j < 3; j++)
        jogoDaVelha[i][j] = ' ';

    int qtdJogadas = 0;
    int ganhador = 0;
    
    while(qtdJogadas <= 9 && ganhador == 0){
      printf("\n");
        tabuleiro(jogoDaVelha);

      ganhador = vitoria(jogoDaVelha);
      
      if(ganhador == 1)
        printf("O Jogador 1 Ganhou!");
      else if(ganhador == 2)
        printf("O Jogador 2 Ganhou!");
      else{
        int jogador;
        if(qtdJogadas % 2 != 0)
          jogador = 2;
        else
          jogador = 1;

        if(jogador == 1)
          printf("Jogador 1, informe sua jogada: ");
        else
          printf("Jogador 2, informe sua jogada: ");

        char celula[3];
        scanf("%s", celula);

        preencherTabuleiro(jogoDaVelha, jogador, celula);

        qtdJogadas = 0;
        for(int i = 0; i < 3; i++)
          for(int j = 0; j < 3; j++)
            if(jogoDaVelha[i][j] != ' ')
              qtdJogadas++;
      }
    }

    if(qtdJogadas == 9)
      printf("Ninguém Ganhou!");
}