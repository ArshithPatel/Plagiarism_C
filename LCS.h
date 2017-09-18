#include<stdio.h>
#include<string.h>
#include <stdlib.h>

//Declaring prototypes for calculating Plagiarism using Longest Common Substring Algorithm.
int max();
float lcs();
void array();

//Function that returns the maximum value of the two integers.
int max(int a, int b)
{   

    if (a>b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

//Calculates the Plagiarism percent of two files. 
//Accepts the character arrays that has all the characters in the file as arguments.
float lcs(char X[100], char Y[100])
{
    int m = strlen(X), n = strlen(Y), i;
    
    float d;
    d = m+n;
    
    int  x=0;
    int L[m][n];
   
   //Calculates the length of longest common substring.
    for (int i=0; i< m; i++)
    {
        for (int j=0; j< n; j++)
        {
            if (i == 0 || j == 0)
            {
                L[i][j] = 0;
            }

            else
            {
                if (X[i] == Y[j])
                {   
                    
                    L[i][j] = L[i-1][j-1] + 1;

                    if  (x < L[i][j])
                    {
                        x = L[i][j];
                    }

                }
                else
                {
                    L[i][j] = 0;   
                }
            }    
        }    
    }

    //Calculates the plagiarism percent from the length of longest common substring calculated above.
    
    float lcs_perc;
    lcs_perc = ((2*x)/(d))*100;
    return lcs_perc;
}

//Starts the Longest Common Substring Algorithm. 
float LongestCommonSubstring(char fp[], char gp[])      //Accepts file pointers as arguments
{
    int m=0, n=0;
    FILE *f, *g;
    char ch;
    char arr1[100], arr2[100];

    //Opens the files that need to be tested.
    f = fopen(fp,"r");
    g = fopen(gp,"r");

    //Converts the data in the file as an array of characters.
    array(f, arr1);
    array(g, arr2);

    //Calls the function to calculate the Plagiarism percent using Longest Common Substring Algorithm.
    float lperc = lcs(arr1, arr2);
         
    return lperc;
}

//Function to create a character array of the data in the file.
void array(FILE *file, char arr[])
{    
    char ch;
    int m = 0;
    ch = fgetc(file);
    arr[m] = '*';
    m++;
    while(ch != EOF)                    //Checks for the end of line.
    {
        if(ch != ' ' && ch != '\n')     //Checks for spaces and new line character
        {
            arr[m] = ch;  
            m++;
        }
        ch = fgetc(file);
        
    }
    arr[m] = '\0';
}