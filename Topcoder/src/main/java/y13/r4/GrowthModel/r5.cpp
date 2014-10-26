#include <fstream>
#include <iostream>
#include <string>

class algorithm
{
    std::string s;
public:
    void solution(char* input, char* output);
    void solve(std::ifstream & fin, std::ofstream & fout);
    void out(int n, std::ofstream & fout);
};

void algorithm::out(int n, std::ofstream & fout)
{
    if(n==1)
    {
        fout<<s;
    }
    else
    {
        int len = s.length();
        for(int i=0; i<len; ++i)
        {
            if(s[i]=='F')
                out(n-1, fout);
            else
                fout<<s[i];
        }
    }
}

void algorithm::solve(std::ifstream & fin, std::ofstream & fout)
{
    int n;
    fin>>n>>s;
    out(n, fout);
    fout<<std::endl;
}

void algorithm::solution(char *input, char *output)
{
    std::ios_base::sync_with_stdio(0);

    std::ifstream fin(input);
    std::ofstream fout(output);

    int test_cases;
    fin >> test_cases;

    for (int test_case = 1; test_case <= test_cases; ++test_case)
    {
//        fout << "Case# " << test_case << std::endl;
        solve(fin, fout);
    }

    fin.close();
    fout.close();
}
