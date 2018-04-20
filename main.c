/*
 * main.c
 *
 *  Created on: 14/04/2018
 *      Author: Léo
 */

#include <stdio.h>
#include <string.h>

void opening(){
		printf("/*****************/\n");
		printf("|~ Jogo da Forca ~|\n");
		printf("/*****************/\n\n");
}

void choose_word(char * secret_word){
	sprintf(secret_word, "developer");
}

void guessing(char guesses[], int *attempts){
	char guess;
	//guesses[30];
	printf("Chute uma letra: ");
	fflush(stdout);
	scanf(" %c", &guess);
	fflush(stdout);
	guesses[*attempts] = guess;
	(*attempts)++;
}

int alreadyGuessed(char letter, char * guesses, int attempts){
	int j = 0;
	int found = 0;
	for (; j < attempts; j++){
		if(guesses[j] == letter){
			found = 1;
			break;
		}
	}
	return found;
}

void draw(char * secret_word, char * all_guesses, int attempts){
	int i;
	printf("Você já deu %d chutes!\n", attempts);
	fflush(stdout);
	for (i = 0; i < strlen(secret_word); i++){

				if(alreadyGuessed(secret_word[i], all_guesses, attempts)){
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
	int hang = 0;
	int attempts = 0;
	//char guess;
	char all_guesses[30];
	char secret_word[30];

	opening();
	choose_word(secret_word);


	do {
		draw(secret_word, all_guesses, attempts);
		guessing(all_guesses, &attempts);

		/*for(; i < strlen(secret_word); i++){ //diz a posição e se existe a letra!
			if(secret_word[i] == guess){
				printf("A posição %d tem esta letra!\n", i+1);
				fflush(stdout);
			}
		}*/

	} while(!hit && !hang); //executa isto enquanto não tiver acertado ou sido enforcado

	return 0;
}
