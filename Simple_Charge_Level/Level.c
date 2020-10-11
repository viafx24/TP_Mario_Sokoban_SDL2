#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes.h"

void GetMapInfo(int **carte, int col, int Curseur)
{
	FILE *stream;
	char str[60];
	stream = fopen("Sokoban.txt", "r");

	if (stream == NULL)
	{
		printf("Problem with Files\n");
		exit(1);
	}
	else
	{

		printf("The file  was opened\n");
		fseek(stream, Curseur, SEEK_SET);

		int i = 0;
		while (fgets(str, 60, stream) != NULL)
		{
			if (strlen(str) < 2)
				break;

			else
			{
				for (int j = 0; j < col; j++)

					switch (str[j])
					{

					case ' ':
						carte[i][j] = 0;
						break;
					case '#':
						carte[i][j] = 1;
						break;
					case '$':
						carte[i][j] = 2;
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
}


void GetMainInfoSokobanFile(int ArrayLevelSokoban[8][4])
{
	FILE *stream;

	char str[60];
	int Height = 0;
	int Length = 0;
	long BeginArray[9] = { 0 };

	// first loop to get the correct size of each sokoban and write it in a file.
	int NumberSokoban = 0;
	int Compteur = 0;

	stream = fopen("Sokoban.txt", "r");

	if (stream == NULL)
	{
		printf("Problem with Files\n");
		exit(1);
	}
	else
	{

		printf("The file  was opened\n");

		while (fgets(str, 60, stream) != NULL)
		{
			if (strlen(str) < 2)
			{
				NumberSokoban++;
				BeginArray[NumberSokoban] = ftell(stream);
				printf("Sokoban Numero %d, longueur %d, hauteur %d, seek %ld\n", NumberSokoban, Length, Height, BeginArray[NumberSokoban - 1]);

				ArrayLevelSokoban[Compteur][0] = NumberSokoban;
				ArrayLevelSokoban[Compteur][1] = Length;
				ArrayLevelSokoban[Compteur][2] = Height;
				ArrayLevelSokoban[Compteur][3] = BeginArray[NumberSokoban - 1];
				ArrayLevelSokoban[1][Compteur];

				Height = 0;
				Length = 0;
				Compteur++;
			}
			else {
				printf("longueur de ligne identique?%d\n", strlen(str));
				Length = strlen(str) - 1;
				Height++;
			}
		}

		// fseek(stream, 2005, SEEK_SET);
		// fgets(str, 60, stream);
		// printf(str);

		int err_1 = fclose(stream);

		if (err_1 == 0)
		{
			printf("File closed");
		}

		else
		{
			printf("problem closing file");
		}
	}
}