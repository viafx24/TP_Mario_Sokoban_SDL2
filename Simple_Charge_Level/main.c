
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constantes.h"
//#include "jeu.h"


//int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR]);
//int foo();

void myfunc(int ** s, int row, int col);
int chargerNiveau(int ** carte, int row, int col, int NumLevel);

int main(void)
{
	int NumLevel = 1;

	int NumeroLevel[8][3] = { {1,19,14},{2,12,13},{3,18,15},{4,20,18},{5,19,16},{6,21,17},{7,19,15},{8,20,18} };


	int row = NumeroLevel[NumLevel - 1][2], col = NumeroLevel[NumLevel - 1][1];

	int ** carte = (int**)malloc(sizeof(int*)*row);
	for (int i = 0; i < row; i++)
		*(carte + i) = (int*)malloc(sizeof(int)*col);
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			carte[i][j] = 0;

	chargerNiveau(carte, row, col, NumLevel);
	myfunc(carte, row, col);
	for (int i = 0; i < row; i++) {
		free(carte[i]);
	}
	free(carte);
	return 0;
}

void myfunc(int ** carte, int row, int col)
{
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++)
			printf("%d ", carte[i][j]);
		printf("\n");
	}
}

int chargerNiveau(int ** carte, int row, int col, int NumLevel)
{


	FILE* fichier = NULL;
	char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = { 0 };
	int i = 0, j = 0;

	fichier = fopen("Level.txt", "r");
	if (fichier == NULL)
		return 0;

	while (i < NumLevel)
	{

		fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);
		i++;
	}

	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			switch (ligneFichier[(i * row) + j])
			{
			case '0':
				carte[i][j] = 0;
				break;
			case '1':
				carte[i][j] = 1;
				break;
			case '2':
				carte[i][j] = 2;
				break;
			case '3':
				carte[i][j] = 3;
				break;
			case '4':
				carte[i][j] = 4;
				break;
			}
		}
	}

	fclose(fichier);
	return 1;
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
//
//
//
//
//
//
//
//
//
//int main(int argc, char *argv[])
//{
//
//	//int NumeroLevel[8][3] = { {1,19,14},{2,12,13},{3,18,15},{4,20,18},{5,19,16},{6,21,17},{7,19,15},{8,20,18} };
//	int **NumeroLevel;
//	foo();
//
//	for (int i = 0; i < 8; ++i)
//	{
//	
//		printf("%d, %d, %d\n", NumeroLevel[i][0], NumeroLevel[i][1], NumeroLevel[i][2]);
//	
//	}
//
//	//int carte[19][14] = { 0 };
//
//
//
//
//	return 0;
//}
//
//
//int foo()
//{
//	int NumeroLevel[8][3] = { {1,19,14},{2,12,13},{3,18,15},{4,20,18},{5,19,16},{6,21,17},{7,19,15},{8,20,18} };
//}
//
//
//
//int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR])
//{
//	FILE* fichier = NULL;
//	char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = { 0 };
//	int i = 0, j = 0;
//
//	fichier = fopen("niveaux.lvl", "r");
//	if (fichier == NULL)
//		return 0;
//
//	fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier);
//
//	for (i = 0; i < NB_BLOCS_LARGEUR; i++)
//	{
//		for (j = 0; j < NB_BLOCS_HAUTEUR; j++)
//		{
//			switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j])
//			{
//			case '0':
//				niveau[j][i] = 0;
//				break;
//			case '1':
//				niveau[j][i] = 1;
//				break;
//			case '2':
//				niveau[j][i] = 2;
//				break;
//			case '3':
//				niveau[j][i] = 3;
//				break;
//			case '4':
//				niveau[j][i] = 4;
//				break;
//			}
//		}
//	}
//
//	fclose(fichier);
//	return 1;
//}