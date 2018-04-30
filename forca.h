/*
 * forca.h
 *
 *  Created on: 24/04/2018
 *      Author: Léo
 */

#ifndef FORCA_H_
#define FORCA_H_

#define WORD_SIZE 20

int hang();
void opening();
void guessing();
int alreadyGuessed(char letter);
int win();
void draw();
void chooseWord();
int letterExists(char letter);
int wrongAttempts();
void addWord();
void defineLevel();

#endif /* FORCA_H_ */
