/*
	features:

	creates a folder for each secret santa group
	read in a text file with the rules of secret santa and add it into the each text file
	----> maybe add ascii art in text file
			---> maybe use curl and email it to everyone
	---> add checking file length before reading in the file so that we don't waste memory
	---> make the arrays dynamic
*/
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define	LINESIZE 450
#define FILELENGTH 62
// #define DEBUG

/*
	initializes array to -1
*/
void reset(int *list, int *success, int *i, int people)
{
	for (int j = 0; j < people; j++) 
	{
		list[j] = -1;
	}

	*success = 0;
	*i = -1;
}

void printTest(char const *argv[], int *list, int people)
{
	int i;
	
	for (i = 0; i < people; i++) 
	{
		printf ("person %d got person %d\n", i+2, list[i]+2);
	}
	printf("\n");
	for (i = 0; i < people; i++)
	{
		printf("%s:\t\t%s\n",argv[i+2],argv[list[i]+2]);
	}

}

int readRules(char rules[][LINESIZE])
{
	int i = 0;
	int numLines;

	FILE * filePtr = NULL;
	filePtr = fopen("RULES","r");
	
	if (filePtr == NULL)
	{
		fprintf(stderr, "Fatal: Failed to open file\n");
		fprintf(stderr, "Invalid filename or filepath\n");
		exit(0);
	}
    
    while (fgets(rules[i],LINESIZE,filePtr) != NULL)
    {
    	i++;
    	// printf("%s",rules[i] );
    }
	numLines = i;
	fclose(filePtr);
	
	return numLines;	
}

void printToFile(char const *argv[], int *list, int people,int numLines, char rules[][LINESIZE])
{
	FILE * filePtr;
	int i;
	char tempName[100];
	
	sprintf(tempName,"Results/%s",argv[1]);
	mkdir(tempName,0777);
	
	for (i = 0; i < people; ++i)
	{
		char fileName[100];
		sprintf(fileName,"%s/%s.txt",tempName,argv[i+2]);
		
		filePtr = fopen(fileName,"w");
		if (filePtr == NULL)
		{
			fprintf(stderr, "Fatal: Failed to open file\n");
			fprintf(stderr, "Invalid filename or filepath\n");
			exit(0);
		}
		
		fprintf(filePtr, "You are the secret santa for %s!\n\n",argv[list[i]+2]);
		for (int j = 0; j < numLines; ++j)
		{
			fprintf(filePtr, "%s",rules[j]);
		}
		fclose(filePtr);
	}
}

int main (int argc, char const *argv[]) 
{
	int people = argc-2;

	int randn;
	int list[people];
	int i;
	int success;
	reset(list,&success,&i,people);

	srand(time(NULL));
	success = 1;

	for (i = 0; i < people; i++) 
	{

		randn = rand()%people;

		for (int j = 0; j < people; j++) 
		{

			if (list[j] == randn) 
			{
				reset(list,&success,&i,people);
			}
		}

		if (randn == i) 
		{
			reset(list,&success,&i,people);
		} 
		else 
		{
			success = 1;
		}

		if (success == 1) 
		{
			list[i] = randn;
		}
	}

	#ifdef DEBUG
		printTest(argv, list, people);
	#endif	//DEBUG

	char rules[FILELENGTH][LINESIZE];
	int numLines = readRules(rules);
	printToFile(argv, list, people, numLines, rules);

	return 0;	
}