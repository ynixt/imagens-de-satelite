/**
* Auto Instrucional de Estrutura de Dados 2 - 1/2017: Parte 1
* Feito por Gabriel Alves Silva e Gabriel da Silva Cavalcante
*/

#if !defined(IMAGEM_SATELITE_SATELITE_H)
#define IMAGEM_SATELITE_SATELITE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int valor;
	int jaVerificado;
} CELULA;

typedef struct {
	CELULA **matriz;

	int qtdColunas;
	int qtdLinhas;

	char *nomeArquivo;
} IMAGEM_SATELITE;

int caractereIsValido(char);
int popularMatriz(IMAGEM_SATELITE*, FILE*);
int criarMatriz(IMAGEM_SATELITE*, FILE*);
void verificaCelula(IMAGEM_SATELITE*, int, int);
int primeiraCelulaDaConstrucao(IMAGEM_SATELITE*, int, int);
int obterNumeroConstrucoes(IMAGEM_SATELITE*);
int tratarImagem(IMAGEM_SATELITE*);
int limparImagem(IMAGEM_SATELITE*);

#endif