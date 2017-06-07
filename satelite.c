/**
* Auto Instrucional de Estrutura de Dados 2 - 1/2017: Parte 1
* Feito por Gabriel Alves Silva e Gabriel da Silva Cavalcante
*/

#include <locale.h>
#include <stdio.h>
#include "imagemSatelite.h"

IMAGEM_SATELITE imagem;

int lerArquivo(char url[]){
	FILE *arq = fopen(url, "r");

	if(arq != NULL) {
		return criarMatriz(&imagem, arq);
	}
	    
	fclose(arq);

	return -1;
}

int main(int argc, char **argv){
	
	setlocale(LC_ALL,"");
	
	if(argc != 2){
		printf("Utilização: satélite <imagem>\n\t<imagem>: nome do arquivo contendo a imagem");
	}else{
		imagem.nomeArquivo = argv[1];

		if(lerArquivo(imagem.nomeArquivo) == 0){
			tratarImagem(&imagem);
		}

		limparImagem(&imagem);
	}

}

