//You can include standard C++ language libraries that you want use.//
#include <cstdio>

int s[66666];

class algorithm {
public:
    void solution(char *input, char *output);

    /* You can add your own class functions, 
    but main function call "solution" function only. */

};

void algorithm::solution(char *input, char *output) {

    /* User Implementation
     1.   	first argument is input path(include file name)
            second argument is output path(include file name).
     2.		  you must parsing the input data form input file.
     3. 		you must write the output data into text file.
     */
    FILE *R = fopen(input, "r");
    FILE *W = fopen(output, "w");

    int t;
    fscanf(R, "%d", &t);
    while (t--) {

        int n;
        int st, ed;
        st = ed = 33333;
        fscanf(R, "%d", &n);
        s[st] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = st; j <= ed; j++) s[j]++;
            st--;
            s[st] = 1;
            st--;
            s[st] = s[ed];
            ed--;
        }

        for (int i = st; i <= ed; i++)
            fprintf(W, "%d ", s[i]);
        fprintf(W, "\n");
    }
    fclose(R);
    fclose(W);
    return;
}
