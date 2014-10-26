//You can include standard C++ language libraries that you want use.//
#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;

class algorithm {
public:
    void solution(char *input, char *output);

    /* You can add your own class functions, 
    but main function call "solution" function only. */

};

typedef long long ll;

int M[101][101];
int MOD = 100000007;

vector<vector<ll> > identityMatrix(int n) {
    vector<vector<ll> > res(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) res[i][i] = 1;
    return res;
}

vector<vector<ll> > mulMatrix(
        vector<vector<ll> >& a,
        vector<vector<ll> >& b,
        ll MOD) {
    int i, j, k;
    vector<vector<ll> > res(a.size(), vector<ll>(b.size(), 0));
    for (int i = 0; i < a.size(); i++) {
        for (int j = 0; j < b.size(); j++) {
            for (int k = 0; k < b.size(); k++) {
                res[i][j] = (res[i][j] + (a[i][k] * b[k][j]) % MOD) % MOD;
            }
        }
    }
    return res;
}

vector<vector<ll> > powerMatrix(
        vector<vector<ll> >& a, ll p, ll MOD) {
    int n = a.size();
    if (p == 0) return identityMatrix(n);
    if (p == 1) return a;
    vector<vector<ll> > res = powerMatrix(a, p / 2, MOD);
    res = mulMatrix(res, res, MOD);
    if (p % 2) res = mulMatrix(res, a, MOD);
    return res;
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
        int N, M;
        fscanf(fin, "%d%d", &N, &M);
        vector<vector<ll> > a(N, vector<ll>(N, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                int e;
                fscanf(fin, "%d", &e);
                a[i][j] = e;
            }
        }
        vector<vector<ll> > res = powerMatrix(a, M, MOD);
        fprintf(fout, "Case# %d\n", t);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (j) fprintf(fout, " ");
                fprintf(fout, "%lld", res[i][j]);
            }
            fprintf(fout, "\n");
        }
    }
    fclose(fin);
    fclose(fout);
}