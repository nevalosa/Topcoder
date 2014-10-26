//You can include standard C++ language libraries that you want use.//
#include <stdio.h>
class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions, 
but main function call "solution" function only. */

};



void algorithm::solution(char *input, char *output){

/* User Implementation
 1.   	first argument is input path(include file name)
        second argument is output path(include file name).
 2.		  you must parsing the input data form input file.
 3. 		you must write the output data into text file.
 */
	int t, m, n;
	FILE *fin = fopen(input, "r");
	FILE *fout = fopen(output, "w");
	
	fscanf(fin, "%d", &t);
	for(int i = 0; i < t; i++)
	{
		fscanf(fin, "%d %d", &m, &n);
		
		int **arr;
		arr = new int*[m];
		for(int j = 0; j < m; j++) arr[j] = new int[n];
		for(int j = 0; j < m; j++)
			for(int k = 0; k < n; k++)
				fscanf(fin, "%d", &arr[j][k]);

		int cnt = 0;

		for(int j = 0; j < m; j++)
		{
			int run = 0;
			
			for(int k = 0; k < n; k++)
			{
				if(arr[j][k]) 
				{
					if(run >= 2) cnt++;
					run = 0;
				}
				else run++;
			}
			if(run >= 2) cnt++;
		}
		for(int j = 0; j < n; j++)
		{
			int run = 0;
			
			for(int k = 0; k < m; k++)
			{
				if(arr[k][j]) 
				{
					if(run >= 2) cnt++;
					run = 0;
				}
				else run++;
			}
			if(run >= 2) cnt++;
		}

		fprintf(fout, "Case# %d\n", i + 1);
		fprintf(fout, "%d\n", cnt);
	}
}
