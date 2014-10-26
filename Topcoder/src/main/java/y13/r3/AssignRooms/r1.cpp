//You can include standard C++ language libraries that you want use.//

#include <stdio.h>
#include <stdlib.h>

struct Meet {
    int beg;
    int end;
    int num;
};

class algorithm {
public:
    void solution(char *input, char *output);
    void solve(int K, const Meet ms[], int N);
    Meet a[10000];
    int na;
};

FILE* fin;
FILE* fout;

void algorithm::solve(int K, const Meet ms[], int N) {
    na = 0;
    int cur[K];
    for (int i = 0; i < K; i++) {
        cur[i] = -1;
    }

    for (int i = 0; i < N; i++) {
        int minDif = 2000;
        int bestk = -1;
        for (int k = 0; k < K; k++) {
            int dif = ms[i].beg - cur[k];
            if (0 < dif && dif < minDif) {
                minDif = dif;
                bestk = k;
            }
        }
        if (bestk != -1) {
            a[na] = ms[i];
            a[na++].beg = bestk;
            cur[bestk] = ms[i].end;
        }
    }
}

int compMeet(const void* pleft, const void* pright) {
    Meet* left = (Meet*) pleft;
    Meet* right = (Meet*) pright;
    if (left->end != right->end) {
        return (left->end)>(right->end);
    } else {
        return (left->beg) >= (right->beg);
    }
}

int compMeetByRoom(const void* pleft, const void* pright) {
    return (((Meet*) pleft)->beg)>(((Meet*) pright)->beg);
}

void algorithm::solution(char *input, char *output) {
    FILE* fin = fopen(input, "r");
    FILE* fout = fopen(output, "w+");
    int C;
    fscanf(fin, "%d", &C);
    for (int c = 0; c < C; c++) {
        int N, K;
        fscanf(fin, "%d %d", &N, &K);
        Meet ms[N];
        for (int i = 0; i < N; i++) {
            int h0, m0, h1, m1;
            fscanf(fin, "%d %d %d %d", &h0, &m0, &h1, &m1);
            Meet m;
            m.num = i + 1;
            m.beg = h0 * 60 + m0;
            m.end = h1 * 60 + m1;
            ms[i] = m;
        }
        qsort(ms, N, sizeof (Meet), compMeet);
        if (c != 0) fprintf(fout, "\n");
        fprintf(fout, "Case# %d", c + 1);
        solve(K, ms, N);

        qsort(a, na, sizeof (Meet), compMeetByRoom);

        fprintf(fout, "\n%d ", a[0].num);
        for (int i = 1; i < na; i++) {
            if (a[i].beg != a[i - 1].beg) {
                fprintf(fout, "\n");
            }
            fprintf(fout, "%d ", a[i].num);
        }

    }
    fclose(fin);
    fclose(fout);
}
