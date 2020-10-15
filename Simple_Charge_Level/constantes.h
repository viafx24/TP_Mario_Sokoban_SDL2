/*
constantes.h
------------

Par mateo21, pour Le Site du Z�r0 (www.siteduzero.com)

R�le : d�finit des constantes communes � tout le programme (taille de la fen�tre...)
*/

#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    #define TAILLE_BLOC         34 // Taille d'un bloc (carr�) en pixels
    //#define NB_BLOCS_LARGEUR    22
    //#define NB_BLOCS_HAUTEUR    22
    //#define LARGEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_LARGEUR
    //#define HAUTEUR_FENETRE     TAILLE_BLOC * NB_BLOCS_HAUTEUR

	#define WAV_PATH "applause2.wav"
	#define MUS_PATH "JAZZ_30.mp3"

// je ne me sert pas de ces deux lignes, j'ai eu un bug avec mais ce serait pr�ferable
// car ce serait plus propre. ca eviterait de changer le 8 partout dans le code si on ajoute des niveaux.

	#define NumberRowSokobanLevel 8 

	#define NumberColSokobanLevel 4

    enum {HAUT, BAS, GAUCHE, DROITE};
    enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};

#endif
