#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
# define tamanho 5
# define TRUE 1
# define FALSE 0

// Função para trocar luzes acesas para apagadas e vice-versa

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

//Função de verificação caso todas as luzes estejam apagadas

int ganhou (int z[5][5]) {  // Passagem de parâmetro da situação da matriz
	
	int *p;
	
	for (p = &z[0][0]; p < &z[0][0] + 25; p++) {
		if (*p!=0) {
			return FALSE;
		}
	}
	
	return TRUE;
}

void constroi_menu (){		//Função do menu de opções
	
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
		
		printf("<a class='menu' href= ?nivel=1>Easy</a>");		// Link das escolhas dos quatro níveis
		printf("<br>");
		printf("<a class='menu' href= ?nivel=2>Medium</a>");
		printf("<br>");
		printf("<a class='menu' href= ?nivel=3>Hard</a>");
		printf("<br>");
		printf("<a class='menu' href= ?nivel=4>Super Hard</a>");
		printf("<br>");
		
}

int constroi_matriz (int z[5][5]) {		// Função que constroi a matriz
	
	printf("<!DOCTYPE html>\n"
		"<html lang='pt-br'>\n"
		"\n"
		"	<head>\n"
		"		<title>Logical Lights</title>\n"
		"		<link rel='stylesheet' href='http://cap.dc.ufscar.br/~726568/Jogo-Luzes.css'>\n"
		"	</head>\n"
		"	\n"
		"	<body background: ""cap.jpg"" bgproperties=""fixed""; >\n"
		"		<table align: ""center"">\n");
		int linhas, colunas;
		
		char parametros[50];
		strcpy(parametros, "matriz=");
		
		for (linhas=0; linhas<5; linhas++){     // Gera a string de 0 e 1 na url para informar ao client a situação da matriz
			for (colunas=0; colunas<5;colunas++) {
				strcat(parametros, z[linhas][colunas] ?  "1" : "0");	// If in line: caso z[
			}
		}
		
		for (linhas=0; linhas<5; linhas++){
			printf("<tr>\n");
			for (colunas=0; colunas<5;colunas++) {
				printf("<td class=\"%s\"> <a href='?linha=%d&coluna=%d&%s'></a></td>\n", z[linhas][colunas] ? "luz-acesa" : "luz-apagada", linhas, colunas, parametros);
			// Se o botão atual for igual a 1 (verdadeiro) é luz acesa, senão é luz apagada
			}
			printf("</tr>\n");
		}
}

void resultado () {
	
	printf("<!DOCTYPE html>\n"
		"<html lang='pt-br'>\n"
		"\n"
		"	<head>\n"
		"		<title>Logical Lights</title>\n"
		"		<link rel='stylesheet' href='http://cap.dc.ufscar.br/~726568/Jogo-Luzes.css'>\n"
		"	</head>\n"
		"	\n"
		"	<body>\n"
		"		<h1 style=""text-align:center;"">Parabéns, você ganhou!</h1>\n"
		"	</body>");
}

int main () {
	
	srand((unsigned)time(NULL));
	
	printf("Content-type: text/html\n\n");
	
	char *parametros, matrizParametro[25];

	parametros = getenv("QUERY_STRING");    // pega os parametros da URL
	
	int matriz[tamanho][tamanho];
	int l, c, caux, laux, cont=0, tentativas=0, nivel;
	
	if(sscanf(parametros, "linha=%d&coluna=%d&matriz=%s", &l,&c, &matrizParametro) == 3) {
		int i = 0;
		for (laux = 0; laux < 5; laux++) {
			for (caux = 0; caux < 5; caux++) {
				matriz[laux][caux] = matrizParametro[i] == '1' ? 1 : 0;
				i++;
			}
		}
		
		toggle (l, c, matriz);
		constroi_matriz (matriz);
		
	} else if(sscanf(parametros, "nivel=%d", &nivel) >= 0) {
		
		// Povoando a matriz com 1
		
		for (c=0; c < tamanho; c++) {
			for (l=0; l < tamanho; l++) {
				matriz[l][c] = 1;
			}
		}
		
		if (nivel==1) {			// Nível Fácil
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
		}
		
		if (nivel==2) {			// Nível Médio
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
		}
		
		if (nivel==3){			// Nivel Difícil
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
		}
		
		if (nivel==4) {
		
			while (12 > cont) {		// 12 luzes aleatórias começarão acesas
			
				l = rand () %5;
				c = rand () %5;

				if (matriz[l][c] == 1) {  // apagado
					matriz[l][c] = 0;	 // aceso	
					cont ++;	
				}
			}
		}
		
		constroi_matriz (matriz);
	}
	
	else {
		constroi_menu();
	}
	
	if(ganhou(matriz)==TRUE){
		
		resultado();
	}
	
	return 0;
}
