#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
# define tamanho 5
# define TRUE 1
# define FALSE 0

// Fun��o para trocar luzes acesas para apagadas e vice-versa

int toggle (int x, int y, int z[5][5]) {  // x = linha, y = coluna, z = matriz[l][c]
	
	if (x==0 && y==0){
		z[x][y] = !z[x][y];			// Canto superior esquerdo
		z[x][y+1] = !z[x][y+1];
		z[x+1][y] = !z[x+1][y];
	}
	if (x==0 && y==4){
		z[x][y] = !z[x][y];			// Canto superior direito
		z[x+1][y] = !z[x+1][y];
		z[x][y-1] = !z[x][y-1];
	}
	if (x==4 && y==0){
		z[x][y] = !z[x][y];			// Canto inferior esquerdo
		z[x][y+1] = !z[x][y+1];
		z[x-1][y] = !z[x-1][y];
	}
	if (x==4 && y==4){
		z[x][y] = !z[x][y];			// Canto inferior direito
		z[x][y-1] = !z[x][y-1];
		z[x-1][y] = !z[x-1][y];
	}
	
	if ((x>=1 && x<=3) && (y>=1 && y<=3)) {		// Meio
		z[x][y] = !z[x][y];
		z[x+1][y] = !z[x+1][y];
		z[x][y+1] = !z[x][y+1];
		z[x-1][y] = !z[x-1][y];
		z[x][y-1] = !z[x][y-1];		
	}	
	if ((x==0) && (y >= 1 && y <= 3)){		//Linhas laterais
        z[x][y] = !z[x][y];
        z[x][y-1] = !z[x][y-1];
        z[x][y+1] = !z[x][y+1];
        z[x+1][y] = !z[x+1][y];
    }
   
    if ((x==4) && (y >= 1 && y <= 3)){
        z[x][y] = !z[x][y];
        z[x][y-1] = !z[x][y-1];
        z[x][y+1] = !z[x][y+1];
        z[x-1][y] = !z[x-1][y];
    }
   
    if ((y==0) && (x >= 1 && x <= 3)){
        z[x][y] = !z[x][y];
        z[x-1][y] = !z[x-1][y];
        z[x+1][y] = !z[x+1][y];
        z[x][y+1] = !z[x][y+1];
    }
 
    if ((y==4) && (x >= 1 && x <= 3)){
        z[x][y] = !z[x][y];
        z[x-1][y] = !z[x-1][y];
        z[x+1][y] = !z[x+1][y];
        z[x][y-1] = !z[x][y-1];
    }	
}

//Fun��o de verifica��o caso todas as luzes estejam apagadas

int ganhou (int z[5][5]) {  // Passagem de par�metro da situa��o da matriz
	
	int *p;
	
	for (p = &z[0][0]; p < &z[0][0] + 25; p++) {
		if (*p!=0) {
			return FALSE;
		}
	}
	
	return TRUE;
}

void constroi_menu (){		//Fun��o do menu de op��es
	
	printf("<!DOCTYPE html>\n"
		"<html lang='pt-br'>\n"
		"\n"
		"	<head>\n"
		"		<title>Logical Lights</title>\n"
		"		<link rel='stylesheet' href='http://cap.dc.ufscar.br/~726568/Jogo-Luzes.css'>\n"	// Link do arquivo css 
		"	</head>\n"
		"	\n"
		"	<body background: url(cap.jpg) >\n"
		"		<table>\n");
		
		printf("<p class= 'subtitulo'>""Apague as luzes</p>");
		printf("<br>");
		printf("<br>");
		
		printf("<a class='menu' href= ?nivel=1>Easy</a>");		// Link das escolhas dos quatro n�veis
		printf("<br>");
		printf("<a class='menu' href= ?nivel=2>Medium</a>");
		printf("<br>");
		printf("<a class='menu' href= ?nivel=3>Hard</a>");
		printf("<br>");
		printf("<a class='menu' href= ?nivel=4>Super Hard</a>");
		printf("<br>");
		
}

