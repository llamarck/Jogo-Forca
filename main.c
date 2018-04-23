/*
 * main.c
 *
 *  Created on: 14/04/2018
 *      Author: Léo
 */

#include <stdio.h>
#include <string.h>
//includes

int attempts = 0;
char all_guesses[30];
char secret_word[30];
//declaração de funções globais

void opening(){
		printf("/*****************/\n");
		printf("|~ Jogo da Forca ~|\n");
		printf("/*****************/\n\n");
}

void choose_word(){
	sprintf(secret_word, "developer");
}

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
	int j = 0;
	int found = 0;
	for (; j < attempts; j++){
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
				}else{
					printf("_ ");
				}
			}

	printf("\n");
}

int main(){


	int found = 0;
	int hit = 0;
	//char guess;

	opening();
	choose_word();


	do {
		draw(secret_word, all_guesses, attempts);
		guessing(all_guesses, &attempts);

		/*for(; i < strlen(secret_word); i++){ //diz a posição e se existe a letra!
			if(secret_word[i] == guess){
				printf("A posição %d tem esta letra!\n", i+1);
				fflush(stdout);
			}
		}*/

	} while(!hit && !hang()); //executa isto enquanto não tiver acertado ou sido enforcado

	return 0;
}
