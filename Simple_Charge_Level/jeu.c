
/* fonctions principales qui gère le fonctionnement du jeu*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Level.h"
#include "constantes.h"
#include "main.h"
//#include "jeu.h"


//void jouer(int ArrayLevelSokoban[8][4], int Level);
void deplacerJoueur(int** carte, SDL_Rect* pos, int direction, int col, int row);
void deplacerCaisse(int* premiereCase, int* secondeCase);
void DisplayWindowsWin(SDL_Window* win_2, SDL_Renderer* rend, int Level, int row, int col);


// fonction principale

void jouer(int ArrayLevelSokoban[8][4], int Level) //  le 8 et 4 reste imparfait mais en l'état ca reste comme cela.
{

	int row = ArrayLevelSokoban[Level - 1][2]; // en fonction du niveau choisi par l'utilisateur de 1 à 8  dans Level, determine le nombre de ligne
	int col = ArrayLevelSokoban[Level - 1][1];// idem pour les colonnes
	int Curseur = ArrayLevelSokoban[Level - 1][3]; // trouve ou placer le curseur pour lire le bon sokoban choisi dans sokoban.txt


	// allocation dynamique complexe d'un tableau à deux dimension (j'ai piqué le code sur internet, 
	//je n'ai pas étudié en détail la mémoire etle fonctionnement

	int **carte = (int **)malloc(sizeof(int *) * row);
	for (int i = 0; i < row; i++)
		*(carte + i) = (int *)malloc(sizeof(int) * col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			carte[i][j] = 0;

	GetMapInfo(carte, col, Curseur);

	SDL_Window* win_2 = SDL_CreateWindow("Mario Sokoban", // creates a window 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		TAILLE_BLOC * row, TAILLE_BLOC * col, 0); // création de la deuxième fenètre: celle du jeu.

	// triggers the program that controls 
	// your graphics hardware and sets flags 
	Uint32 render_flags = SDL_RENDERER_ACCELERATED;

	// creates a renderer to render our images 
	SDL_Renderer* rend = SDL_CreateRenderer(win_2, -1, render_flags);


	// quelques initialisations reprise à partir du code de Mathieu.

	SDL_Surface *mario[4] = { NULL }; // 4 surfaces pour chacune des directions de mario
	SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;

	SDL_Rect position, positionJoueur;
	SDL_Event event_2;

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

	// transformation des surfaces en texture.
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

	// boucle principale du jeu.

	while (continuer)
	{
		SDL_WaitEvent(&event_2); // attente des evenements. Pollevent est une alternative quand on ne veut pas attendre.

		switch (event_2.type)
		{
		case SDL_WINDOWEVENT: // for unknwon reason the classic SQL_QUIT doesn't work; code 512
			switch (event_2.window.event) // code 14
			{
			case SDL_WINDOWEVENT_CLOSE: // fermeture de la fenètre si l'utilisateur clique sur la croix.
				continuer = 0;
				break;
			}
		case SDL_KEYDOWN: // deplacement de mario avec les fleches du clavier.
			switch (event_2.key.keysym.scancode)
			{
			case SDL_SCANCODE_ESCAPE:
				continuer = 0;
				break;
			case SDL_SCANCODE_UP:
				marioActuel = marioTexHAUT;
				deplacerJoueur(carte, &positionJoueur, HAUT, col, row);
				break;
			case SDL_SCANCODE_DOWN:
				marioActuel = marioTexBAS;
				deplacerJoueur(carte, &positionJoueur, BAS, col, row);
				break;
			case SDL_SCANCODE_RIGHT:
				marioActuel = marioTexDROITE;
				deplacerJoueur(carte, &positionJoueur, DROITE, col, row);
				break;
			case SDL_SCANCODE_LEFT:
				marioActuel = marioTexGAUCHE;
				deplacerJoueur(carte, &positionJoueur, GAUCHE, col, row);
				break;
			}
			break;
		}
		// Effacement de l'écran
		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderClear(rend);

		// Placement des objets à l'écran grâce au tableau carte récupéré dans lequel i et j lise toutes les cases.
		objectifsRestants = 0;

		for (i = 0; i < row; i++)
		{
			for (j = 0; j < col; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;

				switch (carte[i][j])
				{
				case MUR: // mur, caisse, caisseok et obejctif correspondent à un enum defini dans constante.h (equivalent de 1, 2, 3, 4
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
		{
			DisplayWindowsWin(win_2, rend, Level, row, col); 
			continuer = 0;
		}
		// On place le joueur à la bonne position
		position.x = positionJoueur.x * TAILLE_BLOC;
		position.y = positionJoueur.y * TAILLE_BLOC;

		// on actualise la position de mario et montre la fenètre tel quel doit apparaître avec SDL_renderpresent
		SDL_QueryTexture(marioActuel, NULL, NULL, &position.w, &position.h);
		SDL_RenderCopy(rend, marioActuel, NULL, &position);
		SDL_RenderPresent(rend);

	}

	// liberation de mémoire
	// destroy renderer 
	SDL_DestroyRenderer(rend);

	// destroy window 
	SDL_DestroyWindow(win_2);

	return 0;
//

}

// le double pointeur sur carte est la solution trouvé pour avoir un tableau bidimensionnel dynamique
// la fonction sert à gérer le deplacement de mario et à voir si le deplacement est autorisé ( pas dans un mur!).

void deplacerJoueur(int **carte, SDL_Rect *pos, int direction, int col, int row)
{
	switch (direction)
	{
	case HAUT:
		if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
			break;
		if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arrête
			break;
		// Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
		if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
			(pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
				carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
			break;

		// Si on arrive là, c'est qu'on peut déplacer le joueur !
		// On vérifie d'abord s'il y a une caisse à déplacer
		deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

		pos->y--; // On peut enfin faire monter le joueur (oufff !)
		break;


	case BAS:
		if (pos->y + 1 >= col)
			break;
		if (carte[pos->x][pos->y + 1] == MUR)
			break;

		if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
			(pos->y + 2 >= col || carte[pos->x][pos->y + 2] == MUR ||
				carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
			break;


		deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);

		pos->y++;
		break;


	case GAUCHE:
		if (pos->x - 1 < 0)
			break;
		if (carte[pos->x - 1][pos->y] == MUR)
			break;

		if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
			(pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
				carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
			break;


		deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);

		pos->x--;
		break;


	case DROITE:
		if (pos->x + 1 >= row)
			break;
		if (carte[pos->x + 1][pos->y] == MUR)
			break;

		if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
			(pos->x + 2 >= row || carte[pos->x + 2][pos->y] == MUR ||
				carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
			break;

		deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);

		pos->x++;
		break;
	}
}


// fonction qui gère le deplacement d'une case de départ à la case d'arrivée

void deplacerCaisse(int *premiereCase, int *secondeCase)
{
	if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
	{
		if (*secondeCase == OBJECTIF)
			*secondeCase = CAISSE_OK;
		else
			*secondeCase = CAISSE;

		if (*premiereCase == CAISSE_OK)
			*premiereCase = OBJECTIF;
		else
			*premiereCase = VIDE;
	}
}


// message de félicitation si le joueur reussit le niveau

void DisplayWindowsWin(SDL_Window* win_2, SDL_Renderer* rend, int Level, int row, int col)
{
	// tout n'était peutt-être pas necessaire de recréer mais ca marche.
	// on remplit le fond de blanc et on écrit du texte. pas besoin de réinitialiser TTF_init() je ne sais pas trop pourquoi.

	SDL_Surface *text_surface_2, *screen_2;
	screen_2 = SDL_CreateRGBSurface(0, TAILLE_BLOC * row, TAILLE_BLOC * col, 32, 0, 0, 0, 0);
	SDL_FillRect(screen_2, NULL, SDL_MapRGB(screen_2->format, 255, 255, 255));
	SDL_Texture *texture_screen_2 = SDL_CreateTextureFromSurface(rend, screen_2);
	SDL_FreeSurface(screen_2);
	SDL_Rect dsscreen_2 = { 0,0,0,0 }; // prend toute la fenètre.

	SDL_QueryTexture(texture_screen_2, NULL, NULL, &dsscreen_2.w, &dsscreen_2.h);
	SDL_RenderCopy(rend, texture_screen_2, NULL, &dsscreen_2);

	TTF_Font *police_2 = NULL;
	police_2 = TTF_OpenFont("angelina.ttf", 46);
	if (!police_2) {
		printf("error");
	}

	// choix position pour que le texte rentre dans les 8 fenètres de taille différente.
	SDL_Rect dstrect_2 = { (TAILLE_BLOC * col/2)-175,(TAILLE_BLOC * row)/2-100,0,0 };

	DrawText(rend, police_2, "Bravo tu as réussi !!!", dstrect_2);
	dstrect_2.y = dstrect_2.y + 100;

	char src[50], dest[50];

   // copie le string dans dest
   strcpy(dest, "Passe au niveau ");

   // converti un entier en string et le met dans src
   itoa(Level + 1, src, 10);
   //strcpy(src, itoa(Level + 1));

   //concatene dest et src
	strcat(dest,src);

	//imprime le texte
	DrawText(rend, police_2, dest, dstrect_2);

	// affiche le resultat à l'écran.
	SDL_RenderPresent(rend);

	// emmet un son d'applaudissement en utilisant les fonctions de SDL_mixer
	Mix_Chunk *wave = NULL;
	wave = Mix_LoadWAV(WAV_PATH);
	if (wave == NULL)
		return -1;

	// pour un son, il faut créer un canal (je crois 0+1 soit 1 canal créé; voir doc SDL2_mixer).
	if (Mix_PlayChannel(-1, wave, 0) == -1)
		return -1;

	// affiche la fenètre pendant 4 seconde
	SDL_Delay(4000);


	//libération mémoire.
	Mix_FreeChunk(wave);

	SDL_DestroyTexture(texture_screen_2);
	SDL_DestroyRenderer(rend);
	SDL_DestroyWindow(win_2);

}