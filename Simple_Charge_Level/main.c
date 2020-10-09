
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Level.h"
#include "constantes.h"


int main(int argc, char *argv[])
{
	int ArrayLevelSokoban[8][4] = { 0 };

	GetMainInfoSokobanFile(ArrayLevelSokoban);

	int Level = 8;
	int row = ArrayLevelSokoban[Level - 1][2];
	int col = ArrayLevelSokoban[Level - 1][1];
	int Curseur = ArrayLevelSokoban[Level - 1][3];

	int **carte = (int **)malloc(sizeof(int *) * row);
	for (int i = 0; i < row; i++)
		*(carte + i) = (int *)malloc(sizeof(int) * col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			carte[i][j] = 0;

	GetMapInfo(carte, col, Curseur);

	return 0;
}

// cart à rajouter dans les arguments. colonne et fenetre change à chaque event. Compatible SDL?
