/**
* Auto Instrucional de Estrutura de Dados 2 - 1/2017: Parte 1
* Feito por Gabriel Alves Silva e Gabriel da Silva Cavalcante
*/

#include <stdio.h>
#include <stdlib.h>
#include "imagemSatelite.h"

/*
* Verifica se o carectere de valor de uma c�lula � v�lido. Uma c�lula s�
* pode possuir valores iguais a '0' ou '1'.
*/
int caractereIsValido(char c){
	return c == '0' || c == '1';
}

/*
* Cria uma nova matriz para a imagem de sat�lite respeitando as 
* defini��es da matriz encontradas na primeira linha do arquivo de imagem.
*/
int criarMatriz(IMAGEM_SATELITE *imagem, FILE *arq){
	
	int qtdLinhas, qtdColunas;

	char c;
	int i;

	//Obter n�mero linhas

	char *strQtdLinhas = malloc(sizeof(char) * 100);

	for(i = 0, c =  fgetc(arq); c != ' ' && c != EOF; c = fgetc(arq), i++){
		strQtdLinhas[i] = c;
		
		//Teve quebra de linha antes de informar a quantidade de colunas
		if(c == '\n'){
			return -1;
		}
	}

	qtdLinhas = atoi(strQtdLinhas);
	free(strQtdLinhas);

	//Obter n�mero colunas
	
	char* strQtdColunas = malloc(sizeof(char) * 100);
	for(i = 0, c =  fgetc(arq); c != '\n' && c != EOF; c = fgetc(arq), i++){
		strQtdColunas[i] = c;
	}

	qtdColunas = atoi(strQtdColunas);
	free(strQtdColunas);

	imagem->qtdLinhas = qtdLinhas;
	imagem->qtdColunas = qtdColunas;
	imagem->matriz = malloc(sizeof(CELULA*) * qtdLinhas);

	for(i = 0; i < qtdLinhas; i++){
		imagem->matriz[i] = malloc(sizeof(CELULA) * qtdColunas);
	}

	//Popula a matriz
	return popularMatriz(imagem, arq);
}

/*
* Popula a matriz da imagem com os valores presentes no arquivo.
*/
int popularMatriz(IMAGEM_SATELITE *imagem, FILE *arq){
	int i, j;
	char c;

	for(i = 0; i < imagem->qtdLinhas; i++){
		for(j = 0; j < imagem->qtdColunas; j++){

			//Pular espa�os
			do{
				c = fgetc(arq);
				if(c == EOF) return -1;
			}while(!caractereIsValido(c));

			CELULA celula;
			celula.valor = (int) c - 48;
			celula.jaVerificado = 0;

			imagem->matriz[i][j] = celula;
		}

		//pular quebra de linha
		while(!caractereIsValido(c)){
			c = fgetc(arq);

			if(c == EOF && i != imagem->qtdLinhas - 1) return -1;
		}
	}

	return 0;
}

/*
* Obt�m o n�mero de constru��es que uma imagem possu�.
*/
int obterNumeroConstrucoes(IMAGEM_SATELITE *imagem){
	int qtd = 0;

	int i, j;

	for(i = 0; i < imagem->qtdLinhas; i++){
		for(j = 0; j < imagem->qtdColunas; j++){

			//Caso seja a primeira c�lula n�o verificada daquela constru��o incrementa o n�mero de constru��es
			if(primeiraCelulaDaConstrucao(imagem, i, j)){
				qtd ++;
			}

		}
	}

	return qtd;
}

/*
* Trata uma imagem de sat�lite, retornando informa��es como:
* - Imagem que est� sendo examinada
* - N�mero de c�lulas que essa imagem possu�
* - N�mero de constru��es que essa imagem possu�
*/
int tratarImagem(IMAGEM_SATELITE *imagem){
	printf("Examinando imagem %s\n", imagem->nomeArquivo);
	printf("N�mero de c�lulas da imagem: %d\n", imagem->qtdLinhas * imagem->qtdColunas);
	printf("N�mero de constru��es: %d", obterNumeroConstrucoes(imagem));
}

