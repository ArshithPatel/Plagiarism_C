//Incluc=ding the required header files.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
//Including the user defined header files.
#include "BOW_Test.h"
#include "LCS.h"
#include "FingerPrint.h"

/* The driver class. Program starts execution here.*/
/*Accepts command line input.*/

int main(int argc, char const *argv[])
{
	FILE *f, *g;
	struct dirent *dir;
	char p[100];
	strcpy(p, argv[1]);
	int n=0, i=0;
	chdir(p);
	DIR *d = opendir(p);
	/*Opens the directory and counts the number of files in the directory*/
	while ((dir = readdir(d)) != NULL)
	{
		if (!strcmp(dir->d_name,".") || !strcmp(dir->d_name, ".."))
		{

		}
		else
		{
			n++;
		}
	}
	rewinddir(d);

	char *filesList[n];
	/*Appends files name of those that are of .txt format in a fileList array*/
	while ((dir = readdir(d)) != NULL)
	{
		if (!strcmp(dir->d_name,".") || !strcmp(dir->d_name, ".."))
		{

		}
		else
		{
			if ((dir->d_name[strlen(dir->d_name)-1] == 't') && (dir->d_name[strlen(dir->d_name)-2] == 'x') && (dir->d_name[strlen(dir->d_name)-3] == 't'))
			{
				filesList[i] = (char*) malloc(strlen(dir->d_name)+1);	//Condition to verify whether files are of .txt format.
				strcpy(filesList[i], dir->d_name);
				i++;
			}
		}
	}

	float BOW_Arr[n][n]; 		//Declaration of 2-dimensional array for getting Bag_of_Words
	printf("\t\tBag Of Words\n");

	//Printing the matrix format of Plagiarism results using Bag of Words Algorithm

	printf("\t");
	for (int i=0; i<n; i++)
	{
		printf("  %d\t", i+1);
	}
	printf("\n");
	for (int i=0; i<n; i++)
	{
		printf("\n%d", i+1);
		for (int j=0; j<n; j++)
		{
			if (i==j)
			{
				BOW_Arr[i][j]= 0.00;		//Declaring Plagiarism as 0 for two same files.
				printf("\t0.00");		
			}
			else
			{
				float bow = BOW(filesList[i],filesList[j]);		//Calling BagOfWords functionality for two files in a loop.
				printf("\t%0.2f", bow);
			}

		}
		printf("\n");
	}
	printf("********************************************************\n");
	printf("\t\tLongest Common Substring\n");
	float LCS_Arr[n][n];		//Declaring 2-dimensional array for storing Plagiarism results using Longest Common Substring algorithm

	printf("\t");
	for (int i=0; i<n; i++)
	{
		printf("  %d\t", i+1);
	}
	printf("\n");
	for (int i=0; i<n; i++)
	{
		printf("\n%d", i+1);
		for (int j=0; j<n; j++)
		{
			if (i==j)
			{
				LCS_Arr[i][j]= 0.00;		//Declaring Plagiarism as 0 for two same files.
				printf("\t0.00");
			}
			else
			{
				float b = LongestCommonSubstring(filesList[i],filesList[j]);		//Calling Longest Common Substring for two files in a loop
				printf("\t%0.2f", b);
			}

		}
		printf("\n");
	}
	printf("********************************************************\n");
	printf("\t\tFinger Printing\n");
	float F_Print[n][n];		//Declaring 2-dimensional array for storing Plagiarism results using Finger Printing algorithm

	printf("\t");
	for (int i=0; i<n; i++)
	{
		printf("  %d\t", i+1);
	}
	printf("\n");
	for (int i=0; i<n; i++)
	{
		printf("\n%d", i+1);
		for (int j=0; j<n; j++)
		{
			if (i==j)
			{
				F_Print[i][j]= 0.00;		//Declaring Plagiarism as 0 for two same files.
				printf("\t%0.2f", F_Print[i][j]);
				
			}
			else
			{
				float b = Finger_Printing(filesList[i],filesList[j]);	//Calling Finger Printing for two files in a loop
				printf("\t%0.2f", b);
			}

		}
		printf("\n");
	}


	return 0;
}