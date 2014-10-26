//You can include standard C++ language libraries that you want use.//
#include <stdio.h>

struct State {
    int m;
    int k;
    int s;
};

class algorithm {
public:
    void solution(char *input, char *output);
    int N;
    int solve(int nMi, int cap);
    int calcNPathes();
    int used[30];
    int cur;
    int mat1[30 * 30];
    int matn[30 * 30];
};

int isStep(const State& src, const State& dst, int cap) {
    if (src.s == dst.s) {
        return 0;
    }
    int dm = (dst.m - src.m) * src.s;
    int dk = (dst.k - src.k) * src.s;
    if (dm < 0 || dk < 0 || (dm + dk) > cap || (dm + dk) == 0) {
        return 0;
    }
    return 1;
}

int algorithm::calcNPathes() {
    if (used[cur] == N - 1) {
        return 1;
    }
    if (cur == N - 1) {
        return 0;
    }
    int nPa = 0;
    int src = used[cur];
    for (int i = 0; i < N; i++) {
        if (mat1[src * N + i] == 0) {
            continue;
        }
        int loop = 0;
        for (int j = 0; j < cur; j++) {
            if (used[j] == i) {
                loop = 1;
                break;
            }
        }
        if (loop) {
            continue;
        }
        used[++cur] = i;
        nPa += calcNPathes();
        --cur;
    }
    return nPa;
}

int algorithm::solve(int nMi, int cap) {
    N = 6 * nMi;
    State st[N];
    st[0].m = nMi;
    st[0].k = nMi;
    st[0].s = -1;
    st[N - 1].m = 0;
    st[N - 1].k = 0;
    st[N - 1].s = 1;
    cur = 1;
    for (int i = 0; i < nMi; i++) {
        st[cur].m = nMi;
        st[cur].k = i;
        st[cur].s = 1;
        st[cur + 1] = st[cur];
        st[cur + 1].s = -1;
        cur += 2;

        st[cur].m = 0;
        st[cur].k = i + 1;
        st[cur].s = 1;
        st[cur + 1] = st[cur];
        st[cur + 1].s = -1;
        cur += 2;

        if (i != 0) {
            st[cur].m = i;
            st[cur].k = i;
            st[cur].s = 1;
            st[cur + 1] = st[cur];
            st[cur + 1].s = -1;
            cur += 2;
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matn[i * N + j] = (i == j);
            mat1[i * N + j] = isStep(st[i], st[j], cap);
        }
    }

    cur = 0;
    used[0] = 0;
    int nPathes = calcNPathes();
    return nPathes;
}

FILE* fin;
FILE* fout;

void algorithm::solution(char *input, char *output) {
    fin = fopen(input, "r");
    fout = fopen(output, "w+");
    int T;
    fscanf(fin, "%d", &T);
    for (int i = 0; i < T; i++) {
        int m;
        int k;
        int cap;
        fscanf(fin, "%d %d %d", &m, &k, &cap);

        int nPa = solve(m, cap);
        if (i != 0) {
            fprintf(fout, "\n");
        }
        fprintf(fout, "%d", nPa);
    }
    fclose(fin);
    fclose(fout);
}
