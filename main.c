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
char secret_word[30];
//declaração de funções globais

int hang(){
	int errors = 0;
	int i;
	int j;
	for (i = 0; i < attempts; i++){
		int exists = 0;
		for (j = 0; j < strlen(secret_word); j++){
			if(all_guesses[i] == secret_word[j]){
				exists = 1;
				break;
			}
		}
		if(!exists){
			errors++;
		}
	}
	return errors >= 5;

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
	//guesses[30];
	printf("Chute uma letra: ");
	fflush(stdout);
	scanf(" %c", &guess);
	fflush(stdout);
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
}

void chooseWord(){
	int number_words;
	FILE* f; //declara o ponteiro
	f = fopen("words.txt", "r"); //passa o arquivo e o modo (reading, no caso)
	//sprintf(secret_word, "developer");
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
	/*char word[50];
	fscanf(f, "%s", word);*/
}

void addWord(){
	char want;
	printf("Você deseja adicionar alguma palavra no jogo(S/N)?");
	fflush(stdout);
	scanf("%c", &want);
	fflush(stdout);

	if(want == 'S'){
		char new_word[20];
		printf("Digite a nova palavra: ");
		fflush(stdout);
		scanf("%c", new_word);
		fflush(stdout);

		FILE* f;

		f = fopen("words.txt", "r+"); //a stands for append
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
	}
}

int main(){

	opening();
	chooseWord();


	do {
		draw();
		guessing();

		/*for(; i < strlen(secret_word); i++){ //diz a posição e se existe a letra!
			if(secret_word[i] == guess){
				printf("A posição %d tem esta letra!\n", i+1);
				fflush(stdout);
			}
		}*/

	} while(!win() && !hang()); //executa isto enquanto não tiver acertado ou sido enforcado

	return 0;
}
