#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _CRT_SECURE_NO_WARNINGS 

int largest(int arr[], int n);


int main(void)
{

	FILE *stream;
	FILE *stream_2;

	char str[60];

	int Height = 0;
	int Length = 0;
	int ArrayLength[30];

	stream = fopen("soloban01.txt", "r+");
	stream_2 = fopen("Level.txt", "w+");

	if (stream  == NULL)
	{
		printf("Problem with Files\n");
		exit(1);
	}

	if (stream_2 == NULL)
	{
		printf("Problem with Files\n");
		exit(1);
	}
  
	else

	{

		printf("The files  were  opened\n");

		while (fgets(str, 60, stream) != NULL)
		{

			for (int i = 0; i < strlen(str); i++)
			{
				switch (str[i])
				{
				case ' ':
					fputc('0', stream_2);
					break;
				case '#':
					fputc('1', stream_2);
					break;
				case '$':
					fputc('2', stream_2);
					break;
				case '.':
					fputc('3', stream_2);
					break;
				case '@':
					fputc('4', stream_2);
					break;
				case '*':
					fputc('5', stream_2);
					break;
				case '+':
					fputc('6', stream_2);
					break;

				}
			}

			ArrayLength[Height] = strlen(str);
			printf("Longueur %d \n", ArrayLength[Height]);
			Height++;
		}
	
		fclose(stream);
		fclose(stream_2);

		Length = largest(ArrayLength, Height);
		
		printf("Longeur Max= %d\n", Length);
		printf("Hauteur Max= %d\n", Height);

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