int carrega_matriz (int z[5][5], int nivel) {
	
	char nome_arquivo[256];
	
	if (nivel==1) {
		
		strcpy(nome_arquivo, "/home/bcc/726568/public_html/facil.julia");
	}
	
	else if (nivel == 2) {
		strcpy(nome_arquivo, "/home/bcc/726568/public_html/medio.julia");
	}
	
	else if (nivel == 3) {
		strcpy(nome_arquivo, "/home/bcc/726568/public_html/dificil.julia");
	}

	FILE *pArquivo = fopen (nome_arquivo, "rb");
	
	fread (z, sizeof(int), 25, pArquivo);
	
	fclose(pArquivo);
	
	printf("<!DOCTYPE html>\n"
		"<html lang='pt-br'>\n"
		"\n"
		"	<head>\n"
		"		<title>Logical Lights</title>\n"
		"		<link rel='stylesheet' href='http://cap.dc.ufscar.br/~726568/Jogo-Luzes.css'>\n"
		"	</head>\n"
		"	<body background: ""cap.jpg"" bgproperties=""fixed""; >\n"
		"		<strong><a class='opcoes' href=\"?nivel=0\">MENU</a></strong> <strong><a class = 'opcoes' href=\"?nivel=%d\">PROXIMO NiVEL</a></strong> <br><br>"
		"		<table align: ""center"">\n", nivel+1);
	
	int linhas, colunas;
	
	char parametros[50];
	strcpy(parametros, "matriz=");
	
	for (linhas=0; linhas<5; linhas++){     // Gera a string de 0 e 1 na url para informar ao client a situa��o da matriz
		for (colunas=0; colunas<5;colunas++) {
			strcat(parametros, z[linhas][colunas] ?  "1" : "0");	// If in line: caso z[linhas][colunas] seja verdadeiro(1) ent�o concatenamos "1", sen�o "0"
		}
	}
	
	for (linhas=0; linhas<5; linhas++){		// Gera o link na matriz e verifica o local clicado (temos um link para cada bot�o)
		printf("<tr>\n");
		for (colunas=0; colunas<5;colunas++) {
			printf("<td class=\"%s\"> <a href='?linha=%d&coluna=%d&nivel=%d&%s'></a></td>\n", z[linhas][colunas] ? "luz-acesa" : "luz-apagada", linhas, colunas, nivel, parametros);
		// Se o bot�o atual for igual a 1 (verdadeiro) � luz acesa, sen�o � luz apagada
		}
		printf("</tr>\n");
	}

}

int constroi_matriz (int z[5][5], int nivel) {		// Fun��o que constroi a matriz
	
	printf("<!DOCTYPE html>\n"
		"<html lang='pt-br'>\n"
		"\n"
		"	<head>\n"
		"		<title>Logical Lights</title>\n"
		"		<link rel='stylesheet' href='http://cap.dc.ufscar.br/~726568/Jogo-Luzes.css'>\n"
		"	</head>\n"
		"	<body background: ""cap.jpg"" bgproperties=""fixed""; >\n"
		"		<strong><a class='opcoes' href=\"?nivel=0\">MENU</a></strong> <strong><a class = 'opcoes' href=\"?nivel=%d\">PROXIMO NiVEL</a></strong> <br><br>"
		"		<table align: ""center"">\n", nivel+1);
		
		int linhas, colunas;
		
		char parametros[50];
		strcpy(parametros, "matriz=");
		
		for (linhas=0; linhas<5; linhas++){     // Gera a string de 0 e 1 na url para informar ao client a situa��o da matriz
			for (colunas=0; colunas<5;colunas++) {
				strcat(parametros, z[linhas][colunas] ?  "1" : "0");	// If in line: caso z[linhas][colunas] seja verdadeiro(1) ent�o concatenamos "1", sen�o "0"
			}
		}
		
		for (linhas=0; linhas<5; linhas++){		// Gera o link na matriz e verifica o local clicado (temos um link para cada bot�o)
			printf("<tr>\n");
			for (colunas=0; colunas<5;colunas++) {
				printf("<td class=\"%s\"> <a href='?linha=%d&coluna=%d&nivel=%d&%s'></a></td>\n", z[linhas][colunas] ? "luz-acesa" : "luz-apagada", linhas, colunas, nivel, parametros);
			// Se o bot�o atual for igual a 1 (verdadeiro) � luz acesa, sen�o � luz apagada
			}
			printf("</tr>\n");
		}
		
		FILE *pArquivo = fopen ("facil.julia", "w");
		fwrite (z,sizeof(int), 25, pArquivo);
		
		fclose (pArquivo);
}

