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
        int n;
        infile >> n;
        vector<vector<int> > G;
        set<pair<int, int> > Map;
        vector<int> Color(n, 0); // all black
        vector<int> Same(n, 0);

        for (int i = 0; i < n; i++) {
            vector<int> line;
            int k;
            infile >> k;
            for (int j = 0; j < k; j++) {
                int tmp;
                infile >> tmp;
                line.push_back(tmp - 1);
            }
            Same[i] = line.size();
            Map.insert(make_pair(Same[i], i));
            G.push_back(line);
        }

        // solution
        while (1) {
            set<pair<int, int> >::iterator it = Map.end();
            --it;
            int num = it->first;
            int v = it->second;
            Map.erase(it);
            if (num <= 1)
                break;

            // change colors
            int newNum = 0;
            int curColor = Color[v];
            for (int k = 0; k < G[v].size(); k++) {
                int tmp = Same[G[v][k]];
                if (Color[G[v][k]] == curColor) {
                    // new color will be different dec same. update map
                    tmp--;
                } else {
                    // new color will be different same. was different
                    newNum++;
                    tmp++;
                }

                pair<int, int> oldPair = make_pair(Same[G[v][k]], G[v][k]);
                set<pair<int, int> >::iterator it = Map.find(oldPair);
                Map.erase(it);
                Same[G[v][k]] = tmp;
                Map.insert(make_pair(tmp, G[v][k]));

            }
            Color[v] = 1 - curColor;
            Same[v] = newNum;
            Map.insert(make_pair(Same[v], v));
        }

        int total = 0;
        vector<int> res;
        for (int i = 0; i < n; i++) {
            if (Color[i] == 0) {
                res.push_back(i + 1);
                total++;
            }
        }

        outfile << "Case# " << t + 1 << "\n";
        outfile << total << "\n";
        for (int i = 0; i < total; i++)
            outfile << res[i] << " ";
        outfile << "\n";
    }
    outfile.close();
}