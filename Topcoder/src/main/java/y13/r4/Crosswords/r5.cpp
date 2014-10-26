#include <stdio.h>

char a[1001][1001];

class algorithm
{
public:
    void solution(char *input, char *output);
    void solve(FILE *in, FILE *out);
};

void algorithm::solve(FILE *in, FILE *out)
{
    int M, N;
    fscanf(in, "%d %d", &M, &N);

    for(int m=0; m<M; ++m)
        for(int n=0; n<N; ++n)
            fscanf(in, "%d", &a[m][n]);

    int words = 0;
    int M1=M-1;
    int N1=N-1;

    for (int n = 0; n < N; ++n)
        for (int m = 0; m < M; ++m)
            if(a[m][n]==0)
                words = words +
                    ( (!m||a[m-1][n]) && (m<M1) && !a[m+1][n] ) +
                    ( (!n||a[m][n-1]) && (n<N1) && !a[m][n+1] );

    fprintf(out, "%d\n", words);
}

void algorithm::solution(char *input, char *output)
{
    FILE * in = fopen(input, "rt");
    FILE * out = fopen(output, "wt");

    int T;
    fscanf(in, "%d", &T);

    for(int t=1; t<=T; ++t)
    {
        fprintf(out, "Case# %d\n", t);
        solve(in, out);
    }

    fclose(out);
    fclose(in);
}
