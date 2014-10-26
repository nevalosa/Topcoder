#include <stdio.h>

class algorithm {
public:
    void solution(char *input, char *output);

    /* You can add your own class functions, 
    but main function call "solution" function only. */

};





const int N = 10000;
int cards[2 * N - 1];

FILE* fin;
FILE* fout;

void solve(int n) {
    int first = 2 * (n - 1);
    int last = first;
    cards[last] = n;
    for (int i = n - 1; i >= 1; i--) {
        cards[--first] = i;
        cards[--first] = cards[last--];
    }
}

void algorithm::solution(char* input, char* output) {
    fin = fopen(input, "r");
    fout = fopen(output, "w+");
    int nTests;
    fscanf(fin, "%d", &nTests);
    for (int i = 0; i < nTests; i++) {
        int n;
        fscanf(fin, "%d", &n);
        solve(n);
        for (int i = 0; i < n; i++) {
            fprintf(fout, "%d ", cards[i]);
        }
        fprintf(fout, "\n");
    }
    fclose(fin);
    fclose(fout);
}