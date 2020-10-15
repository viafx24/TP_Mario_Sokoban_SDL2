
/* deux fonctions qui gèrent la lecture du fichier sokoban.txt pour y extraire les informations du niveau (position des murs, objectif, caisse, position initial de Mario
Les sokoban viennent d'un site d'un passionné dont le lien est sur le site openclassroom mario Sokoban*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"


// toute la subilité d'un code trouvé sur internet pour gérer un tableau dynamique bidimensionnel; double pointeur sur carte
// cette fonction renvoie le bon sokoban grâce à l'information du curseur

void GetMapInfo(int **carte, int col, int Curseur)
{
	FILE *stream;// créé un flux/ pointeur sur le fichier à ouvrir
	char str[60];
	stream = fopen("Sokoban.txt", "r");

	if (stream == NULL)
	{
		printf("Problem with Files\n");
		exit(1);
	}
	else
	{

	//	printf("The file  was opened\n");
		fseek(stream, Curseur, SEEK_SET); // place le curseur à la bonne position pour écrire la carte.

		int i = 0;
		while (fgets(str, 60, stream) != NULL) // parcours le fichier ligne aprés ligne à partir du curseur placé précedemment.
		{
			if (strlen(str) < 2) // si on tombe sur une ligne vide on arrête (on ne veut qu'une carte de sokoban).
				break;

			else
			{
				for (int j = 0; j < col; j++) // on parcours chaque caractère et chaque ligne (i et j) et on place 1,2,3,4,5,6 qui corresponde
				// à mur, caisse, mario, objectif etc...

					switch (str[j])
					{

					case ' ':
						carte[i][j] = 0; // case vide
						break;
					case '#':
						carte[i][j] = 1;// mur
						break;
					case '$':
						carte[i][j] = 2; // etc..
						break;
					case '.':
						carte[i][j] = 3;
						break;
					case '@':
						carte[i][j] = 4;
						break;
					case '*':
						carte[i][j] = 5;
						break;
					case '+':
						carte[i][j] = 6;
						break;
					}
				i++;
			}
		}
	}

	int err_1 = fclose(stream); // ferme et verifie la bonne fermeture du fichier/flux.

	if (err_1 == 0)
	{
	//	printf("File closed");
	}

	else
	{
		printf("problem closing file");
	}
}

// cette seconde fonction lit l'ensemble du fichier sokoban.txt pour y extraire pour chaque sokoban(8)
// la largeur et hauteur de carte de chaque sokoban, l'emplacement du curseur à placer pour commencer la lecture 
// de la fonction précedente.

void GetMainInfoSokobanFile(int ArrayLevelSokoban[8][4]) // au debu ArrayLevelSokoban est vide; le but est de le remplir
{
	FILE *stream;

	char str[60];
	int Height = 0;
	int Length = 0;
	long BeginArray[9] = { 0 };

	// first loop to get the correct size of each sokoban and write it in a file.
	int NumberSokoban = 0;
	int Compteur = 0;


	// ouverture du fichier en lecture seule (Visual studio bug si on utilise w ou  r+; n'accepte pas le mode d'écriture).
	stream = fopen("Sokoban.txt", "r");

	if (stream == NULL)
	{
		printf("Problem with Files\n");
		exit(1);
	}
	else
	{

	//	printf("The file  was opened\n");

		while (fgets(str, 60, stream) != NULL) // lit les lignes les unes aprés les autres.
		{
			if (strlen(str) < 2) // si ligne vide (espace entre deux cartes de sokoban), écrit les infos extraites pour cette carte-là
			{
				NumberSokoban++;
				BeginArray[NumberSokoban] = ftell(stream);// note l'emplacement du curseur

	//			La ligne ci-dessous devrait être decommenter pour s'aider à comprendre le code si ajout de niveau

	//			printf("Sokoban Numero %d, longueur %d, hauteur %d, seek %ld\n", NumberSokoban, Length, Height, BeginArray[NumberSokoban - 1]);

				ArrayLevelSokoban[Compteur][0] = NumberSokoban; //8
				ArrayLevelSokoban[Compteur][1] = Length;//longueur
				ArrayLevelSokoban[Compteur][2] = Height;// hauteur
				ArrayLevelSokoban[Compteur][3] = BeginArray[NumberSokoban - 1];// curseur
				ArrayLevelSokoban[1][Compteur];

				Height = 0; // on remet hauteur et longeur à zero pour chaque sokoban parcouru (8 fois en tout)
				Length = 0;
				Compteur++;
			}
			else {
//				printf("longueur de ligne identique?%d\n", strlen(str));
				Length = strlen(str) - 1;// longueur - 1 car il faut enlever \n (saut de fin de ligne).
				Height++;
			}
		}

		// fermeture du fichier.
		int err_1 = fclose(stream);

		if (err_1 == 0)
		{
		//	printf("File closed");
		}

		else
		{
			printf("problem closing file");
		}
	}
}