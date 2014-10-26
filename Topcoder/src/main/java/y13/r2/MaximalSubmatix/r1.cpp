//You can include standard C++ language libraries that you want use.//
#include <stdlib.h>
#include <stdio.h>

int A[1001][1001];

int L[1001];
int R[1001];

int g_max;
int g_x1, g_y1, g_x2, g_y2;

void maxArea(int a[], int r, int n) {
    int i;
    for (i = 0; i < n; i++) {
        L[i] = i;
        while (L[i] > 0 && a[i] <= a[L[i] - 1]) L[i] = L[L[i] - 1];
        //        printf("l:%d:%d ", i, L[i]);
    }
    for (i = n - 1; i >= 0; i--) {
        R[i] = i;
        while (R[i] < n - 1 && a[i] <= a[R[i] + 1]) R[i] = R[R[i] + 1];
        //        printf("r:%d:%d ", i, R[i]);
    }
    //    printf("\n");

    for (i = 0; i < n; i++) {
        int len = R[i] - L[i] + 1;
        int s = a[i] * len;
        if (s > g_max) {
            g_max = s;
            g_x1 = L[i];
            g_y1 = r - a[i] + 1;
            g_x2 = R[i];
            g_y2 = r;
        }
    }
}

void solution(char *input, char *output) {

    /* User Implementation
     1.   	first argument is input path(include file name)
            second argument is output path(include file name).
     2.		  you must parsing the input data form input file.
     3. 		you must write the output data into text file.
     */

    FILE* fin = fopen(input, "r");
    FILE* fout = fopen(output, "w");

    int T, t;
    fscanf(fin, "%d", &T);

    for (t = 1; t <= T; t++) {
        int i, j, r, c;
        fscanf(fin, "%d%d", &r, &c);
        for (i = 0; i < r; i++) for (j = 0; j < c; j++) A[i][j] = 0;
        for (i = 0; i < r; i++) {
            for (j = 0; j < c; j++) {
                fscanf(fin, "%d", &A[i][j]);
                if (i > 0 && A[i][j]) A[i][j] = A[i - 1][j] + 1;
            }
        }
        g_max = 0;
        g_x1 = g_y1 = g_x2 = g_y2 = 0;
        for (i = 0; i < r; i++) {
            maxArea(A[i], i, c);
        }
        fprintf(fout, "Case# %d\n", t);
        fprintf(fout, "%d %d %d %d %d\n", g_max, g_y1 + 1, g_x1 + 1, g_y2 + 1, g_x2 + 1);
    }

    fclose(fin);
    fclose(fout);
}