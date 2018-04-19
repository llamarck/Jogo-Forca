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

void guessing(char guesses[], int attempts){
	attempts = 0;
	char guess;
	//guesses[30];
	printf("Chute uma letra: ");
	fflush(stdout);
	scanf(" %c", &guess);
	fflush(stdout);
	guesses[attempts] = guess;
	attempts++;
}

int main(){

	opening();

	int hit = 0;
	int hang = 0;
	int attempts = 0;
	char guess;
	char all_guesses[30];
	char secret_word[30];

	sprintf(secret_word, "developer");
	fflush(stdout);

	int i;
	int j;

	do {
		for (i = 0; i < strlen(secret_word); i++){
			int found = 0;

			for (j = 0; j < attempts; j++){
				if(all_guesses[j] == secret_word[i]){
					found = 1;
					break;
				}
			}

			if(found){
				printf("%c ", secret_word[i]);
			}else{
				printf("_ ");
			}
		}

		printf("\n");
		fflush(stdout);

		guessing(all_guesses, attempts);


		/*for(; i < strlen(secret_word); i++){ //diz a posição e se existe a letra!
			if(secret_word[i] == guess){
				printf("A posição %d tem esta letra!\n", i+1);
				fflush(stdout);
			}
		}*/

	} while(!hit && !hang); //executa isto enquanto não tiver acertado ou sido enforcado

	return 0;
}
