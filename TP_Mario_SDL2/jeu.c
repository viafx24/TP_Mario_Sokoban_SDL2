#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "fichiers.h"
#include "jeu.h"

void jouer(SDL_Window* win, SDL_Renderer* rend)
{
	SDL_Surface *mario[4] = { NULL }; // 4 surfaces pour chacune des directions de mario
	SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;

	SDL_Rect position, positionJoueur;
	SDL_Event event;

	int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
	int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = { 0 };

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

// Chargement du niveau
	if (!chargerNiveau(carte))
		exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau

	// Recherche de la position de Mario au départ
	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
	{
		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
		{
			if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
			{
				positionJoueur.x = i;
				positionJoueur.y = j;
				carte[i][j] = VIDE;
			}
		}
	}
	// Activation de la répétition des touches
 //   SDL_EnableKeyRepeat(100, 100);

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
			case SDL_SCANCODE_ESCAPE:
				continuer = 0;
				break;
			case SDL_SCANCODE_UP:
				marioActuel = marioTexHAUT;
				//				continuer = 0;
								//           deplacerJoueur(carte, &positionJoueur, HAUT);
				break;
			case SDL_SCANCODE_DOWN:
				marioActuel = marioTexBAS;
				//           deplacerJoueur(carte, &positionJoueur, BAS);
				break;
			case SDL_SCANCODE_RIGHT:
				marioActuel = marioTexDROITE;
				//           deplacerJoueur(carte, &positionJoueur, DROITE);
				break;
			case SDL_SCANCODE_LEFT:
				marioActuel = marioTexGAUCHE;
				//           deplacerJoueur(carte, &positionJoueur, GAUCHE);
				break;
			}
			break;
		}

		// Effacement de l'écran

		position.w = 1 * TAILLE_BLOC;
		position.h = 1 * TAILLE_BLOC;

		//position.x = 1;
		//position.y = 1;

		//SDL_QueryTexture(murTex, NULL, NULL, &position.w, &position.h);


		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
		SDL_RenderClear(rend);
		//SDL_RenderCopy(rend, murTex, NULL, &position);

		//
		//SDL_RenderPresent(rend);

	


		/*	SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

		}*/	        // Placement des objets à l'écran
		objectifsRestants = 0;

		for (i = 0; i < NB_BLOCS_LARGEUR; i++)
		{
			for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
			{
				position.x = i * TAILLE_BLOC;
				position.y = j * TAILLE_BLOC;

				switch (carte[i][j])
				{
				case MUR:
					SDL_QueryTexture(murTex, NULL, NULL, &position.w, &position.h);
					SDL_RenderCopy(rend, murTex, NULL, &position);
					//SDL_BlitSurface(mur, NULL, ecran, &position);
					break;
				case CAISSE:
					SDL_QueryTexture(caisseTex, NULL, NULL, &position.w, &position.h);
					SDL_RenderCopy(rend, caisseTex, NULL, &position);
					//SDL_BlitSurface(caisse, NULL, ecran, &position);
					break;
				case CAISSE_OK:
					SDL_QueryTexture(caisseOKTex, NULL, NULL, &position.w, &position.h);
					SDL_RenderCopy(rend, caisseOKTex, NULL, &position);
					//SDL_BlitSurface(caisseOK, NULL, ecran, &position);
					break;
				case OBJECTIF:
					SDL_QueryTexture(objectifTex, NULL, NULL, &position.w, &position.h);
					SDL_RenderCopy(rend, objectifTex, NULL, &position);
					//SDL_BlitSurface(objectif, NULL, ecran, &position);
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
		//SDL_BlitSurface(marioActuel, NULL, ecran, &position);


//		SDL_RenderClear(rend);
		SDL_RenderPresent(rend);
		//   SDL_Flip(ecran);
	}

}
	
//	    // Désactivation de la répétition des touches (remise à 0)
//	    //SDL_EnableKeyRepeat(0, 0);
//	
//	    // Libération des surfaces chargées
//	    SDL_FreeSurface(mur);
//	    SDL_FreeSurface(caisse);
//	    SDL_FreeSurface(caisseOK);
//	    SDL_FreeSurface(objectif);
//	    for (i = 0 ; i < 4 ; i++)
//	        SDL_FreeSurface(mario[i]);
//	}
//	printf("test");
////	SDL_EnableKeyRepeat(100, 100);
//}
    // Activation de la répétition des touches
 






















	//position.w = 1 * TAILLE_BLOC;
	//position.h = 1 * TAILLE_BLOC;

	//position.x = 1;
	//position.y = 1;

	//SDL_QueryTexture(murTex, NULL, NULL, &position.w, &position.h);

 //   SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

	//SDL_RenderClear(rend);
	//SDL_RenderCopy(rend, murTex, NULL, &position);
	//
	//SDL_RenderPresent(rend);



	//SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
	//SDL_Rect rectangle;

	//rectangle.x = 0;
	//rectangle.y = 0;
	//rectangle.w = 50;
	//rectangle.h = 50;
	//SDL_RenderFillRect(rend, &rectangle);

	//SDL_RenderPresent(rend);



	//SDL_RenderClear(rend);
	//SDL_SetRenderDrawColor(rend, 127, 127, 127, 255);


	//SDL_RenderPresent(rend);


//	SDL_Delay(2000); //Pause execution for 3000 milliseconds, for example
//
//	// destroy texture 
//	//SDL_DestroyTexture(murTex);
//	//SDL_DestroyTexture(caisseTex);
//
//	//// destroy renderer 
//	//SDL_DestroyRenderer(rend);
//
//	//// destroy window 
//	//SDL_DestroyWindow(win);
//
//
//	return 0;
//
//}


//	SDL_QueryTexture(murTex, NULL, NULL, &position.w, &position.h);
//
//	position.w = 1 * TAILLE_BLOC;
//	position.h = 1 * TAILLE_BLOC;
//
//	SDL_QueryTexture(caisseTex, NULL, NULL, &position.w, &position.h);
//
//	positionJoueur.w = 2 * TAILLE_BLOC;
//	positionJoueur.h = 1 * TAILLE_BLOC;
//
//
//	SDL_RenderCopy(rend, murTex, NULL, &position);
//	SDL_RenderCopy(rend, caisseTex, NULL, &positionJoueur);
//	// triggers the double buffers 
//	// for multiple rendering 
//	SDL_RenderPresent(rend);
//
//
//	SDL_Delay(10000);  // Pause execution for 3000 milliseconds, for example
//
//	// destroy texture 
//	SDL_DestroyTexture(murTex);
//	SDL_DestroyTexture(caisseTex);
//
//	// destroy renderer 
//	SDL_DestroyRenderer(rend);
//
//	// destroy window 
//	SDL_DestroyWindow(win);
//
//
//	return 0;
//
//}

//
//
//    marioActuel = mario[BAS]; // Mario sera dirigé vers le bas au départ
//
//    // Chargement du niveau
//    if (!chargerNiveau(carte))
//        exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau
//
//    // Recherche de la position de Mario au départ
//    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
//    {
//        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
//        {
//            if (carte[i][j] == MARIO) // Si Mario se trouve à cette position sur la carte
//            {
//                positionJoueur.x = i;
//                positionJoueur.y = j;
//                carte[i][j] = VIDE;
//            }
//        }
//    }
//
//    // Activation de la répétition des touches
//    SDL_EnableKeyRepeat(100, 100);
//
//    while (continuer)
//    {
//        SDL_WaitEvent(&event);
//switch(event.type)
//{
//    case SDL_QUIT:
//        continuer = 0;
//        break;
//    case SDL_KEYDOWN:
//        switch(event.key.keysym.sym)
//        {
//            case SDLK_ESCAPE:
//                continuer = 0;
//                break;
//            case SDLK_UP:
//                marioActuel = mario[HAUT];
//                deplacerJoueur(carte, &positionJoueur, HAUT);
//                break;
//            case SDLK_DOWN:
//                marioActuel = mario[BAS];
//                deplacerJoueur(carte, &positionJoueur, BAS);
//                break;
//            case SDLK_RIGHT:
//                marioActuel = mario[DROITE];
//                deplacerJoueur(carte, &positionJoueur, DROITE);
//                break;
//            case SDLK_LEFT:
//                marioActuel = mario[GAUCHE];
//                deplacerJoueur(carte, &positionJoueur, GAUCHE);
//                break;
//        }
//        break;
//}
//
//        // Effacement de l'écran
//        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
//
//        // Placement des objets à l'écran
//        objectifsRestants = 0;
//
//        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
//        {
//            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
//            {
//                position.x = i * TAILLE_BLOC;
//                position.y = j * TAILLE_BLOC;
//
//                switch(carte[i][j])
//                {
//                    case MUR:
//                        SDL_BlitSurface(mur, NULL, ecran, &position);
//                        break;
//                    case CAISSE:
//                        SDL_BlitSurface(caisse, NULL, ecran, &position);
//                        break;
//                    case CAISSE_OK:
//                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
//                        break;
//                    case OBJECTIF:
//                        SDL_BlitSurface(objectif, NULL, ecran, &position);
//                        objectifsRestants = 1;
//                        break;
//                }
//            }
//        }
//
//        // Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
//        if (!objectifsRestants)
//            continuer = 0;
//
//        // On place le joueur à la bonne position
//        position.x = positionJoueur.x * TAILLE_BLOC;
//        position.y = positionJoueur.y * TAILLE_BLOC;
//        SDL_BlitSurface(marioActuel, NULL, ecran, &position);
//
//
//
//        SDL_Flip(ecran);
//    }
//
//    // Désactivation de la répétition des touches (remise à 0)
//    SDL_EnableKeyRepeat(0, 0);
//
//    // Libération des surfaces chargées
//    SDL_FreeSurface(mur);
//    SDL_FreeSurface(caisse);
//    SDL_FreeSurface(caisseOK);
//    SDL_FreeSurface(objectif);
//    for (i = 0 ; i < 4 ; i++)
//        SDL_FreeSurface(mario[i]);
//}
//
//void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction)
//{
//    switch(direction)
//    {
//        case HAUT:
//            if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
//                break;
//            if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arrête
//                break;
//            // Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
//            if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
//                (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
//                carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
//                break;
//
//            // Si on arrive là, c'est qu'on peut déplacer le joueur !
//            // On vérifie d'abord s'il y a une caisse à déplacer
//            deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);
//
//            pos->y--; // On peut enfin faire monter le joueur (oufff !)
//            break;
//
//
//        case BAS:
//            if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
//                break;
//            if (carte[pos->x][pos->y + 1] == MUR)
//                break;
//
//            if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
//                (pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR ||
//                carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
//                break;
//
//
//            deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);
//
//            pos->y++;
//            break;
//
//
//        case GAUCHE:
//            if (pos->x - 1 < 0)
//                break;
//            if (carte[pos->x - 1][pos->y] == MUR)
//                break;
//
//            if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
//                (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
//                carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
//                break;
//
//
//            deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);
//
//            pos->x--;
//            break;
//
//
//        case DROITE:
//            if (pos->x + 1 >= NB_BLOCS_LARGEUR)
//                break;
//            if (carte[pos->x + 1][pos->y] == MUR)
//                break;
//
//            if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
//                (pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR ||
//                carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
//                break;
//
//            deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);
//
//            pos->x++;
//            break;
//    }
//}
//
//void deplacerCaisse(int *premiereCase, int *secondeCase)
//{
//    if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
//    {
//        if (*secondeCase == OBJECTIF)
//            *secondeCase = CAISSE_OK;
//        else
//            *secondeCase = CAISSE;
//
//        if (*premiereCase == CAISSE_OK)
//            *premiereCase = OBJECTIF;
//        else
//            *premiereCase = VIDE;
//    }
//}
//
