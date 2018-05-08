/*
 * main.c
 *
 *  Created on: 14/04/2018
 *      Author: Léo
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "forca.h"
//includes

int attempts = 0;
char all_guesses[30];
char secret_word[WORD_SIZE];
int level;
//declaração de funções globais

int validateWord(char new_word[]){
	FILE * f;
	f = fopen("words.txt", "r");
	int flag = 1;
	int total;
	fscanf(f, "%d", &total);
	char word[WORD_SIZE];

	int i;
	for(i = 0; i <= total; i++){
		fscanf(f, "%s", word);
		if((strcmp(word, new_word)) == 0){
			flag = 0;
			break;
		}
	}
	return flag;
}

int validateCase(char word[]){
	int i;
	int lower = 1;
	for(i = 0; i < strlen(word); i++){
		if(((int)word[i] < 65) || ((int)word[i] > 90)){
			lower = 0;
			break;
		}
	}
	return lower;
}

void defineLevel(){
	int lvl = 0;

	printf("Selecione o nível de dificuldade\n");
	fflush(stdout);
	printf("FÁCIL (1)   NORMAL (2)   DIFÍCIL(3)\n");
	fflush(stdout);
	scanf("%d", &lvl);
	fflush(stdout);

	if(lvl == 1){
		level = 5;
	}else if(lvl == 2){
		level = 3;
	}else{
		level = 1;
	}
}

int letterExists(char letter){
	int j;
	for (j = 0; j < strlen(secret_word); j++){
		if (letter == secret_word[j]){
			return 1;
		}
	}
	return 0;
}

int wrongAttempts(){
	int errors = 0;
		int i;
		for (i = 0; i < attempts; i++){
			if(!letterExists(all_guesses[i])){
				errors++;
			}
		}
		return errors;
}

int hang(){
	return wrongAttempts() >= level;
}

int win(){
	int i;
	for (i = 0; i < strlen(secret_word); i++){
		if(!alreadyGuessed(secret_word[i])){
			return 0;
		}
	}

	return 1;
}

void opening(){
		printf("/*****************/\n");
		printf("|~ Jogo da Forca ~|\n");
		printf("/*****************/\n\n");
}

void guessing(){
	char guess;
	printf("Chute uma letra: ");
	fflush(stdout);
	scanf(" %c", &guess);
	fflush(stdout);

	if(letterExists(guess)){
		printf("Você acertou! A palavra TEM %c!\n", guess);
		fflush(stdout);
	}else{
		printf("Você errou! A palavra NÃO TEM %c!\n", guess);
		fflush(stdout);

	}

	all_guesses[attempts] = guess;
	attempts++;
}

int alreadyGuessed(char letter){
	int j;
	int found = 0;
	for (j = 0; j < attempts; j++){
		if(all_guesses[j] == letter){
			found = 1;
			break;
		}
	}
	return found;
}

void draw(){
	int mistakes = wrongAttempts();
	int i;
	printf("Você já deu %d chutes!\n", attempts);
	fflush(stdout);
	for (i = 0; i < strlen(secret_word); i++){

				if(alreadyGuessed(secret_word[i])){
					printf("%c ", secret_word[i]);
					fflush(stdout);
				}else{
					printf("_ ");
					fflush(stdout);
				}
			}

	printf("\n");
	fflush(stdout);

	printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (mistakes>=1?'(':' '), (mistakes>=1?'_':' '), (mistakes>=1?')':' '));
	printf(" |      %c%c%c  \n", (mistakes>=3?'\\':' '), (mistakes>=2?'|':' '), (mistakes>=3?'/': ' '));
	printf(" |       %c     \n", (mistakes>=2?'|':' '));
	printf(" |      %c %c   \n", (mistakes>=4?'/':' '), (mistakes>=4?'\\':' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");
}

void chooseWord(){
	int number_words;
	FILE* f;
	f = fopen("words.txt", "r");
	if(f == 0){
		printf("Banco de dados de palavras não disponível.\n\n");
		fflush(stdout);
		exit(1);
	}
	fscanf(f, "%d", &number_words);
	fflush(stdout);

	srand(time(0));
	int random = rand() % number_words;

	int i;
	for(i = 0; i <= random; i++){
		fscanf(f, "%s", secret_word);
		fflush(stdout);
	}
	fclose(f);
}

void addWord(){
	int valid = 0;
	char want;
	printf("Você deseja adicionar alguma palavra no jogo(S/N)?\n");
	fflush(stdout);
	scanf(" %c", &want);
	fflush(stdout);

	if(want == 's'){
		char new_word[WORD_SIZE];

		while(valid == 0){
			printf("\nDigite a nova palavra: ");
			fflush(stdout);
			scanf(" %s", new_word);
			fflush(stdout);

			/*if(!validateWord(new_word)){
				printf("A palavra %s já existe!", new_word);
			}*/

			if((validateCase(new_word)) && (validateWord(new_word))){
				FILE* f;

				f = fopen("words.txt", "r+");
				if(f == 0){
					printf("Banco de palavras não disponível.\n\n");
					exit(1);
				}

				int qtd;
				fscanf(f, "%d", &qtd);
				fflush(stdout);
				qtd++;
				fseek(f, 0, SEEK_SET);
				fprintf(f, "%d", qtd);
				fflush(stdout);

				fseek(f, 0, SEEK_END);
				fprintf(f, "\n%s", new_word);
				fflush(stdout);
				fclose(f);

				valid = 1;
				printf("%s adicionada com sucesso!", new_word);
				break;
			}else{
				printf("Insira apenas palavras com letra MAIÚSCULA e palavras que não existem.\n");
			}
		}
	}
}

int main(){

	opening();
	defineLevel();
	chooseWord();


	do {
		draw();
		guessing();

	} while(!win() && !hang());

	if(win()) {
			printf("\nParabéns, você ganhou!\n\n");

		    printf("       ___________      \n");
		    printf("      '._==_==_=_.'     \n");
		    printf("      .-\\:      /-.    \n");
		    printf("     | (|:.     |) |    \n");
		    printf("      '-|:.     |-'     \n");
		    printf("        \\::.    /      \n");
		    printf("         '::. .'        \n");
		    printf("           ) (          \n");
		    printf("         _.' '._        \n");
		    printf("        '-------'       \n\n");

			addWord();

		 }else{
		    printf("\nVocê foi enforcado!\n");

		    printf("A palavra era **%s**\n\n", secret_word);

		    printf("    _______________         \n");
		    printf("   /               \\       \n");
		    printf("  /                 \\      \n");
		    printf("//                   \\/\\  \n");
		    printf("\\|   XXXX     XXXX   | /   \n");
		    printf(" |   XXXX     XXXX   |/     \n");
		    printf(" |   XXX       XXX   |      \n");
		    printf(" |                   |      \n");
		    printf(" \\__      XXX      __/     \n");
		    printf("   |\\     XXX     /|       \n");
		    printf("   | |           | |        \n");
		    printf("   | I I I I I I I |        \n");
		    printf("   |  I I I I I I  |        \n");
		    printf("   \\_             _/       \n");
		    printf("     \\_         _/         \n");
		    printf("       \\_______/           \n");
		 }

	return 0;
}
