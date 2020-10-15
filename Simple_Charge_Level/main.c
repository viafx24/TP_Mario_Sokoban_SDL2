
/*pour ce projet de mario sokoban, j'ai utilis� le code de mathieu sur openclassroom que j'ai modifi� pour la sdl2.
j'ai install� la sdl2 � la racine, j'ai ajout� les lib, les.h dans les lib et include du dossier sdl2
il faut aussi r�cup�r�r les dll propre � chaque extension et � la sdl2 et les copier dans le dossier debug ou release
o� fini par apparaitre le.exe qui doit aussi contenir image, fichier audio(png, jpg) (.wav, mp3) ainsi que le fichier des niveaux
sokoban.txt(qui contient 8 niveaux)
le jeu ouvre une fen�tre o� l'uilisateur tape de 1 � 8 pour avoir le niveau correspondant. un jazz est jou� en fond gr�ce � sdl_mixer
quand l'uilisateur reussi un niveau, un bravo avec un son d'applaudissement a lieu.il est possible d'ajouter des nivaux en collant le schema � la suite
des 8 premiers et en modifiant le tableau multidimensionnel arraylevelsokoban[8][4](chang� le 8).alternativement, je pourrais utiliser une constante definir
constante.h mais pour une raison que j'ignore ca n'a pas march�; il est possible que j'ai oubli� par ci par l� d'effacer, de lib�rer de la m�moire. j'imagine
cela est fait automatiquement � la fermeture du jeu? parmi les am�liorations possibles, je voudrais le personnaliser pour les enfants mais dans ce cas, je ne
peux plus utiliser github.'*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h> //gestion des images compress�s
#include <SDL_ttf.h> //gestion police
#include <SDL_mixer.h> // gestion audio
#include "Level.h"
#include "constantes.h"
#include "jeu.h"
#include "main.h"



int main(int argc, char *argv[])
{
	int ArrayLevelSokoban[8][4] = { 0 }; // changer le 8 si ajout de niveau

	GetMainInfoSokobanFile(ArrayLevelSokoban);

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}

	SDL_Window* win = SDL_CreateWindow("Mario Sokoban", 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		TAILLE_BLOC * 21, TAILLE_BLOC * 21, 0); //creates a SDL2 window 


	// La gestion et le fonctionnement de la SDL2 n'est pas simple a appr�hender. Il faut faire des surfaces,
	//les transformer en texture (mieux g�r�r par le GPU), definir la position an g�n�ral avec SDL_rect qui poss�de 
	//l'emplacement en x et y, et hauteur et largeur

	Uint32 render_flags = SDL_RENDERER_ACCELERATED;
	SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, render_flags); // cr�e un render de fond sur lequel on mettra les textures

	SDL_Surface *text_surface, *screen; // les surface dans la sdl2 doit �tre converti en texture.

	screen = SDL_CreateRGBSurface(0, TAILLE_BLOC * 21, TAILLE_BLOC * 21, 32, 0, 0, 0, 0);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255)); // fond blanc
	SDL_Texture *texture_screen = SDL_CreateTextureFromSurface(renderer, screen); // converti en texture.
	SDL_FreeSurface(screen);//lib�re la m�moire
	SDL_Rect dsscreen = { 0,0,714,714 }; // position x, y, largeur et hauteur
	
	SDL_QueryTexture(texture_screen, NULL, NULL, &dsscreen.w, &dsscreen.h);
	SDL_RenderCopy(renderer, texture_screen, NULL, &dsscreen); // on vient mettre la texture dans le render

	TTF_Init();
	TTF_Font *police = NULL;
	police = TTF_OpenFont("angelina.ttf", 46);
	if (!police) {
		printf("error");
	}


	SDL_Rect dstrect = { 135,50,0,0 }; // position x et y dans la fen�tre; 

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


	SDL_RenderPresent(renderer); // on met � jour et "imprime" la fen�tre.


// Gestion of the music
	Mix_Music *music = NULL;
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 1, 4096) == -1) // 44100hz cr�� avec audacity sur un mp3
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
		case SDL_QUIT: // si l'utilisateur clique sur la croix de la fenetre. SDL_QUIT si il y a plusieurs fenetre, voir plus loin.
			continuer = 0;
			break;
		case SDL_KEYDOWN:// regarde � l'appui sur une touche.
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

	// principaux appels de liberation de la m�moire. J'en ai peut-�tre oublier.

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

// fonction qui imprime un texte dans le render. le texte � imprimer est envoy� en argument
// de m�me que la position (dsrect), la police et le render d'accueil.

void DrawText(SDL_Renderer *renderer, TTF_Font* police, const char* text, SDL_Rect dstrect)
{
	SDL_Color black = { 0,0,0 }; // noir
	SDL_Surface *text_surface;

	text_surface = TTF_RenderText_Blended(police, text, black);
	SDL_Texture *texture_text = SDL_CreateTextureFromSurface(renderer, text_surface);
	SDL_FreeSurface(text_surface);
	SDL_QueryTexture(texture_text, NULL, NULL, &dstrect.w, &dstrect.h);
	SDL_RenderCopy(renderer, texture_text, NULL, &dstrect);
	SDL_DestroyTexture(texture_text);
}