/*
* Verifica se � a primeira c�lula da constru��o, ou seja, se � uma c�lula que ainda
* n�o foi verificada.
*/
int primeiraCelulaDaConstrucao(IMAGEM_SATELITE *imagem, int i, int j){

	if(imagem->matriz[i][j].valor != 1)
		return 0;


	int isPrimeiraCelula = 0;

	//Ele nunca foi verificado ent�o realmente � primeira celula
	if(!imagem->matriz[i][j].jaVerificado){
		isPrimeiraCelula = 1;

		verificaCelula(imagem, i, j);
	}
	
	return isPrimeiraCelula;

}

/*
* Verifica todas as c�lulas de um grupo de estrutura. Ap�s a verifica��o cada c�lula tem seu status
* alterado para verificado.
*/
void verificaCelula(IMAGEM_SATELITE *imagem, int i, int j){

	if(i >= imagem->qtdLinhas || j >= imagem->qtdColunas)
		return;

	//Se o celula possui valor diferente de 1 ou se j� foi verificado n�o faz sentido verifica-lo
	if( imagem->matriz[i][j].valor != 1 || imagem->matriz[i][j].jaVerificado){
		return;
	}

	//Informa que este celula j� foi verificado
	imagem->matriz[i][j].jaVerificado = 1;

	int pdPossuirAdjSupEsq = 1;
	int pdPossuirAdjSupCen = 1;
	int pdPossuirAdjSupDir = 1;

	int pdPossuirAdjEsq = 1;
	int pdPossuirAdjDir = 1;

	int pdPossuirAdjInfEsq = 1;
	int pdPossuirAdjInfCen = 1;
	int pdPossuirAdjInfDir = 1;

	//Um celula que est� na linha 0 n�o possui adjacentes em cima dele
	if(i == 0){
		pdPossuirAdjSupEsq = 0;
		pdPossuirAdjSupCen = 0;
		pdPossuirAdjSupDir = 0;
	}

	//Um celula que est� na coluna 0 n�o possui adjacentes a sua esquerda
	if(j == 0){
		pdPossuirAdjSupEsq = 0;
		pdPossuirAdjInfEsq = 0;
		pdPossuirAdjEsq = 0;
	}

	//Um celula que est� na �ltima linha n�o possui adjacentes a sua direita
	if(i == imagem->qtdLinhas - 1){
		pdPossuirAdjInfEsq = 0;
		pdPossuirAdjInfCen = 0;
		pdPossuirAdjInfDir = 0;
	}

	//Um celula que est� na �ltima coluna n�o possui adjacentesa em baixo dele
	if(j == imagem->qtdColunas - 1){
		pdPossuirAdjSupDir = 0;
		pdPossuirAdjInfDir = 0;
		pdPossuirAdjDir = 0;
	}

	//Verifica as celulas adjacentes superiores
	
	if(pdPossuirAdjSupEsq){
		verificaCelula(imagem, i - 1, j - 1);
	}

	if(pdPossuirAdjSupCen){
		verificaCelula(imagem, i - 1, j);
	}

	if(pdPossuirAdjSupDir){
		verificaCelula(imagem, i - 1, j + 1);
	}

	// Verifica as celulas adjacentes centrais

	if(pdPossuirAdjEsq){
		verificaCelula(imagem, i, j - 1);
	}

	if(pdPossuirAdjDir){
		verificaCelula(imagem, i, j + 1);
	}

	//Verifica as celulas adjacentes inferiores

	if(pdPossuirAdjInfEsq){
		verificaCelula(imagem, i + 1, j - 1);
	}

	if(pdPossuirAdjInfCen){
		verificaCelula(imagem, i + 1, j);
	}

	if(pdPossuirAdjInfDir){
		verificaCelula(imagem, i + 1, j + 1);
	}
}


int limparImagem(IMAGEM_SATELITE *imagem){

	if(imagem->matriz != NULL){
		free(imagem->matriz);
	}

	if(imagem->nomeArquivo != NULL){
		free(imagem->nomeArquivo);
	}

	imagem->qtdColunas = 0;
	imagem->qtdLinhas = 0;
}

