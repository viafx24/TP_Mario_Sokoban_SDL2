#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//char *line = NULL;
//size_t len = 0;
//size_t read;




int main(void)
{

	FILE *stream;
	FILE *stream_2;

	errno_t err;
	errno_t err_2;


	char str[60];

	int Height = 0;
	int Length = 0;
	int ArrayLength[30];

	err = fopen_s(&stream, "soloban01.txt", "r");

	if (err != NULL)
	{
		printf("The file  was not opened\n");
		exit(1);
	}

	else

	{

		printf("The file  was  opened\n");

		while (fgets(str, 60, stream) != NULL)
		{

			/* writing content to stdout */
			//printf(str);
			ArrayLength[Height] = strlen(str);
			printf("Longueur %d \n", ArrayLength[Height]);

			Height++;
		}

		if (stream)
		{
			err = fclose(stream);
			if (err == 0)
			{
				printf("The file  was closed\n");
			}
			else
			{
				printf("The file  was not closed\n");
			}
		}


		Length = largest(ArrayLength, 30);
		
		printf("Longeur Max= %d\n", Length);
		printf("Hauteur Max= %d\n", Height);



		err_2 = fopen_s(&stream_2, "Level.txt", "w");


		while (fgets(str, 60, stream) != NULL)
		{

			for (i = 0; i < Height; i++)
			{
				for (j = 0; j < Length; j++)
				{
					switch (str[(i * Length) + j])
					{
					case ' ':
						niveau[j][i] = 0;
						break;
					case '#':
						niveau[j][i] = 1;
						break;
					case '$':
						niveau[j][i] = 2;
						break;
					case '.':
						niveau[j][i] = 3;
						break;
					case '@':
						niveau[j][i] = 4;
						break;
					case '*':
						niveau[j][i] = 5;
						break;
					case '+':
						niveau[j][i] = 6;
						break;
					
					}
				}
			}

			fclose(fichier);
		}




		if (stream)
		{
			err = fclose(stream);
			if (err == 0)
			{
				printf("The file  was closed\n");
			}
			else
			{
				printf("The file  was not closed\n");
			}
		}

		return 0;
	}
}


int largest(int arr[], int n)
{
	int i;

	// Initialize maximum element 
	int max = arr[0];

	// Traverse array elements from second and 
	// compare every element with current max   
	for (i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];

	return max;
}