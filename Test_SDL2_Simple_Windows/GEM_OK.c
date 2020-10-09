//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define _CRT_SECURE_NO_WARNINGS
//
//int largest(int arr[], int n);
//
//char str[60];
//
//int main()
//{
//
//	FILE *stream;
//	FILE *stream_2;
//	FILE *stream_3;
//
//
//
//	int Height = 0;
//	int Length = 0;
//	int ArrayLength[30];
//
//	int NumberSokoban = 0;
//
//	stream = fopen("sokoban.txt", "r");
//	stream_2 = fopen("Level.txt", "w");
//	stream_3 = fopen("Taille.txt", "w");
//
//	
//
//
//	//if (stream == NULL || stream_2 == NULL || stream_3 == NULL)
//	//{
//	//	printf("Problem with Files\n");
//	//	exit(1);
//	//}
//
//	//else
//
//	//{
//
//		printf("The files  were  opened\n");
//
//		while (fgets(str, 60, stream) != NULL)
//		{
//
//			if (strlen(str) < 2)
//			{
//				NumberSokoban++;
//				fputc('\n', stream_2);
//
//				Length = largest(ArrayLength, Height);
//
//				//printf("Longeur Max= %d\n", Length);
//				//printf("Hauteur Max= %d\n", Height);
//
//				fprintf(stream_3, "%d", Length);
//				fputc(' ', stream_3);
//				fprintf(stream_3, "%d", Height);
//				//fputc(Height,stream_3);
//				fputc('\n', stream_3);
//
//				printf("Sokoban Numero %d, longueur %d, hauteur,%d\n", NumberSokoban, Length, Height);
//
//				Height = 0;
//				Length = 0;
//			}
//
//			for (int i = 0; i < strlen(str); i++)
//			{
//				switch (str[i])
//				{
//				case ' ':
//					fputc('0', stream_2);
//					break;
//				case '#':
//					fputc('1', stream_2);
//					break;
//				case '$':
//					fputc('2', stream_2);
//					break;
//				case '.':
//					fputc('3', stream_2);
//					break;
//				case '@':
//					fputc('4', stream_2);
//					break;
//				case '*':
//					fputc('5', stream_2);
//					break;
//				case '+':
//					fputc('6', stream_2);
//					break;
//				}
//			}
//
//			ArrayLength[Height] = strlen(str);
//			//	printf("Longueur %d \n", ArrayLength[Height]);
//			Height++;
//		}
//
//		int err_1 = fclose(stream);
//		int err_2 = fclose(stream_2);
//		int err_3 = fclose(stream_3);
//
//		if (err_1 == 0 && err_2 == 0 && err_3 == 0)
//		{
//			printf("Files closed");
//		}
//
//		else
//		{
//			printf("problem closing files");
//		}
//
//		return 0;
//	//}
//}
//
//int largest(int arr[], int n)
//{
//	int i;
//
//	// Initialize maximum element
//	int max = arr[0];
//
//	// Traverse array elements from second and
//	// compare every element with current max
//	for (i = 1; i < n; i++)
//		if (arr[i] > max)
//			max = arr[i];
//
//	return max;
//}
