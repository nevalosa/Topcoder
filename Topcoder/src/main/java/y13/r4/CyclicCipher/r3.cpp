#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

class algorithm
{

public:
void solution(char *input, char *output);

};

vector<int> kmp_prefix(const string& P) {
    int m = P.size();
    vector<int> pi(m, 0);
    int a = 1;
    int b = 0;
    while (a + b < m) {
        if (P[a + b] == P[b]) {
            b += 1;
            pi[a + b - 1] = b;
        } else {
            if (b == 0) {
                a += 1;
            } else {
                a += b - pi[b - 1];
                b = pi[b - 1];
            }
        }
    }
    return pi;
}

int kmp_search(const string& H, const string& P) {
    int n = H.size();
    int m = P.size();
    vector<int> pi = kmp_prefix(P);
    int a = 0;
    int b = 0;
    int res = -1;
    while (a <= n - m) {
        if (b < m && H[a + b] == P[b]) {
            b += 1;
            if (b == m) res = a;
        } else {
            if (b == 0) {
                a += 1;
            } else {
                a += b - pi[b - 1];
                b = pi[b - 1];
            }
        }
    }
    return res;
}

char in1[250001];
char in2[250001];

void algorithm::solution(char *input, char *output) {
    FILE* fin = fopen(input, "r");
    FILE* fout = fopen(output, "w");

    int T;
    fscanf(fin, "%d", &T);
    for (int t = 1; t <= T; ++t) {
        int n;
        fscanf(fin, "%d%s%s", &n, in1, in2);
        string H = in1;
        string P = in2;
        H = H + H;
        int res = kmp_search(H, P);
        fprintf(fout, "%d\n", res < 0 ? -1 : n - res);
    }

    fclose(fin);
    fclose(fout);
}
