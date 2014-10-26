#include <fstream>
#include <string>

class algorithm
{
public:
    void solution(char* input, char* output);
    void solve(std::ifstream & fin, std::ofstream & fout);
};

void algorithm::solve(std::ifstream & fin, std::ofstream & fout)
{
    int fake;
    std::string s, s1;
    fin>>fake>>s>>s1;
    s1 = s1+s1;
    int res = s1.find(s, 0);
    fout<<((res==std::string::npos)?-1:res)<<std::endl;
}

void algorithm::solution(char *input, char *output)
{
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
