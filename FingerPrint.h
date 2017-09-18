#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

//Declaring prototypes for calculating Plagiarism using Finger Printing Algorithm.
void string_Array();
void hash_Table();
int array_size();
float fingerPercent();

//Initializing the Finger Printing algorithm.
float Finger_Printing(char fp[], char gp[])
{
	FILE *f, *g;
	char arr1[1000], arr2[1000];
	char w;
	long int array1[1000]={0}, array2[1000]={0};
	int n = 0;

	//Opening the files that need to be tested.
	f = fopen(fp,"r");
	g = fopen(gp,"r");

	//Calling the function that gives an array with all the valid characters in the file.
	string_Array(f, arr1);
	string_Array(g, arr2);

	//Calculating the Hash values of the above created array.
	hash_Table(arr1, array1);
	hash_Table(arr2, array2);
	
	//Calling a function that calculates the array size of the character array.
	int p = array_size(arr1);
	int q = array_size(arr2);

	//Calculates the percentage of plagiarism.
	float fperc = 0.0;	
	if (p != 0 && q!=0)
	{
		//Calls the function to calculate the percentage.
		fperc = fingerPercent(array1, array2, p, q);	
	}
	else
	{
		fperc = 0.00;
	}
	return fperc;
}

//Function to create a character array from the characters present in the file.
void string_Array(FILE *f, char arr[])
{
	char ch;
	int n = 0;

	ch = fgetc(f);

	while (ch != EOF)
	{
		if (isalnum(ch) || ch == '_')
		{
			arr[n] = tolower(ch);
			n++;
		}
		ch  = fgetc(f);
		
	}
	arr[n] = '\0';
}

//Function to calculates the weighted Hash values of the character array.
void hash_Table(char arr[], long int array[])
{
	int n = 0;

	while(arr[n+4] != '\0')
	{
		for (int i = n; i < n+5; i++)
		{
			array[n] += (int)arr[i] * (pow(5,i-n)); 
		}
		array[n] = array[n] / 1103;
		n++;
	}
	array[n] = 0;
}

//Function to calculate the size of the character array created above using string_Array function.
int array_size(char array[])
{
	int c = 0, i = 0;
	while (array[i] != '\0')
	{
		c += 1;
		i++;
	}
	return c;

}

//Calculates the percentage of plagiarism of two files.
float fingerPercent(long int array1[], long int array2[], int m, int n)
{
	int  count=0;
	for(int i=0; i<m; i++)
	{
		
		for(int j=0; j<n; j++)
		{
			if(array1[i] == array2[j])
			{
				count += 1;
				
				array2[j] = 0;
				break;
			}
			
		}	
		
	}

	float x = m;
	float y = n;

	float finperc = ((2*count)/(x + y)) * 100;
	return finperc;
}