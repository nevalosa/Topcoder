#include <cstdlib>
#include <cstdio>

class algorithm
{

public:
void solution(char *input, char *output);

};

char Model[101];
int Len;
int Depth;
FILE* FOUT;
void go(int depth) {
    if (depth == Depth) {
        fprintf(FOUT, "%s", Model);
    } else {
        for (int i = 0; Model[i]; ++i) {
            if (Model[i] == 'F') go(depth + 1);
            else fprintf(FOUT, "%c", Model[i]);
        }
    }
}

void algorithm::solution(char *input, char *output) {
    FILE* fin = fopen(input, "r");
    FILE* fout = fopen(output, "w");
    FOUT = fout;

    int T;
    fscanf(fin, "%d", &T);
    for (int t = 1; t <= T; ++t) {
        fscanf(fin, "%d%s", &Depth, Model);
        go(1);
        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);
}
