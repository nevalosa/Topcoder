//You can include standard C++ language libraries that you want use.//
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

class algorithm
{

public:
void solution(char *input, char *output);

/* You can add your own class functions, 
but main function call "solution" function only. */

};

using namespace std;
 
//----------------------------
//Returns a vector containing the zero based index of 
//  the start of each match of the string K in S.
//  Matches may overlap
//----------------------------
int KMP(string S, string K)
{
        vector<int> T(K.size() + 1, -1);
        vector<int> matches;
 
        if(K.size() == 0)
        {
			return -1;
        }
        for(int i = 1; i <= K.size(); i++)
        {
                int pos = T[i - 1];
                while(pos != -1 && K[pos] != K[i - 1]) pos = T[pos];
                T[i] = pos + 1;
        }
 
        int sp = 0;
        int kp = 0;
        while(sp < S.size())
        {
                while(kp != -1 && (kp == K.size() || K[kp] != S[sp])) kp = T[kp];
                kp++;
                sp++;
                if(kp == K.size()) 
					return sp - K.size();
        }
 
		return -1;
}


void algorithm::solution(char *input, char *output){

/* User Implementation
 1.   	first argument is input path(include file name)
        second argument is output path(include file name).
 2.		  you must parsing the input data form input file.
 3. 		you must write the output data into text file.
 */
	int t, n;
	string s1, s2, s2_dup;

	ifstream fin(input);
	FILE *fout = fopen(output, "w");
	
	fin >> t;
	for(int i = 0; i < t; i++)
	{
		fin >> n;
		fin >> s1 >> s2;
		
		s2_dup = s2 + s2;
		
		fprintf(fout, "%d\n", KMP(s2_dup, s1));
	}
}
