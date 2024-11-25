#include<stdio.h>
#include<conio.h>
#include <stdlib.h>

void mostraTitulo();
void mostraInstrucoes();
void iniciar(int quadro[][3]);
char preencheBloco(int quadro);
void montaTabuleiro(int quadro[][3]);
void realizaMovimento(int quadro[][3], int);
int checaContinue(int *quadro[3]);
int checaVitoria(int *quadro[3]);
int jogo(int quadro[][3]); 
void placar(int,int &, int &);
int jogarNovamente();
void mostraFinal();

int main(){
    //matriz 3x3 que armazena os valores do jogo
    int quadro [3][3];
    int contador = 0,jogador1=0,jogador2=0,resultado;
    do
    {
        mostraTitulo();
        mostraInstrucoes();
        iniciar(quadro);
        resultado = jogo(quadro);
        montaTabuleiro(quadro);
        placar(resultado,jogador1,jogador2);
        contador = jogarNovamente();
    } while (contador==1);
    mostraFinal();    
    return 0;
}

//funcao que mostra o titulo do jogo
void mostraTitulo(){
       char art[20][200] = { 
        "     _____   ______    ______    ______         _______    ______         __     __  ________  __        __    __   ______  \n",
        "    |     \\ /      \\  /      \\  /      \\       |       \\  /      \\       |  \\   |  \\|        \\|  \\      |  \\  |  \\ /      \\ \n",
        "     \\$$$$$|  $$$$$$\\|  $$$$$$\\|  $$$$$$\\      | $$$$$$$\\|  $$$$$$\\      | $$   | $$| $$$$$$$$| $$      | $$  | $$|  $$$$$$\\\n",
        "       | $$| $$  | $$| $$ __\\$$| $$  | $$      | $$  | $$| $$__| $$      | $$   | $$| $$__    | $$      | $$__| $$| $$__| $$\n",
        " __    | $$| $$  | $$| $$|    \\| $$  | $$      | $$  | $$| $$    $$       \\$$\\ /  $$| $$  \\   | $$      | $$    $$| $$    $$\n",
        " |  \\  | $$| $$  | $$| $$ \\$$$$| $$  | $$      | $$  | $$| $$$$$$$$        \\$$\\  $$ | $$$$$   | $$      | $$$$$$$$| $$$$$$$$\n",
        " | $$__| $$| $$__/ $$| $$__| $$| $$__/ $$      | $$__/ $$| $$  | $$         \\$$ $$  | $$_____ | $$_____ | $$  | $$| $$  | $$\n",
        "  \\$$    $$ \\$$    $$ \\$$    $$ \\$$    $$      | $$    $$| $$  | $$          \\$$$   | $$     \\| $$     \\| $$  | $$| $$  | $$\n",
        "   \\$$$$$$   \\$$$$$$   \\$$$$$$   \\$$$$$$        \\$$$$$$$  \\$$   \\$$           \\$     \\$$$$$$$$ \\$$$$$$$$ \\$$   \\$$ \\$$   \\$$\n",
        "                                                                                                                           \n",
		"  _______                             __       __  __       __   ______  \n"
		" \t\t\t\t\t  _______                             __       __  __       __   ______  \n",
		" |       \\                           |  \\     /  \\|  \\     /  \\ /      \\ \n",
		" | $$$$$$$\\  ______    ______        | $$\\   /  $$| $$\\   /  $$|  $$$$$$\\\n",
		" | $$__/ $$ /      \\  /      \\       | $$$\\ /  $$$| $$$\\ /  $$$| $$___\\$$\n",
		" | $$    $$|  $$$$$$\\|  $$$$$$\\      | $$$$\\  $$$$| $$$$\\  $$$$ \\$$    \\ \n",
		" | $$$$$$$ | $$  | $$| $$   \\$$      | $$\\$$ $$ $$| $$\\$$ $$ $$ _\\$$$$$$\\\n",
		" | $$      | $$__/ $$| $$            | $$ \\$$$| $$| $$ \\$$$| $$|  \\__| $$\n",
		" | $$       \\$$    $$| $$            | $$  \\$ | $$| $$  \\$ | $$ \\$$    $$\n",
		"  \\$$        \\$$$$$$  \\$$             \\$$      \\$$ \\$$      \\$$  \\$$$$$$ "};

    for (int i = 0; i < sizeof(art) / sizeof(art[0]); i++) {
        printf("\t\t\t\t\t%s", art[i]);

    }
	  }

