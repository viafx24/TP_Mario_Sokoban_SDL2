/*
jeu.h
-----

Par mateo21, pour Le Site du Zér0 (www.siteduzero.com)

Rôle : prototypes des fonctions du jeu.
*/

// le but du ifndef est d'empecher l'inclusion plusieurs fois de ce fichier itérativement en cas d'erreur (ca arrive souvent).

#ifndef DEF_JEU
#define DEF_JEU

void jouer(int ArrayLevelSokoban[8][4], int Level);
void deplacerJoueur(int** carte, SDL_Rect* pos, int direction, int col, int row);
void deplacerCaisse(int* premiereCase, int* secondeCase);
void DisplayWindowsWin(SDL_Window* win_2, SDL_Renderer* rend, int Level, int row, int col);

#endif
