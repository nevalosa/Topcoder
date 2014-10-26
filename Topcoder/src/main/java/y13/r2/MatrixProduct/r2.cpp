//You can include standard C++ language libraries that you want use.//
#include <cstdio>
#include <cstdlib>

#define MOD 100000007

long long n, m;
long long a[30][111][111];
long long sol[2][111][111];

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

    int t;
    FILE *R = fopen(input, "r");
    FILE *W = fopen(output, "w");

    fscanf(R, "%d", &t);
    for (int z = 1; z <= t; z++) {
        fscanf(R, "%lld %lld", &n, &m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                fscanf(R, "%lld", &a[0][i][j]);

        for (int i = 1; i < 30; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    a[i][j][k] = 0;
                    for (int l = 0; l < n; l++) {
                        a[i][j][k] = (a[i][j][k] + ((a[i - 1][j][l] * a[i - 1][l][k]) % MOD)) % MOD;
                    }
                }
            }
        }

        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (j == k) sol[0][j][k] = 1;
                else sol[0][j][k] = 0;
            }
        }

        long long tmp = m;

        int i = 0;
        int sol_idx = 0;
        while (tmp > 0) {

            if (tmp % 2 == 1) {

                sol_idx = 1 - sol_idx;
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        sol[sol_idx][j][k] = 0;
                    }
                }

                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < n; k++) {
                        for (int l = 0; l < n; l++) {
                            sol[sol_idx][j][k] = (sol[sol_idx][j][k] + ((sol[1 - sol_idx][j][l] * a[i][l][k]) % MOD)) % MOD;
                        }
                    }
                }
            }

            tmp /= 2;
            i++;
        }

        fprintf(W, "Case# %d\n", z);
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                fprintf(W, "%d ", sol[sol_idx][j][k]);
            }
            fprintf(W, "\n");
        }
    }
    fclose(R);
    fclose(W);

    return;
}
