#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

	err_2 = fopen_s(&stream_2, "Level.txt", "w");

	if (err != NULL || err_2 != NULL)
	{
		printf("Problem with Files\n");
		exit(1);
	}

	else

	{

		printf("The files  were  opened\n");

		while (fgets(str, 60, stream) != NULL)
		{

			for (int i = 0; i < length(str); i++)
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

		if (stream && stream_2)
		{
			err = fclose(stream);
			err_2 = fclose(stream_2);
			if (err == 0 && err_2 == 0)
			{
				printf("The files  were closed\n");
			}
			else
			{
				printf("The files  were not closed\n");
			}
		}


		Length = largest(ArrayLength, 30);
		
		printf("Longeur Max= %d\n", Length);
		printf("Hauteur Max= %d\n", Height);

=




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