/*
 * main.c
 *
 *  Created on: 14/04/2018
 *      Author: Léo
 */

#include <stdio.h>
#include <string.h>

int main(){
	char guess;
	int hit = 0;
	int hang = 0;
	char secret_word[20];

	do {
		char chute;
		printf("Chute uma letra: ");
		fflush(stdout);
		scanf("%c", guess);
		fflush(stdout);

		for(int i = 0; i <= strln(secret_word); i++){
			if(secret_word[i] = guess){

			}
		}

	} while(!hit && !hang);

	return 0;
}
