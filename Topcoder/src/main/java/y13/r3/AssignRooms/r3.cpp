//You can include standard C++ language libraries that you want use.//
#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>


std::pair <int, std::pair <int, int> > m[11111];
int r[111];

std::vector <int> v[111];

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
    FILE *R = fopen(input, "r");
    FILE *W = fopen(output, "w");

    int t;
    fscanf(R, "%d", &t);
    for (int z = 1; z <= t; z++) {
        int n, k;
        fscanf(R, "%d %d", &n, &k);
        for (int i = 0; i < k; i++) r[i] = -1;
        for (int i = 0; i < n; i++) {
            int st_h, st_m, ed_h, ed_m;
            fscanf(R, "%d %d %d %d", &st_h, &st_m, &ed_h, &ed_m);
            m[i].second.second = i + 1;
            m[i].second.first = st_h * 60 + st_m;
            m[i].first = ed_h * 60 + ed_m;
        }

        std::sort(m, m + n);

        for (int i = 0; i < k; i++) v[i].clear();

        for (int i = 0; i < n; i++) {

            int best_idx = -1;
            for (int j = 0; j < k; j++) {
                if (r[j] < m[i].second.first) {
                    if (best_idx < 0) best_idx = j;
                    else if (r[best_idx] < r[j]) best_idx = j;
                }
            }

            if (best_idx >= 0) {
                v[best_idx].push_back(m[i].second.second);
                r[best_idx] = m[i].first;
            }
        }
        fprintf(W, "Case# %d\n", z);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < v[i].size(); j++) {
                fprintf(W, "%d ", v[i][j]);
            }
            fprintf(W, "\n");
        }
    }
    fclose(R);
    fclose(W);
    return;
}