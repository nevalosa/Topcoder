//You can include standard C++ language libraries that you want use.//
#include <stdio.h>
#include <string.h>


class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions, 
but main function call "solution" function only. */

void readInput(FILE *fpInput);
void writeOutput(FILE *fpOutput, int nCaseNum);
void solveProblem();

void draw_fractal(FILE *fpOutput, int nDegree);

int N;
int word_len;

char word[1024];

};


void algorithm::readInput(FILE *fpInput)
{
	fscanf(fpInput, "%d", &N);
	fscanf(fpInput, "%s", word);

	word_len = strlen(word);
}

void algorithm::draw_fractal(FILE *fpOutput, int nDegree)
{
	if (nDegree == N)
	{
		fprintf(fpOutput, "%s", word);
		return;
	}

	for(int i=0;i < word_len; i++)
	{
		if(word[i] == 'F')
		{
			draw_fractal(fpOutput, nDegree + 1);
		}
		else
		{
			fprintf(fpOutput, "%c", word[i]);
		}
	}
}

void algorithm::writeOutput(FILE *fpOutput, int nCaseNum)
{
	draw_fractal(fpOutput, 1);

	fprintf(fpOutput, "\n");
}

void algorithm::solveProblem()
{
	return;
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
