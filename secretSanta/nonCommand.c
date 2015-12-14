#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define PEOPLE 16

/*
	initializes array to -1
*/
void reset(int *list, int *success, int *i)
{
	for (int j = 0; j < PEOPLE; j++) 
	{
		list[j] = -1;
	}

	*success = 0;
	*i = -1;
}

int main (void) 
{

	int randn;
	int list[PEOPLE];
	int i;
	int success;
	reset(list,&success,&i);

	srand(time(NULL));
	success = 1;

	for (i = 0; i < PEOPLE; i++) 
	{

		randn = rand()%PEOPLE;

		for (int j = 0; j < PEOPLE; j++) 
		{

			if (list[j] == randn) 
			{
				reset(list,&success,&i);
			}
		}

		if (randn == i) 
		{
			reset(list,&success,&i);
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

	for (i = 0; i < PEOPLE; i++) 
	{
		printf ("person %d got person %d\n", i, list[i]);
	}

	return 0;	
}