//funcao que mostra as instrucoes do jogo
void mostraInstrucoes() {
    int mostraTutorial;
    printf("\n\nDeseja mostrar o tutorial? 1 para Sim e 0 para Nao: ");
    scanf("%d",&mostraTutorial);
    if(mostraTutorial==1){
        printf("===================================\n");
        printf("          INSTRUCOES DO JOGO      \n");
        printf("===================================\n");
        printf("1. O jogo eh jogado por dois jogadores.\n");
        printf("2. Um jogador eh 'X' e o outro eh 'O'.\n");
        printf("3. O tabuleiro eh uma grade 3x3.\n");
        printf("4. Os jogadores se alternam em suas jogadas.\n");
        printf("5. Para fazer uma jogada, digite a linha e a coluna (0-2).\n");
        printf("6. O objetivo e alinhar tres de suas marcas (X ou O) em uma linha.\n");
        printf("   Isso pode ser feito:\n");
        printf("   - Horizontalmente\n");
        printf("   - Verticalmente\n");
        printf("   - Diagonalmente\n");
        printf("7. O jogo termina quando um jogador vence ou o tabuleiro esta cheio (empate).\n");
        printf("8. Divirta-se!\n");
        printf("===================================\n");
        getch();
    }
}

//inicia o tabuleiro colocando 0 em todas as casas
void iniciar(int quadro[][3]){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
           quadro[i][j]=0;
        }
    }
}

//coloca ' ' se o valor eh 0, coloca X se o valor eh 1, e se for um valor diferente, coloca O
char preencheBloco(int bloco){
    if(bloco == 0){
        return ' ';
    }else if (bloco==1)
    {
        return 'X';
    } else{
        return 'O';
    }
}

//monta o tabuleiro todo
void montaTabuleiro(int quadro[][3]){
	system("cls");
    for (int linha = 0; linha < 3; linha++)
    {
        //talvez apagar as linhas anteriores quando for preencher um novo quadro
        printf("\n %c | %c | %c \n",preencheBloco(quadro[linha][0]),
            preencheBloco(quadro[linha][1]),preencheBloco(quadro[linha][2]));
        if (linha!=2)
        {
            printf("___ ___ ___\n");
        }   
    }   
}

//funcao que realiza as jogadas
void realizaMovimento(int quadro[][3], int jogador){
    int linha, coluna, checa;
    do
    {
    printf("Linha: ");
    scanf("%d",&linha);
    printf("Coluna: ");
    scanf("%d",&coluna);
    linha--;coluna--;
    checa = quadro[linha][coluna] || linha<0 || linha>2 || coluna<0 || coluna>2;
    if(checa){
        printf("Essa casa nao esta vazia ou esta fora do intervalo 3x3\n");
    }
    } while (checa);
    if (jogador==0)
    {
        quadro[linha][coluna]=1;
    } else{
        quadro[linha][coluna]=-1;
    }
}

//funcao que checa se ainda tem espaco em branco no quadro
int checaContinue(int quadro[][3]){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if(quadro[i][j]==0){
                return 1;
            }  
        }
    }
    return 0;
}

int checaVitoria(int quadro[][3]){
    int linha, coluna,soma;
    //verificacao de vitoria em linha
    for(linha=0;linha<3;linha++){
        soma=0;
        for (coluna = 0; coluna<3; coluna++)
        {
            soma += quadro[linha][coluna];
        } 
        if(soma==3){
            return 1;
        }
        if (soma==-3)
        {
            return -1;
        }
    }
    //verificacao de vitoria em coluna
    for (coluna = 0; coluna<3; coluna++)
    {
        soma=0;
        for (linha = 0; linha<3; linha++)
        {
            soma+=quadro[linha][coluna];
            if (soma==3)
            {
                return 1;
            }
            if(soma==-3){
                return -1;
            }
        }
    }
    //verificacao de vitoria em diagonal
    soma=0;
    for(linha = 0;linha<3;linha++){
        soma+= quadro[linha][linha];
    }
    if(soma==3){
        return 1;
    }
    if (soma==-3)
    {
       return -1;
    }
    soma =quadro[0][2]+quadro[1][1]+quadro[2][0];
    if(soma==3){
        return 1;
    }
    if (soma==-3)
    {
       return -1;
    }
    return 0;
}

