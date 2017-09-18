#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include<ctype.h>

//Declaring Prototype functions reqiured for implementing 
void get_word();
int get_spaces();
void get_freq();
void bow();
int dot_prod();
float euclidean_norm();

//Initializing a structure for getting dictionary data type.
struct Word_Frequency
{
	char word[20];
	int freq;
};

//Bag Of Words function.
float BOW(char fp[], char gp[])
{
	FILE *f, *g;
	char **arr1, **arr2;
	char w;
	struct Word_Frequency word_f[100], word_g[100];

	//Opening the files that need to be tested.
	f = fopen(fp,"r");
	g = fopen(gp,"r");

	//Counting number of spaces in order to get number of words in file.
	int space_count1 = get_spaces(f);
	int space_count2 = get_spaces(g);
	
	//Initializing an array
	arr1 = (char**) calloc(space_count1+10,sizeof(char*));
	arr2 = (char**) calloc(space_count2+10,sizeof(char*));
	
	//Calling a function for getting all the words in an array.
	get_word(f,arr1);
	get_word(g,arr2);

	//Calculating the percentage of Plagiarism.
	if (arr1[0][0] != '\0' && arr2[0][0] != '\0')
	{
		//Calling the frequency funtion.
		get_freq(arr1, word_f, space_count1);
		get_freq(arr2, word_g, space_count2);
		
		//Calling the Dot-Product function.
		int k = dot_prod(word_f, word_g, space_count1, space_count2);
		
		//Calling the Euclidean Norm function.
		float e1 = euclidean_norm(word_f, space_count1);
		float e2 = euclidean_norm(word_g, space_count2);

		//Calculating the Percentage of plagiarism.
		float e = e1*e2;
		float p = k/e;
		return p*100;
	}
	else
	{
		return 0.00;
	}
	
}

//Function to get the number of words in the file.
int get_spaces(FILE *f)
{
	int c=0;
	char ch;
	ch = fgetc(f);
	while(ch != EOF)
	{
		if(ch == ' ')
		{
			c+=1;
		}
		ch = fgetc(f);
	}
	return c;
}

//Function to create an array with all the words in the file.
void get_word(FILE *f, char **word_arr)
{
	int m=0, n=0;
	char c, word[20];
	fseek(f, 0, SEEK_SET);
	c = fgetc(f);
	while(c != EOF && c != '\n') //Checks for the End of file or new line character.
	{

		n=0;
		while(c != ' ' && c != EOF && c != '\n')
		{
			if (isalnum(c) || c == '_') //Removes special characters except '_'  from the words in the file.
			{
				word[n] = tolower(c); //Converts the complete file into lower case for easy comparision.
				n++;
			}
			c = fgetc(f);

		}
		c = fgetc(f);
		
		word[n] = '\0';
		word_arr[m] = strdup(word);
		m++;		
	}
	word_arr[m] = "\0";
}

//Calculating the frequency of words in the file.
void get_freq(char **arr, struct Word_Frequency word_f[], int space_count)
{
	int c=0, k=0;
	for (int i=0; i<=space_count+1; i++)
	{
		if (strcmp(arr[i],"\0") != 0)
		{	c=1;
			for (int j=0; j<=space_count+1; j++)
			{
				if(strcmp(arr[i],arr[j]) == 0 && i!=j) //Compares the words in the list using double loops.
				{
					c+=1;
					strcpy(arr[j], "\0");
				}				
			}
			strcpy(word_f[k].word,arr[i]);		//Appending the word and frequency to struct.
			word_f[k].freq = c;					//Gives the frequency of a word in the file.
			k++;
		}		
	}
	strcpy(word_f[k].word, "\0");
	word_f[k].freq = 0;
}

//Calculating dot-product for two files.
int dot_prod(struct Word_Frequency word_f[], struct Word_Frequency word_g[], int space_count1, int space_count2)
{
	int d = 0, i = 0, j = 0;
	for (i = 0; i < space_count1; i++)
	{
		for (j = 0; j < space_count2; j++)
		{
			if(strcmp(word_f[i].word,word_g[j].word) == 0)
			{
				d+=(word_f[i].freq*word_g[j].freq);
			}
		}	
	}	
	return d;
}

//Calculates the Euclidean norm of a single file.
float euclidean_norm(struct Word_Frequency word[], int space_count)
{
	int e=0,i=0;
	for (i = 0; i < space_count; i++)
	{
		e+=pow(word[i].freq,2);
	}

	float sq_e = sqrt(e);

	return sq_e;

}
