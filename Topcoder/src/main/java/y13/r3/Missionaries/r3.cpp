//You can include standard C++ language libraries that you want use.//
#include <cstdio>
int n_miss;
int n_carn;
int capa;

bool ch[10][10][10];

long long sol;

class algorithm {
public:
    void solution(char *input, char *output);
    void go(int miss, int carn, int boat, int steps);
    bool valid(int miss, int carn, int boat);
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
        fscanf(R, "%d %d %d", &n_miss, &n_carn, &capa);

        for (int i = 0; i < 10; i++)
            for (int j = 0; j < 10; j++)
                for (int k = 0; k < 10; k++)
                    ch[i][j][k] = false;

        sol = 0;
        go(n_miss, n_carn, 1, 0);
        fprintf(W, "%lld\n", sol);
    }
    fclose(R);
    fclose(W);
    return;
}

bool algorithm::valid(int miss, int carn, int boat) {
    if (miss > 0 && miss < carn) return false;
    if (n_miss - miss > 0 && n_miss - miss < n_carn - carn) return false;
    return true;
}

void algorithm::go(int miss, int carn, int boat, int steps) {

    //      printf("miss=%d carn=%d boat=%d\n",miss,carn,boat);
    if (miss == 0 && carn == 0 && boat == 0) {
        sol++;
        return;
    }

    if (boat) { // boat on wrong side
        for (int i = 0; i <= miss; i++) {
            for (int j = 0; j <= carn; j++) {
                if ((i + j > 0) && (i + j <= capa) && (valid(miss - i, carn - j, 0) == true) && ch[miss][carn][boat] == false) {
                    ch[miss][carn][boat] = true;
                    go(miss - i, carn - j, 0, steps + 1);
                    ch[miss][carn][boat] = false;
                }
            }
        }
    } else { // boat on right side
        for (int i = 0; i <= n_miss - miss; i++) {
            for (int j = 0; j <= n_carn - carn; j++) {
                if ((i + j > 0) && (i + j <= capa) && (valid(miss + i, carn + j, 1) == true && ch[miss][carn][boat] == false)) {
                    ch[miss][carn][boat] = true;
                    go(miss + i, carn + j, 1, steps + 1);
                    ch[miss][carn][boat] = false;
                }
            }
        }
    }
}