//funcao que realiza o jogo, juntando as funcoes de jogo aqui
int jogo(int quadro[][3]){
    int turno =0, continuar, vitoria;
   do
   {
        montaTabuleiro(quadro);
        printf("Vez do Jogador %d\n",turno%2+1);
        realizaMovimento(quadro,turno%2);
        turno++;
        continuar = checaContinue(quadro);
        vitoria = checaVitoria(quadro);
   } while (continuar && !vitoria);
    if(vitoria==1){
        return 1;
    } else if (vitoria==-1)
    {
        return 2;
    } else{
    	
    }
    return 0;
}

//funcao que mostra o placar do jogo
void placar(int resultado, int &jogador1,int &jogador2){
    if(resultado==1){
        jogador1++;
        printf("Jogador 1 ganhou!!!\n");
    }
    else if (resultado==2)
    {
        jogador2++;
        printf("Jogador 2 ganhou!!!\n");
    }
    else if(resultado==0){
    	printf("Empate\n");
	}
    printf("Placar: Jogador 1| %d X %d |Jogador 2",jogador1,jogador2);
}

int jogarNovamente(){
    int contador;
    printf("\nDeseja jogar novamente?\n");
    printf("0- Nao\n");
    printf("1- Jogar novamente");
    scanf("%d",&contador);
    return contador;
}

//funcao que mostra mensagem final ao fechar o jogo
void mostraFinal(){
   char art[20][400] = {
        " \t\t\t\t ________  __                            __                     _____                               \n",
        " \t\t\t\t|        \\|  \\                          |  \\                   |     \\                              \n",
        " \t\t\t\t| $$$$$$$$ \\$$ ______ ____          ____| $$  ______            \\$$$$$  ______    ______    ______ \n",
        " \t\t\t\t| $$__    |  \\|      \\    \\        /      $$ /      \\             | $$ /      \\  /      \\  /      \\ \n",
        " \t\t\t\t| $$  \\   | $$| $$$$$$\\$$$$\\      |  $$$$$$$|  $$$$$$\\       __   | $$|  $$$$$$\\|  $$$$$$\\|  $$$$$$\n",
        " \t\t\t\t| $$$$$   | $$| $$ | $$ | $$      | $$  | $$| $$    $$      |  \\  | $$| $$  | $$| $$  | $$| $$  | $$\n",
        " \t\t\t\t| $$      | $$| $$ | $$ | $$      | $$__| $$| $$$$$$$$      | $$__| $$| $$__/ $$| $$__| $$| $$__/ $$\n",
        " \t\t\t\t| $$      | $$| $$ | $$ | $$       \\$$    $$ \\$$     \\       \\$$    $$ \\$$    $$ \\$$    $$ \\$$    $$\n",
        " \t\t\t\t \\$$       \\$$ \\$$  \\$$  \\$$        \\$$$$$$$  \\$$$$$$$        \\$$$$$$   \\$$$$$$  _\\$$$$$$$  \\$$$$$$ \n",
        " \t\t\t\t                                                                                |  \\__| $$             \n"
  	"  _______                             __       __  __       __   ______  \n"
		" \t\t\t\t\t  _______                             __       __  __       __   ______  \n",
		" |       \\                           |  \\     /  \\|  \\     /  \\ /      \\ \n",
		" | $$$$$$$\\  ______    ______        | $$\\   /  $$| $$\\   /  $$|  $$$$$$\\\n",
		" | $$__/ $$ /      \\  /      \\       | $$$\\ /  $$$| $$$\\ /  $$$| $$___\\$$\n",
		" | $$    $$|  $$$$$$\\|  $$$$$$\\      | $$$$\\  $$$$| $$$$\\  $$$$ \\$$    \\ \n",
		" | $$$$$$$ | $$  | $$| $$   \\$$      | $$\\$$ $$ $$| $$\\$$ $$ $$ _\\$$$$$$\\\n",
		" | $$      | $$__/ $$| $$            | $$ \\$$$| $$| $$ \\$$$| $$|  \\__| $$\n",
		" | $$       \\$$    $$| $$            | $$  \\$ | $$| $$  \\$ | $$ \\$$    $$\n",
		"  \\$$        \\$$$$$$  \\$$             \\$$      \\$$ \\$$      \\$$  \\$$$$$$ "};

    for (int i = 0; i < sizeof(art) / sizeof(art[0]); i++) {
        printf("%s", art[i]);
    }
    getch();
}


