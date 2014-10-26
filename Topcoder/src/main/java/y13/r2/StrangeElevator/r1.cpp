//You can include standard C++ language libraries that you want use.//
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <memory.h>
using namespace std;

class algorithm {
public:
    void solution(char *input, char *output);

    /* You can add your own class functions, 
    but main function call "solution" function only. */

};

const int INF = 987654321;

int K, N;
int n[1001];
int sum[1001];
int mem[1001][1001];
int pem[1001][1001];
int pre[1001][1001];

int presum() {
    sum[0] = n[0];
    for (int i = 1; i < N; i++)
        sum[i] = sum[i - 1] + n[i];
}

int getSum(int lo, int hi) {
    return sum[hi] - (lo == 0 ? 0 : sum[lo - 1]);
}

pair<int, int> getError(int lo, int hi) {
    int m = 0, s = 0;
    int len = hi - lo + 1;
    if (len % 2) {
        int t = len / 2;
        m = lo + t;
        s = getSum(m + 1, hi) - getSum(lo, m - 1);
    } else {
        int t = len / 2;
        m = lo + t;
        s = getSum(m, hi) - getSum(lo, m - 1);
    }
    return make_pair(m, s);
}

int go(int from, int parts) {
    if (from == N) return 0;
    if (parts == 0) return INF;
    int& res = mem[from][parts];
    if (res != -1) return res;
    res = INF;
    for (int i = 1; from + i <= N; ++i) {
        int next = go(from + i, parts - 1);
        pair<int, int> err = getError(from, from + i - 1);
        if (res > err.second + next) {
            res = err.second + next;
            pem[from][parts] = err.first;
            pre[from][parts] = from + i;
        }
    }
    return res;
}

void print(FILE* fout, int from, int parts) {
    if (parts == 0) return;
    if (parts < K) fprintf(fout, " ");
    fprintf(fout, "%d", n[pem[from][parts]]);
    print(fout, pre[from][parts], parts - 1);
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
        fscanf(fin, "%d%d", &K, &N);
        for (int i = 0; i < N; i++) fscanf(fin, "%d", &n[i]);
        memset(mem, -1, sizeof (mem));
        presum();
        int res = go(0, K);
        fprintf(fout, "Case# %d\n", t);
        fprintf(fout, "%d\n", res);
        print(fout, 0, K);
        fprintf(fout, "\n");
    }
}
