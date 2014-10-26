//You can include standard C++ language libraries that you want use.//
#include <stdio.h>


class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions, 
but main function call "solution" function only. */

void readInput(FILE *fpInput);
void writeOutput(FILE *fpOutput, int nCaseNum);
void solveProblem();

int M, N;
int mat[1001][1001];
int word_cnt;

};


void algorithm::readInput(FILE *fpInput)
{
	fscanf(fpInput, "%d %d", &M, &N);

	for (int i=0;i < M; i++)
	{
		for (int j=0;j < N; j++)
		{
			fscanf(fpInput, "%d", &(mat[i][j]));
		}
	}

	word_cnt = 0;
}

void algorithm::writeOutput(FILE *fpOutput, int nCaseNum)
{
	fprintf(fpOutput, "Case# %d\n", nCaseNum);
	fprintf(fpOutput, "%d\n", word_cnt);
}

void algorithm::solveProblem()
{
	int i, j, letters;

	for(i=0;i<M;i++)
	{
		letters = 0;

		for(j=0;j<N;j++)
		{
			if(mat[i][j] == 0)
			{
				letters++;
			}
			else {
				if(letters > 1)	word_cnt++;
				letters = 0;
			}
		}
		if(letters > 1)	word_cnt++;
	}

	for(i=0;i<N;i++)
	{
		letters = 0;

		for(j=0;j<M;j++)
		{
			if(mat[j][i] == 0)
			{
				letters++;
			}
			else {
				if(letters > 1)	word_cnt++;
				letters = 0;
			}
		}
		if(letters > 1)	word_cnt++;
	}
}



void algorithm::solution(char *input, char *output){

/* User Implementation
 1.   	first argument is input path(include file name)
        second argument is output path(include file name).
 2.		  you must parsing the input data form input file.
 3. 		you must write the output data into text file.
 */
	FILE *fpInput, *fpOutput;
	
	fpInput = fopen(input, "rt");
	fpOutput = fopen(output, "wt");
	
	int nCase, nIdx;
	
	fscanf(fpInput, "%d", &nCase);
	for(nIdx = 0;nIdx < nCase; nIdx++ )
	{
		readInput(fpInput);
		solveProblem();
		writeOutput(fpOutput, nIdx + 1);
	}
	
	fclose (fpInput);
	fclose (fpOutput);
}
