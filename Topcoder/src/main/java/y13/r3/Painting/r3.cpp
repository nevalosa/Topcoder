//You can include standard C++ language libraries that you want use.//
#include <cstdio>
#include <cstring>

int color[33];
int a[33][33];
int n;

class algorithm {
public:
    void solution(char *input, char *output);
    bool valid(void);
    int func(int idx);

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
        fscanf(R, "%d", &n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                fscanf(R, "%d", &a[i][j]);

        for (int i = 0; i < n; i++) color[i] = -1;
        fprintf(W, "%d\n", func(0));
    }
    fclose(R);
    fclose(W);
    return;
}

bool algorithm::valid(void) {
    for (int i = 0; i < n; i++) {
        if (color[i] != -1) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] && color[i] == color[j]) return false;
            }
        }
    }
    return true;
}

int algorithm::func(int idx) {

    if (valid() == false) return 0;
    if (idx == n) return 1;

    int ans = 0;
    for (int i = 0; i < 4; i++) {
        color[idx] = i;
        ans += func(idx + 1);
        color[idx] = -1;
    }
    return ans;
}