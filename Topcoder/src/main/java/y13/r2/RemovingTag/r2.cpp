//You can include standard C++ language libraries that you want use.//
#include <cstdio>
#include <cstdlib>
#define WHITE 0
#define BLUE 1

int a[11111];
int sol[11111];

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

        int t;
        FILE *R = fopen(input, "r");
        FILE *W = fopen(output, "w");

        fscanf(R, "%d", &t);
        for(int i=1; i<=t; i++){
                int n;
                fscanf(R,"%d",&n);
                for(int j=0; j<n; j++) fscanf(R,"%d",&a[j]);

                int start=0;
                int cur_w=-1;
                int sols=0;
                for(int j=0; j<n; j++){
                        if(a[j]==WHITE){

                                cur_w=j;
                                for(int k=cur_w; k>=start; k--){
                                        sol[sols]=k+1;
                                        sols++;
                                }

                                if(j<n-1){
                                        a[j+1] = 1-a[j+1];
                                        start=j+1;
                                }
                        }
                }

                fprintf(W, "Case# %d\n", i);

                if(sols==n){
                        for(int j=0; j<sols; j++)
                                fprintf(W,"%d ", sol[j]);
                }
                else fprintf(W,"-1");

                fprintf(W,"\n");
        }

        fclose(R);
        fclose(W);

        return;

}
