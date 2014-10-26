#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>

const int MINUS_INF = -10000000;

using namespace std;

class algorithm
{
    int R, C;
    std::vector<std::vector<char> > in_data;
    std::vector<std::vector<int> > a;
    std::vector<int> value;
public:
    void clear();
    void load(std::ifstream & fin);
    void convert();
    void solution(char* input, char* output);
    void solve(std::ifstream & fin, std::ofstream & fout);
    void mark(std::vector<std::vector<int> > & tmp, std::pair<int, int> start);
    void printA();
};

int ones_count(int x)
{
    int count = 0;
    for(int i=0, j=1; i<18; ++i, j<<=1)
    {
        if(x&j)++count;
    }
    return count;
}

void algorithm::printA()
{
//    for(int i=0; i<a.size(); ++i)
//    {
//        for(int j=0; j<a.size(); ++j)
//        {
//            std::cout<<a[i][j]<<" ";
//        }
//        std::cout<<std::endl;
//    }
}

void algorithm::mark(std::vector<std::vector<int> > & tmp, std::pair<int, int> start)
{
    tmp[start.first][start.second] = 0;
    std::queue<std::pair<int, int> > q;
    q.push(start);

    while (!q.empty())
    {
        std::pair<int, int> el = q.front();
        q.pop();

        int x = el.first, y = el.second;

        if ((x > 0) && (in_data[x - 1][y] != '~'))
        {
            if(tmp[x - 1][y]<(tmp[x][y] - 2))
            {
                tmp[x - 1][y]=(tmp[x][y] - 2);
                q.push(std::make_pair(x - 1, y));
            }
        }
        if ((x < (R - 1)) && (in_data[x + 1][y] != '~'))
        {
            if(tmp[x + 1][y]<(tmp[x][y] - 2))
            {
                tmp[x + 1][y]=(tmp[x][y] - 2);
                q.push(std::make_pair(x + 1, y));
            }
        }
        if ((y > 0) && (in_data[x][y - 1] != '~'))
        {
            if(tmp[x][y-1]<(tmp[x][y] - 2))
            {
                tmp[x][y-1]=(tmp[x][y] - 2);
                q.push(std::make_pair(x, y-1));
            }
        }
        if ((y < (C - 1)) && (in_data[x][y + 1] != '~'))
        {
            if(tmp[x][y+1]<(tmp[x][y] - 2))
            {
                tmp[x][y+1]=(tmp[x][y] - 2);
                q.push(std::make_pair(x, y+1));
            }
        }
    }
}

void algorithm::convert()
{
    std::vector<std::pair<int, int> > vert(1);

    for (int r = 0; r < R; ++r)
        for (int c = 0; c < C; ++c)
            if ((in_data[r][c] <= '9') && (in_data[r][c] >= '1'))
                vert.push_back(std::make_pair(r, c));
            else if (in_data[r][c] == 'E')
                vert[0] = std::make_pair(r, c);

    int N = vert.size();
    value.resize(N);

    for(int i=0; i<N; ++i)
    {
        value[i] = in_data[vert[i].first][vert[i].second] - '0';
    }

    a.resize(N);
    for (int i = 0; i < N; ++i)
        a[i].resize(N);

    for (int i = 0; i < N; ++i)
    {
        std::vector<std::vector<int> > tmp(R);
        for (int r = 0; r < R; ++r)
        {
            tmp[r].reserve(C);
            for (int j = 0; j < C; ++j)
            {
                tmp[r].push_back(MINUS_INF);
            }
        }
        mark(tmp, vert[i]);

//        std::cout<<" -->\n";
//        for(int x=0; x<tmp.size(); ++x)
//        {
//            for(int y=0; y<tmp[x].size(); ++y)
//            {
//                std::cout<<tmp[x][y]<<" ";
//            }
//            std::cout<<"\n";
//        }

        for(int j=0; j<N; ++j)
        {
            a[i][j] = tmp[vert[j].first][vert[j].second] +
                    ((in_data[vert[j].first][vert[j].second]=='E')?0:(in_data[vert[j].first][vert[j].second] - '0'));
        }
    }
}

void algorithm::clear()
{
    in_data.clear();
    a.clear();
    value.clear();
}

void algorithm::load(std::ifstream & fin)
{
    fin >> R >> C;
    clear();
    in_data.resize(R);
    for (int r = 0; r < R; ++r)
    {
        in_data[r].resize(C);
        for (int c = 0; c < C; ++c)
        {
            fin >> in_data[r][c];
        }
    }
    convert();
}

void algorithm::solve(std::ifstream & fin, std::ofstream & fout)
{
    vector<vector<int> > dp;
    int mask_all = 1;
    int N = a.size();
    for(int i=1; i<N; ++i)
        mask_all |= (mask_all<<1);

    int M = mask_all + 1;

    std::vector<std::vector<int> > by_ones(N+1);
    for (int i = 0; i < M; ++i)
        by_ones[ones_count(i)].push_back(i);

    dp.resize(N);
    for(int i=0; i<N; ++i)
    {
        dp[i].reserve(M);
        for(int j=0; j<M; ++j)
            dp[i].push_back(MINUS_INF);
    }

    for(int i=0; i<M; ++i)
        dp[0][i] = 0;

    for(int ones = 0; ones < N; ++ones)
    {
        for(int mask_n=0; mask_n<by_ones[ones].size(); ++mask_n)
        {
            int cur_mask = by_ones[ones][mask_n];
            for(int i=0; i<N; ++i)
            {
                if(dp[i][cur_mask]!=MINUS_INF)
                {
                    for(int node=1, ms=1; node<N; ++node, ms<<=1)
                    {
                        if((cur_mask&ms)==0)
                        {
//                            cout<<"here2 ["<<cur_mask<<endl;
                            int new_mask = cur_mask | ms;
//                            cout<<"["<<new_mask<<"<-"<<cur_mask<<endl;
                            if(dp[i][new_mask]<dp[i][cur_mask])
                                dp[i][new_mask] = dp[i][cur_mask];
                            if(dp[node][new_mask]<dp[i][cur_mask] + a[i][node])
                                dp[node][new_mask]=dp[i][cur_mask] + a[i][node];
                        }
                    }
                }
            }
        }
    }

//    cout<<"\ndp\n";
//    for(int x=0; x<dp.size(); ++x)
//    {
//        for(int y=0; y<dp[x].size(); ++y)
//        {
//            cout<<dp[x][y]<<" ";
//        }
//        cout<<"\n";
//    }

    int result = 0;

    for(int msk = 1; msk<M; ++msk)
    {
        int op_msk = (~msk)&mask_all;
        for(int node=1; node<N; ++node)
        {
            if(dp[node][msk]>0)
            {
                result = std::max(result, dp[node][msk] + a[node][0]);

                for(int i=1, mms=1; i<N; ++i, mms<<=1)
                {
                    if(op_msk&mms)
                    {
                        int res1 = dp[node][msk] + dp[i][op_msk] + a[i][node] - value[node];
                        result = std::max(result, res1);
                    }
                }
            }
        }
    }

    fout<<result<<endl;
}

void algorithm::solution(char *input, char *output)
{
//    std::ios_base::sync_with_stdio(0);

    std::ifstream fin(input);
    std::ofstream fout(output);

    int test_cases;
    fin >> test_cases;

    for (int test_case = 1; test_case <= test_cases; ++test_case)
    {
//        fout << "Case# " << test_case << std::endl;
        load(fin);
        solve(fin, fout);
//        printA();
    }

    fin.close();
    fout.close();
}