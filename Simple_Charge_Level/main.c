
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Level.h"
#include "constantes.h"
#include "jeu.h"

int main(int argc, char *argv[])
{
	int ArrayLevelSokoban[8][4] = { 0 };

	GetMainInfoSokobanFile(ArrayLevelSokoban);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}

	SDL_Window* win = SDL_CreateWindow("Mario Sokoban", // creates a window 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		TAILLE_BLOC * 21, TAILLE_BLOC * 21, 0);

	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, render_flags);

	TTF_Init();

	TTF_Font *police = NULL;
	police = TTF_OpenFont("angelina.ttf", 64);
	if (!police) {
		printf("error");
	}

	/*TTF_Font * font = TTF_OpenFont("arial.ttf", 25);*/
	//SDL_Color color = { 255, 255, 255 };
	//SDL_Surface *surface = TTF_RenderText_Solid(police,
	//	"Welcome to Gigi Labs", color);

	

	/*SDL_Color color = { 255, 255, 255 };
	SDL_Surface * surface = TTF_RenderText_Solid(police,
		"Welcome to Gigi Labs", color);*/

	SDL_Color black = { 0,0,0 };
	SDL_Surface *text_surface, *screen;

	screen = SDL_CreateRGBSurface(0, TAILLE_BLOC * 21, TAILLE_BLOC * 21, 32, 0, 0, 0, 0);

	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

	//s = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

	/* Filling the surface with red color. */
	//SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 0, 0));



	const char Test[] = "text";
	text_surface = TTF_RenderText_Blended(police, Test, black);

	SDL_Texture *texture_screen = SDL_CreateTextureFromSurface(renderer, screen);

	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, text_surface);



	//int texW = 100;
	//int texH = 100;
	SDL_Rect dsscreen = { 0,0,714,714 };
	SDL_Rect dstrect = { 200,200,0,0 };
	//dstrect.x = 200;
	//dstrect.y = 200;
	//dstrect.w = 0;
	//dstrect.h = 0;

	SDL_QueryTexture(texture_screen, NULL, NULL, &dsscreen.w, &dsscreen.h);
	SDL_QueryTexture(texture, NULL, NULL, &dstrect.w, &dstrect.h);
	//SDL_Rect dstrect = { 0, 0, texW,texH  };
	
	/*dstrect.x = 20;
	dstrect.y = 20;*/

	SDL_RenderCopy(renderer, texture_screen, NULL, &dsscreen);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_RenderPresent(renderer);

	//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	//DrawText(screen,police, "test");

	

	//position.x = 0;
	//position.y = 0;
	//SDL_BlitSurface(fond, NULL, ecran, &position); /* Blit du fond */

	//position.x = 60;
	//position.y = 370;
	//SDL_BlitSurface(texte, NULL, ecran, &position); /* Blit du texte */
	/*SDL_Flip(screen);*/






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

int DrawText(SDL_Surface* screen, TTF_Font* font, const char* text)
{
	SDL_Color black = { 0,0,0 };
	SDL_Surface *text_surface;

	text_surface = TTF_RenderText_Blended(font, text, black);
	if (text_surface != NULL)
	{
		SDL_BlitSurface(text_surface, NULL, screen, NULL);
		SDL_FreeSurface(text_surface);
		return 0;
	}
	else
	{
		// report error
		return 1;
	}
}

// cart à rajouter dans les arguments. colonne et fenetre change à chaque event. Compatible SDL?
