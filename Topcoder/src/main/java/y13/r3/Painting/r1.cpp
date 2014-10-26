//You can include standard C++ language libraries that you want use.//

#include <vector>
#include <stdio.h>

typedef std::vector<int> Vec;
typedef std::vector<Vec> Mat;

class algorithm {
public:
    void solution(char *input, char *output);
    unsigned int solve(const Mat& m);
};



using namespace std;

unsigned int algorithm::solve(const Mat &m) {
    int v[m.size()];
    int size = m.size();
    int N = 0;

    int cur = 0;
    v[cur] = 3;
    do {
        if (cur == size) {
            N++;
            cur--;
            continue;
        }
        v[cur]++;
        for (int i = 0; i < cur; i++) {
            if (m[cur][i] && v[cur] == v[i]) {
                v[cur]++;
                i = -1;
            }
        }
        if (v[cur] == 5) {
            cur--;
            continue;
        }
        cur++;
        v[cur] = 0;
    } while (cur != -1);
    return 4 * N;
}

void algorithm::solution(char *input, char *output) {
    FILE* fin;
    FILE* fout;
    fin = fopen(input, "r");
    fout = fopen(output, "w+");
    int N;
    fscanf(fin, "%d", &N);
    for (int i = 0; i < N; i++) {
        int n;
        fscanf(fin, "%d", &n);
        Mat m;
        Vec v(n, 0);
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < n; i++) {
                fscanf(fin, "%d", &v[i]);
            }
            m.push_back(v);
        }
        fprintf(fout, "%u", solve(m));
        if (i != N - 1) {
            fprintf(fout, "\n");
        }
    }
}
