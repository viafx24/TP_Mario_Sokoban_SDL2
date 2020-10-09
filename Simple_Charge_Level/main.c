
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

	int Level = 1;
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


	// retutns zero on success else non-zero 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}

	SDL_Window* win = SDL_CreateWindow("Mario Sokoban", // creates a window 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		TAILLE_BLOC * row, TAILLE_BLOC * col, 0);

	// triggers the program that controls 
	// your graphics hardware and sets flags 
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images 
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);


	SDL_Surface *mario[4] = { NULL }; // 4 surfaces pour chacune des directions de mario
	SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;

	SDL_Rect position, positionJoueur;
	SDL_Event event;

	position.w = 1 * TAILLE_BLOC;
	position.h = 1 * TAILLE_BLOC;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;


	// Chargement des sprites (décors, personnage...)
	mur = IMG_Load("mur.jpg");
	caisse = IMG_Load("caisse.jpg");
	caisseOK = IMG_Load("caisse_ok.jpg");
	objectif = IMG_Load("objectif.png");
	mario[BAS] = IMG_Load("mario_bas.gif");
	mario[GAUCHE] = IMG_Load("mario_gauche.gif");
	mario[HAUT] = IMG_Load("mario_haut.gif");
	mario[DROITE] = IMG_Load("mario_droite.gif");


	SDL_Texture *murTex = SDL_CreateTextureFromSurface(rend, mur);
	SDL_Texture *caisseTex = SDL_CreateTextureFromSurface(rend, caisse);
	SDL_Texture *caisseOKTex = SDL_CreateTextureFromSurface(rend, caisseOK);
	SDL_Texture *objectifTex = SDL_CreateTextureFromSurface(rend, objectif);
	SDL_Texture *marioTexBAS = SDL_CreateTextureFromSurface(rend, mario[BAS]);
	SDL_Texture *marioTexGAUCHE = SDL_CreateTextureFromSurface(rend, mario[GAUCHE]);
	SDL_Texture *marioTexHAUT = SDL_CreateTextureFromSurface(rend, mario[HAUT]);
	SDL_Texture *marioTexDROITE = SDL_CreateTextureFromSurface(rend, mario[DROITE]);

	// clears main-memory 
	SDL_FreeSurface(mur);
	SDL_FreeSurface(caisse);
	SDL_FreeSurface(caisseOK);
	SDL_FreeSurface(objectif);
	SDL_FreeSurface(mario[BAS]);
	SDL_FreeSurface(mario[GAUCHE]);
	SDL_FreeSurface(mario[HAUT]);
	SDL_FreeSurface(mario[DROITE]);


	marioActuel = marioTexBAS; // Mario sera dirigé vers le bas au départ

		// Recherche de la position de Mario au départ
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
				carte[i][j] = VIDE;
			}
		}
	}



	// Effacement de l'écran
	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
	SDL_RenderClear(rend);

	// Placement des objets à l'écran
	objectifsRestants = 0;

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			position.x = i * TAILLE_BLOC;
			position.y = j * TAILLE_BLOC;

			switch (carte[i][j])
			{
			case MUR:
				SDL_QueryTexture(murTex, NULL, NULL, &position.w, &position.h);
				SDL_RenderCopy(rend, murTex, NULL, &position);

				break;
			case CAISSE:
				SDL_QueryTexture(caisseTex, NULL, NULL, &position.w, &position.h);
				SDL_RenderCopy(rend, caisseTex, NULL, &position);

				break;
			case CAISSE_OK:
				SDL_QueryTexture(caisseOKTex, NULL, NULL, &position.w, &position.h);
				SDL_RenderCopy(rend, caisseOKTex, NULL, &position);

				break;
			case OBJECTIF:
				SDL_QueryTexture(objectifTex, NULL, NULL, &position.w, &position.h);
				SDL_RenderCopy(rend, objectifTex, NULL, &position);
				objectifsRestants = 1;
				break;
			}
		}
	}

	// Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
	if (!objectifsRestants)
		continuer = 0;

	// On place le joueur à la bonne position
	position.x = positionJoueur.x * TAILLE_BLOC;
	position.y = positionJoueur.y * TAILLE_BLOC;

	SDL_QueryTexture(marioActuel, NULL, NULL, &position.w, &position.h);
	SDL_RenderCopy(rend, marioActuel, NULL, &position);
	SDL_RenderPresent(rend);

	return 0;
}

	

// cart à rajouter dans les arguments. colonne et fenetre change à chaque event. Compatible SDL?