void resultado (int nivel) {
	
	printf("<!DOCTYPE html>\n"
		"<html lang='pt-br'>\n"
		"\n"
		"	<head>\n"
		"		<title>Logical Lights</title>\n"
		"		<link rel='stylesheet' href='http://cap.dc.ufscar.br/~726568/Jogo-Luzes.css'>\n"
		"	</head>\n"
		"	\n"
		"	<body>\n"
		"		<h1>Parabens, voce ganhou!</h1>\n"
		"		<a href= '?nivel=%d'></a>"
		"	</body>", nivel);
		

}


int main () {
	
	srand((unsigned)time(NULL));
	
	printf("Content-type: text/html\n\n");
	
	char *parametros, matrizParametro[25];

	parametros = getenv("QUERY_STRING");    // Pega os parametros da URL
	//parametros = (char*) malloc(256);
	//strcpy(parametros, "nivel=1");
	
	int matriz[tamanho][tamanho];
	int l, c, caux, laux, cont=0, tentativas=0, nivel, voltar, proximo;
	
	if(sscanf(parametros, "linha=%d&coluna=%d&nivel=%d&matriz=%s", &l,&c, &nivel, &matrizParametro) == 4) {		// L� a URL e checa as vari�veis, atribuindo nos par�metros
		int i = 0;
		for (laux = 0; laux < 5; laux++) {		// Pega da URL os 0 e 1 e converte na nossa matriz, salvando o status do jogo 
			for (caux = 0; caux < 5; caux++) {
				matriz[laux][caux] = matrizParametro[i] == '1' ? 1 : 0;
				i++;
			}
		}
		
		toggle (l, c, matriz);		// Chama a fun��o toggle, que acende ou apaga
		constroi_matriz (matriz, nivel);	// Chama a fun��o que constroi a matriz
		
	} else if(sscanf(parametros, "nivel=%d", &nivel) >= 0) {
	
		// Povoando a matriz com 1 (aceso)
		
		for (c=0; c < tamanho; c++) {
			for (l=0; l < tamanho; l++) {
				matriz[l][c] = 1;
			}
		}
		
		if (nivel==0 || nivel>4) {
			constroi_menu();
		}
		
		if (nivel==1) {			// N�vel F�cil
			matriz[0][0] = 0;
			matriz[0][2] = 0;
			matriz[0][4] = 0;
			matriz[1][2] = 0;
			matriz[2][0] = 0;
			matriz[2][2] = 0;
			matriz[2][4] = 0;
			matriz[3][1] = 0;
			matriz[3][3] = 0;
			matriz[4][1] = 0;
			matriz[4][3] = 0;
			
			carrega_matriz (matriz, nivel);
		}
		
		if (nivel==2) {			// N�vel M�dio
			matriz[0][2] = 0;
			matriz[1][0] = 0;
			matriz[1][1] = 0;
			matriz[1][2] = 0;
			matriz[1][3] = 0;
			matriz[1][4] = 0;
			matriz[2][2] = 0;
			matriz[3][0] = 0;
			matriz[3][1] = 0;
			matriz[3][2] = 0;
			matriz[3][3] = 0;
			matriz[4][2] = 0;
			matriz[4][3] = 0;
			matriz[4][4] = 0;
			
			carrega_matriz (matriz, nivel);
		}
		
		if (nivel==3){			// Nivel Dif�cil
			matriz[1][0] = 0;
			matriz[1][1] = 0;
			matriz[1][3] = 0;
			matriz[1][4] = 0;
			matriz[2][0] = 0;
			matriz[2][1] = 0;
			matriz[2][3] = 0;
			matriz[2][4] = 0;
			matriz[3][0] = 0;
			matriz[3][1] = 0;
			matriz[3][3] = 0;
			matriz[3][4] = 0;
			
			carrega_matriz (matriz, nivel);
		}
		
		if (nivel==4) {
		
			while (12 > cont) {		// 12 luzes aleat�rias come�ar�o acesas
			
				l = rand () %5;
				c = rand () %5;

				if (matriz[l][c] == 1) {  // apagado
					matriz[l][c] = 0;	 // aceso	
					cont ++;	
				}
			}
			constroi_matriz (matriz, nivel);
		}
	
	}
	
	else {
		constroi_menu();
	}
	
	if(ganhou(matriz)==TRUE){
		
		sscanf(parametros, "nivel=%d", &nivel) >= 0;
		resultado(nivel);
	}
	
	
	return 0;
}
