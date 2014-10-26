/*
 * main.cpp
 *
 *  Created on: Feb 21, 2013
 *      Author: a-grigoriev
 */

#include <fstream>
#include <vector>
#include <stack>

class algorithm {
public:
    void solution(char *input, char *output);

private:
    void inputData(std::ifstream & in);
    void outputResult(std::ofstream & out) const;

    std::vector < std::vector < size_t > > g;
    std::vector < int > color;
    size_t n;

    void dfs(size_t v);
};

void algorithm::inputData(std::ifstream & in) {
    size_t i = 0, x = 0, v = 0;

    g.clear();
    color.clear();

    in >> n;

    g.resize(n);
    color.assign(n, 0);

    for (; i < n; ++i) {
        in >> x;
        while (x--) {
            in >> v;
            g[i].push_back(--v);
        }
    }
}

void algorithm::outputResult(std::ofstream & out) const {
    std::vector<size_t> result;
    for (size_t i = 0; i < n; ++i) {
        if (color[i] == 1) {
            result.push_back(i + 1);
        }
    }
    if (!result.size()) {
        result.push_back(1);
    }
    if (result.size() == n) {
        result.pop_back();
    }
    out << result.size() << std::endl;
    for (size_t i = 0; i < result.size(); ++i) {
        out << result[i] << " ";
    }
    out << std::endl;
}

void algorithm::solution(char *input, char *output) {
    std::ifstream in(input);
    std::ofstream out(output);

    size_t test_cases_count;
    in >> test_cases_count;

    for (int test_case = 1; test_case <= test_cases_count; ++test_case) {
        inputData(in);

        for (int i = 0; i < n; ++i) {
            dfs(i);
        }

        out << "Case# " << test_case << std::endl;
        outputResult(out);
    }

    in.close();
    out.close();
}

void algorithm::dfs(size_t v) {
    size_t cnt = 0;
    for (size_t i = 0; i < g[v].size(); ++i) {
        cnt += (color[ g[v][i] ] == color[ v ]);
    }

    if (cnt > 1) {
        color[v] ^= 1;
        for (size_t i = 0; i < (int) g[v].size(); ++i)
            if (color[ g[v][i] ] == color[ v ])
                dfs(g[v][i]);
    }
}
