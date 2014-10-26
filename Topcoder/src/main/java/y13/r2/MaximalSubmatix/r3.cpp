//You can include standard C++ language libraries that you want use.//

#include "stdio.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include <set>
#include <map>
#include <stack>

using namespace std;

class algorithm {
public:
    void solution(char *input, char *output);
};

void algorithm::solution(char *input, char *output) {
    ifstream infile(input);
    ofstream outfile;
    outfile.open(output);

    int T;
    infile >> T;

    for (int t = 0; t < T; t++) {
        int n, m;
        infile >> n >> m;
        m = m + 1;
        vector<vector<int> > A(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m - 1; j++) {
                infile >> A[i][j];
            }

        vector<vector<int> > H(n, vector<int>(m, 0));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) {
                if (A[i][j] == 1) {
                    H[i][j] = 1;
                    if (i > 0)
                        H[i][j] += H[i - 1][j];
                }
            }

        int bestVal = 0;
        int bestI1 = 0, bestJ1 = 0;
        int bestI2 = 0, bestJ2 = 0;
        for (int i = 0; i < n; i++) {
            stack<pair<int, int> > Stack;
            Stack.push(make_pair(0, 0));

            for (int j = 0; j < m; j++) {
                int h = Stack.top().first;
                int pos = Stack.top().second;

                if (H[i][j] > h)
                    Stack.push(make_pair(H[i][j], j));
                else {
                    while (H[i][j] < h) {
                        pos = Stack.top().second;
                        Stack.pop();
                        if (bestVal < (j - pos) * h) {
                            bestVal = (j - pos) * h;
                            bestI1 = i - h + 1;
                            bestJ1 = pos;
                            bestI2 = i;
                            bestJ2 = j - 1;
                        }

                        h = Stack.top().first;
                    }
                    Stack.push(make_pair(H[i][j], pos));
                }
            }
        }



        outfile << "Case# " << t + 1 << "\n";
        outfile << bestVal << " " << bestI1 + 1 << " " << bestJ1 + 1 << " " << bestI2 + 1 << " " << bestJ2 + 1 << " ";
        outfile << "\n";
    }
    outfile.close();
}