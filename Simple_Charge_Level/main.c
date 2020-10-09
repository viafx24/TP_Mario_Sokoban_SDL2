
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Level.h"
#include "constantes.h"
#include "jeu.h"

int main(int argc, char *argv[])
{
	int ArrayLevelSokoban[8][4] = { 0 };

	GetMainInfoSokobanFile(ArrayLevelSokoban);

	int Level = 1;


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}

	SDL_Window* win = SDL_CreateWindow("Mario Sokoban", // creates a window 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		TAILLE_BLOC * 12, TAILLE_BLOC * 12, 0);


	int continuer = 1;
	SDL_Event event; // un autre le met juste aprés le while.

	while (continuer)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			continuer = 0;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE: // Veut arrêter le jeu
				continuer = 0;
				break;
			case SDL_SCANCODE_KP_1: // Demande à jouer
				jouer(ArrayLevelSokoban,1);
				continuer = 0;
				break;
			case SDL_SCANCODE_KP_2: // Demande à jouer
				jouer(ArrayLevelSokoban, 2);
				continuer = 0;
				break;
			case SDL_SCANCODE_KP_3: // Demande à jouer
				jouer(ArrayLevelSokoban, 3);
				continuer = 0;
				break;
			case SDL_SCANCODE_KP_4: // Demande à jouer
				jouer(ArrayLevelSokoban, 4);
				continuer = 0;
				break;
			case SDL_SCANCODE_KP_5: // Demande à jouer
				jouer(ArrayLevelSokoban, 5);
				continuer = 0;
				break;
			case SDL_SCANCODE_KP_6: // Demande à jouer
				jouer(ArrayLevelSokoban, 6);
				continuer = 0;
				break;
			case SDL_SCANCODE_KP_7: // Demande à jouer
				jouer(ArrayLevelSokoban, 7);
				continuer = 0;
				break;
			case SDL_SCANCODE_KP_8: // Demande à jouer
				jouer(ArrayLevelSokoban, 8);
				continuer = 0;
				break;
			}
			break;
		}
	}

	return 0;

}

	

// cart à rajouter dans les arguments. colonne et fenetre change à chaque event. Compatible SDL?
