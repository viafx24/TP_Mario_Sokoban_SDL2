
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Level.h"
#include "constantes.h"
#include "jeu.h"
#include "main.h"


//void DrawText(SDL_Renderer *renderer, TTF_Font* police, const char* text, SDL_Rect dstrect);

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

	SDL_Surface *text_surface, *screen;
	screen = SDL_CreateRGBSurface(0, TAILLE_BLOC * 21, TAILLE_BLOC * 21, 32, 0, 0, 0, 0);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
	SDL_Texture *texture_screen = SDL_CreateTextureFromSurface(renderer, screen);
	SDL_FreeSurface(screen);
	SDL_Rect dsscreen = { 0,0,714,714 };
	
	SDL_QueryTexture(texture_screen, NULL, NULL, &dsscreen.w, &dsscreen.h);
	SDL_RenderCopy(renderer, texture_screen, NULL, &dsscreen);

	TTF_Init();
	TTF_Font *police = NULL;
	police = TTF_OpenFont("angelina.ttf", 46);
	if (!police) {
		printf("error");
	}


	SDL_Rect dstrect = { 135,50,0,0 };

	DrawText(renderer, police, "Bienvenue sur Mario Sokoban!", dstrect);
	dstrect.y = dstrect.y + 100;
	DrawText(renderer, police, "Pour le niveau 1, taper 1 !", dstrect);
	dstrect.y = dstrect.y + 50;
	DrawText(renderer, police, "Pour le niveau 2, taper 2 !", dstrect);
	dstrect.y = dstrect.y + 50;
	DrawText(renderer, police, "Pour le niveau 3, taper 3 !", dstrect);
	dstrect.y = dstrect.y + 50;
	DrawText(renderer, police, "Pour le niveau 4, taper 4 !", dstrect);
	dstrect.y = dstrect.y + 50;
	DrawText(renderer, police, "Pour le niveau 5, taper 5 !", dstrect);
	dstrect.y = dstrect.y + 50;
	DrawText(renderer, police, "Pour le niveau 6, taper 6 !", dstrect);
	dstrect.y = dstrect.y + 50;
	DrawText(renderer, police, "Pour le niveau 7, taper 7 !", dstrect);
	dstrect.y = dstrect.y + 50;
	DrawText(renderer, police, "Pour le niveau 8, taper 8 !", dstrect);
	dstrect.y = dstrect.y + 100;
	DrawText(renderer, police, "Pour quitter, taper Echap !", dstrect);


	SDL_RenderPresent(renderer);


// Gestion of the music
	Mix_Music *music = NULL;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 4096) == -1)
		return -1;
	music = Mix_LoadMUS(MUS_PATH);
	if (music == NULL)
		return -1;
	Mix_PlayMusic(music, -1);

// gestion of the events


	int continuer = 1;
	SDL_Event event; // un autre le met juste apr�s le while.

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
			case SDL_SCANCODE_ESCAPE: // Veut arr�ter le jeu
				continuer = 0;
				break;
			case SDL_SCANCODE_KP_1: // Demande � jouer
				jouer(ArrayLevelSokoban,1);
				//continuer = 0;
				break;
			case SDL_SCANCODE_KP_2: // Demande � jouer
				jouer(ArrayLevelSokoban, 2);
				//continuer = 0;
				break;
			case SDL_SCANCODE_KP_3: // Demande � jouer
				jouer(ArrayLevelSokoban, 3);
				//continuer = 0;
				break;
			case SDL_SCANCODE_KP_4: // Demande � jouer
				jouer(ArrayLevelSokoban, 4);
				//continuer = 0;
				break;
			case SDL_SCANCODE_KP_5: // Demande � jouer
				jouer(ArrayLevelSokoban, 5);
				//continuer = 0;
				break;
			case SDL_SCANCODE_KP_6: // Demande � jouer
				jouer(ArrayLevelSokoban, 6);
				//continuer = 0;
				break;
			case SDL_SCANCODE_KP_7: // Demande � jouer
				jouer(ArrayLevelSokoban, 7);
				//continuer = 0;
				break;
			case SDL_SCANCODE_KP_8: // Demande � jouer
				jouer(ArrayLevelSokoban, 8);
				//continuer = 0;
				break;
			}
			break;
		}
	}

	Mix_FreeMusic(music);
	Mix_CloseAudio();

	TTF_CloseFont(police);
	TTF_Quit();

	SDL_DestroyTexture(texture_screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0;


}

void DrawText(SDL_Renderer *renderer, TTF_Font* police, const char* text, SDL_Rect dstrect)
{
	SDL_Color black = { 0,0,0 };
	SDL_Surface *text_surface;

	text_surface = TTF_RenderText_Blended(police, text, black);
	SDL_Texture *texture_text = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_FreeSurface(text_surface);
	SDL_QueryTexture(texture_text, NULL, NULL, &dstrect.w, &dstrect.h);
	SDL_RenderCopy(renderer, texture_text, NULL, &dstrect);
	SDL_DestroyTexture(texture_text);
}


//
////
////
//// Our wave file
//Mix_Chunk *wave = NULL;
//// Our music file
//Mix_Music *music = NULL;
//
//
//int main(int argc, char* argv[]) {
//
//	// Initialize SDL.
//	if (SDL_Init(SDL_INIT_AUDIO) < 0)
//		return -1;
//
//	//Initialize SDL_mixer 
//	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 4096) == -1)
//		return -1;
//
//	//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
//	//{
//	//	printf("%s", Mix_GetError());
//	//}
//
//
//
//	// Load our sound effect
//	wave = Mix_LoadWAV(WAV_PATH);
//	if (wave == NULL)
//		return -1;
//
//	// Load our music
//	music = Mix_LoadMUS(MUS_PATH);
//	if (music == NULL)
//		return -1;
//
//	if (Mix_PlayChannel(-1, wave, 0) == -1)
//		return -1;
//
//	if (Mix_PlayMusic(music, -1) == -1)
//		return -1;
//
//	while (Mix_PlayingMusic());
//
//	// clean up our resources
//	Mix_FreeChunk(wave);
//	Mix_FreeMusic(music);
//
//	// quit SDL_mixer
//	Mix_CloseAudio();
//
//	return 0;
//}