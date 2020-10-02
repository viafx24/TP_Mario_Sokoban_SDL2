#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "jeu.h"
//#include "editeur.h"


int main(int argc, char *argv[])

{
	// retutns zero on success else non-zero 
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}
	SDL_Window* win = SDL_CreateWindow("Mario Sokoban", // creates a window 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		LARGEUR_FENETRE, HAUTEUR_FENETRE, 0);

	// triggers the program that controls 
	// your graphics hardware and sets flags 
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images 
	SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

	// creates a surface to load an image into the main memory 
	SDL_Surface *menu;

	// please provide a path for your image 
	menu = IMG_Load("menu.jpg");

	// loads image to our graphics hardware memory. 
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, menu);

	// clears main-memory 
	SDL_FreeSurface(menu);

	// let us control our image position 
	// so that we can move it with our keyboard. 
	SDL_Rect dest;

	// connects our texture with dest to control position 
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

	// adjust height and width of our image box. 
	dest.w /= 1;
	dest.h /= 1;

	// sets initial x-position of object 
	dest.x = 0;

	// sets initial y-position of object 
	dest.y = 0;

	// clears the screen 
	SDL_RenderClear(rend);
	SDL_RenderCopy(rend, tex, NULL, &dest);

	// triggers the double buffers 
	// for multiple rendering 
	SDL_RenderPresent(rend);

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
				jouer(win,rend);
				//printf("you pressed %d\n", 1);
				continuer = 0;
				break;
			case SDL_SCANCODE_KP_2: // Demande l'éditeur de niveaux
				//editeur(ecran);
				printf("you pressed %d\n", 2);
				continuer = 0;
				break;
			}
			break;
		}
	}
		// calculates to 60 fps 
	//	SDL_Delay(1000 / 60);

//		SDL_Delay(10000);  // Pause execution for 3000 milliseconds, for example

	// destroy texture 
		SDL_DestroyTexture(tex);

		// destroy renderer 
		SDL_DestroyRenderer(rend);

		// destroy window 
		SDL_DestroyWindow(win);


		return 0;
	
}













//
//
//
//
//
//
//
//
//
//	SDL_Surface *ecran = NULL, *menu = NULL;
//	SDL_Rect positionMenu;
//	SDL_Event event;
//
//	int continuer = 1;
//
//	SDL_Init(SDL_INIT_VIDEO);
//
//	SDL_WM_SetIcon(IMG_Load("caisse.jpg"), NULL); // L'icône doit être chargée avant SDL_SetVideoMode
//	ecran = SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
//	SDL_WM_SetCaption("Mario Sokoban", NULL);
//
//	menu = IMG_Load("menu.jpg");
//	positionMenu.x = 0;
//	positionMenu.y = 0;
//
//	while (continuer)
//	{
//		SDL_WaitEvent(&event);
//		switch (event.type)
//		{
//		case SDL_QUIT:
//			continuer = 0;
//			break;
//		case SDL_KEYDOWN:
//			switch (event.key.keysym.sym)
//			{
//			case SDLK_ESCAPE: // Veut arrêter le jeu
//				continuer = 0;
//				break;
//			case SDLK_KP1: // Demande à jouer
//				jouer(ecran);
//				break;
//			case SDLK_KP2: // Demande l'éditeur de niveaux
//				editeur(ecran);
//				break;
//			}
//			break;
//		}
//
//		// Effacement de l'écran
//		SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
//		SDL_BlitSurface(menu, NULL, ecran, &positionMenu);
//		SDL_Flip(ecran);
//	}
//
//	SDL_FreeSurface(menu);
//	SDL_Quit();
//
//	return EXIT_SUCCESS;
//}
