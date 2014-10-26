//You can include standard C++ language libraries that you want use.//
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

class algorithm {
public:
    void solution(char *input, char *output);

    /* You can add your own class functions, 
    but main function call "solution" function only. */

};

int swapFlag(int flag) {
    if (flag == 1) return 0;
    if (flag == 0) return 1;
    return -1;
}

void algorithm::solution(char *input, char *output) {

    /* User Implementation
     1.   	first argument is input path(include file name)
            second argument is output path(include file name).
     2.		  you must parsing the input data form input file.
     3. 		you must write the output data into text file.
     */

    FILE* fin = fopen(input, "r");
    FILE* fout = fopen(output, "w");

    int T;
    fscanf(fin, "%d", &T);

    for (int t = 1; t <= T; t++) {
        int N;
        fscanf(fin, "%d", &N);
        vector<int> flags;
        vector<int> order;
        for (int i = 0; i < N; i++) {
            int flag;
            fscanf(fin, "%d", &flag);
            flags.push_back(flag);
        }
        bool isloop = true;
        while (isloop) {
            isloop = false;
            for (int i = 0; i < N; i++) {
                if (flags[i] == 0) {
                    flags[i] = -1;
                    if (i - 1 >= 0) flags[i - 1] = swapFlag(flags[i - 1]);
                    if (i + 1 < N) flags[i + 1] = swapFlag(flags[i + 1]);
                    isloop = true;
                    order.push_back(i + 1);
                }
            }
        }
        fprintf(fout, "Case# %d\n", t);
        if (order.size() == N) {
            for (int i = 0; i < N; i++) {
                if (i) fprintf(fout, " ");
                fprintf(fout, "%d", order[i]);
            }
            fprintf(fout, "\n");
        }
        else {
            fprintf(fout, "-1\n");
        }
    }
    fclose(fout);
    fclose(fin);
}